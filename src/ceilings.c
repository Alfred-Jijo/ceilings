#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/* Platform-specific includes and macros */
#ifdef _WIN32
#include <direct.h>
#include <windows.h>
#define SLEEP_SEC(s) Sleep((s) * 1000)
#define CLEAR_SCREEN system("cls")
#define PATH_SEP "\\"
#define NULL_DEVICE "NUL"
#else
#include <dirent.h>
#include <unistd.h>
#define SLEEP_SEC(s) sleep(s)
#define CLEAR_SCREEN printf("\033[H\033[J")
#define PATH_SEP "/"
#define NULL_DEVICE "/dev/null"
#endif

/* Configuration */
#define PATCH_DIR "patches"
#define EXERCISE_DIR "exercises"
#define MAX_PATH_LEN 1024
#define MAX_PATCHES 100

/* ANSI Colors */
#define GREEN "\033[92m"
#define RED "\033[91m"
#define YELLOW "\033[93m"
#define RESET "\033[0m"
#define BOLD "\033[1m"

/* Function Prototypes */
int compare_strings(const void *a, const void *b);
void print_pass(const char *msg);
void print_fail(const char *msg);
void print_info(const char *msg);
int compile_exercise(const char *patch_filename);
int check_patch(const char *filename);
int get_patch_files(char *patch_list[], int max_patches);

int
main(void)
{
	char *patch_list[MAX_PATCHES];
	int patch_count = 0;
	int all_passed = 1;

/* Enable ANSI escape codes on Windows 10+ */
#ifdef _WIN32
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	if (hOut != INVALID_HANDLE_VALUE && GetConsoleMode(hOut, &dwMode)) {
		dwMode |= 0x0004; // ENABLE_VIRTUAL_TERMINAL_PROCESSING
		SetConsoleMode(hOut, dwMode);
	}
#endif

	patch_count = get_patch_files(patch_list, MAX_PATCHES);

	if (patch_count == 0) {
		fprintf(stderr, "%sNo patches found in '%s'.%s\n", RED, PATCH_DIR, RESET);
		return 1;
	}

	qsort(patch_list, patch_count, sizeof(char *), compare_strings);

	printf("%sVerifying Repository State against %d exercises...%s\n\n", BOLD, patch_count,
	       RESET);

	for (int i = 0; i < patch_count; i++) {
		print_info(patch_list[i]);

		/* Compile the exercise using Make */
		if (!compile_exercise(patch_list[i])) {
			all_passed = 0;
			free(patch_list[i]);
			/* Stop immediately on compile error so the user focuses on one thing */
			break;
		}

		/* Check logic against the patch */
		if (check_patch(patch_list[i])) {
			char msg[MAX_PATH_LEN];
			snprintf(msg, sizeof(msg), "Logic correct.");
			print_pass(msg);
		} else {
			char msg[MAX_PATH_LEN];
			snprintf(msg, sizeof(msg),
				 "Code compiled, but logic doesn't match the solution.");
			print_fail(msg);
			all_passed = 0;
		}
		printf("\n");
		free(patch_list[i]);
	}

	printf("========================================\n");
	if (all_passed) {
		printf("%s%sRESULT: ALL EXERCISES PASSED!%s\n", GREEN, BOLD, RESET);
		return 0;
	} else {
		printf("%s%sRESULT: FAIL%s\n", RED, BOLD, RESET);
		return 1;
	}
}

/* Comparator for qsort to ensure patches run in order (e.g., 01, 02) */
int
compare_strings(const void *a, const void *b)
{
	return strcmp(*(const char **)a, *(const char **)b);
}

void
print_pass(const char *msg)
{
	printf("[%sPASS%s] %s\n", GREEN, RESET, msg);
}

void
print_fail(const char *msg)
{
	printf("[%sFAIL%s] %s\n", RED, RESET, msg);
}

void
print_info(const char *msg)
{
	printf("[%sINFO%s] %s\n", YELLOW, RESET, msg);
}

/* * Compiles the exercise file using Make.
 * Returns 1 if compilation succeeds, 0 otherwise.
 */
int
compile_exercise(const char *patch_filename)
{
	char source_path[MAX_PATH_LEN];
	char make_cmd[MAX_PATH_LEN];
	char base_name[MAX_PATH_LEN];
	char *dot;

	/* Remove .patch extension */
	strncpy(base_name, patch_filename, sizeof(base_name));
	dot = strrchr(base_name, '.');
	if (dot)
		*dot = '\0';

	/* Construct path: exercises/001_intro */
	snprintf(source_path, sizeof(source_path), "%s%s%s", EXERCISE_DIR, PATH_SEP, base_name);

	/* Construct command: make exercises/001_intro */
	snprintf(make_cmd, sizeof(make_cmd), "make \"%s\"", source_path);

	printf("%sCompiling %s...%s\n", BOLD, base_name, RESET);

	int status = system(make_cmd);

	if (status != 0) {
		printf("\n%s[COMPILATION ERROR]%s The code above failed to compile.\n", RED, RESET);
		printf("Fix the errors in '%s.c' before checking logic.\n", base_name);
		return 0;
	}
	return 1;
}

/* * Checks if a patch is applied by attempting to reverse-apply it.
 * Returns 1 if passed (code matches patch), 0 if failed.
 */
int
check_patch(const char *filename)
{
	char command[MAX_PATH_LEN];

	/* Construct the command: git apply --check --reverse patches/<filename> > <null_device>
	 * 2>&1 */
	snprintf(command, sizeof(command), "git apply --check --reverse \"%s%s%s\" > %s 2>&1",
		 PATCH_DIR, PATH_SEP, filename, NULL_DEVICE);

	int status = system(command);

	/* system() returns 0 on success */
	return (status == 0) ? 1 : 0;
}

/* * Cross-platform function to populate the patch_list.
 * Returns the number of patches found.
 */
int
get_patch_files(char *patch_list[], int max_patches)
{
	int count = 0;

#ifdef _WIN32
	WIN32_FIND_DATA findData;
	HANDLE hFind;
	char search_path[MAX_PATH_LEN];

	/* Windows requires a wildcard pattern (e.g., "patches\*.patch") */
	snprintf(search_path, sizeof(search_path), "%s\\*.patch", PATCH_DIR);

	hFind = FindFirstFile(search_path, &findData);
	if (hFind == INVALID_HANDLE_VALUE) {
		return 0; // No files found or directory doesn't exist
	}

	do {
		if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			if (count < max_patches) {
				patch_list[count++] = _strdup(findData.cFileName);
			}
		}
	} while (FindNextFile(hFind, &findData) != 0);

	FindClose(hFind);

#else
	/* POSIX implementation (Linux/macOS) */
	DIR *d;
	struct dirent *dir;

	d = opendir(PATCH_DIR);
	if (!d) {
		return 0;
	}

	while ((dir = readdir(d)) != NULL) {
		if (dir->d_type != DT_REG && dir->d_type != DT_UNKNOWN) {
			continue;
		}

		char *dot = strrchr(dir->d_name, '.');
		if (!dot || strcmp(dot, ".patch") != 0) {
			continue;
		}

		if (count >= max_patches) {
			break;
		}

		patch_list[count++] = strdup(dir->d_name);
	}
	closedir(d);
#endif
	return count;
}
