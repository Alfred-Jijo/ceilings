#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#include <windows.h>
#define SLEEP_SEC(s) Sleep((s) * 1000)
#define CLEAR_SCREEN system("cls")
#else
#include <unistd.h>
#define SLEEP_SEC(s) sleep(s)
#define CLEAR_SCREEN printf("\033[H\033[J")
#endif

#define EXERCISE_DIR "exercises"

// ANSI Colors (Note: Windows 10+ supports these, but older cmds might print raw codes.
#define HEADER "\033[95m"
#define BLUE "\033[94m"
#define GREEN "\033[92m"
#define YELLOW "\033[93m"
#define RED "\033[91m"
#define RESET "\033[0m"
#define BOLD "\033[1m"

typedef struct {
	const char *target;
	const char *filename;
} Exercise;

Exercise CHAPTERS[] = {{"001_START_HERE", "001_START_HERE.c"},
		       {"002_stdio", "002_stdio.c"},
		       {"003_variables", "003_variables.c"},
		       {"004_loops", "004_loops.c"},
		       {"005_constants", "005_constants.c"},
		       {"006_bit_widths", "006_bit_widths.c"},
		       {"007_getchar", "007_getchar.c"},
		       {"008_getlines", "008_getlines.c"},
		       {"019_arrays", "019_arrays.c"},
		       {"999_the_end", "999_the_end.c"},
		       {NULL, NULL}};

int
check_is_done(const char *filepath)
{
	char full_path[256];
	snprintf(full_path, sizeof(full_path), "%s/%s", EXERCISE_DIR, filepath);

	FILE *fp = fopen(full_path, "r");
	if (!fp)
		return 0; // If file doesn't exist, it's definitely not done

	char buffer[1024];
	int not_done = 0;
	while (fgets(buffer, sizeof(buffer), fp)) {
		if (strstr(buffer, "// I AM NOT DONE")) {
			not_done = 1;
			break;
		}
	}
	fclose(fp);
	return !not_done;
}

int
build_and_run(const char *target)
{
	char cmd[1024];

	printf(BLUE "Compiling %s...\n" RESET, target);

	snprintf(cmd, sizeof(cmd), "cmake --build . --target %s", target);
	if (system(cmd) != 0) {
		printf(RED "COMPILATION FAILED\n" RESET);
		return 0;
	}

	printf(GREEN "Running...\n" RESET);
#ifdef _WIN32
	// Windows executable path logic
	snprintf(cmd, sizeof(cmd), "Debug\\%s.exe", target);
	// Fallback check if simple build
	struct stat st;
	if (stat(cmd, &st) != 0) {
		snprintf(cmd, sizeof(cmd), "%s.exe", target);
	}
#else
	snprintf(cmd, sizeof(cmd), "./%s", target);
#endif

	if (system(cmd) != 0) {
		printf(RED "RUNTIME ERROR\n" RESET);
		return 0;
	}
	return 1;
}

int
main(int argc, char **argv)
{
	// Basic check for exercises dir
	struct stat st = {0};
	if (stat(EXERCISE_DIR, &st) == -1) {
		printf(RED "Error: '%s' directory not found.\n" RESET, EXERCISE_DIR);
		printf("Did you forget to apply the patch?\n");
		printf(YELLOW "Run: git apply exercises.patch\n" RESET);
		return 1;
	}

	int watch_mode = (argc > 1 && strcmp(argv[1], "watch") == 0);

	do {
		if (watch_mode) {
			CLEAR_SCREEN;
			printf(HEADER "=== WATCH MODE ===\n" RESET);
		}

		int all_done = 1;
		for (int i = 0; CHAPTERS[i].target != NULL; i++) {
			if (!check_is_done(CHAPTERS[i].filename)) {
				all_done = 0;
				printf(BOLD "Current Exercise: %s\n" RESET, CHAPTERS[i].filename);

				if (build_and_run(CHAPTERS[i].target)) {
					printf(GREEN "Passed! Remove '// I AM NOT DONE' to "
						     "continue.\n" RESET);
				} else {
					printf(YELLOW "Check %s/%s\n" RESET, EXERCISE_DIR,
					       CHAPTERS[i].filename);
				}

				if (!watch_mode)
					return 1; // Exit if failed in normal mode
				goto sleep_loop;
			}
		}

		if (all_done) {
			printf(GREEN BOLD "\nAll exercises completed! You are a C master!\n" RESET);
			return 0;
		}
	sleep_loop:
		if (watch_mode) {
			SLEEP_SEC(2);
		}
	} while (watch_mode);

	return 0;
}
