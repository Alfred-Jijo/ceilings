![ceilings marquis](assets/marquis.png)
# ceilings

A code-along project in C in the vein of [rustlings](https://rustlings.cool) and especially [ziglings](https://ziglings.org). Failing test cases of almost-working C code for a student to correct in order to pass the test suite, learning C in the process!

## NOTE
This project is very much a WIP and quite transparently indebted to the ziglings project, which I'm following along with as I learn both languages.

## Getting Started

### Prerequisites
To use Ceilings, you need the following tools installed and available in your terminal path:
* **Git**: Essential for the verification logic.
* **C Compiler**: `gcc` or `clang`.
* **Make**: GNU Make (standard on Linux/macOS; often part of MinGW or build-essentials).

### Installation & Usage

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/Alfred-Jijo/ceilings.git
    cd ceilings
    ```

2.  **Build the verification tool:**
    Run the standard Make command in the root directory:
    ```bash
    make
    ```
    This compiles the `ceilings` executable (or `ceilings.exe` on Windows).

3.  **Start the course:**
    Run the verification tool:
    * **Linux/macOS:** `./ceilings`
    * **Windows:** `ceilings.exe`

4.  **The Loop:**
    * The tool will verify exercises in order.
    * If an exercise fails (compiler error or logic check), it stops and points you to the file (e.g., `exercises/001_START_HERE.c`).
    * Open the file, fix the code, and save.
    * Run `./ceilings` again.
    * Repeat until you complete Ceilings!

## Roadmap
* [x] Emulate rustlings binary operation 
* [x] Cross-platform support on:
    - Windows *with WSL*
    - Linux
    - macOS
* [ ] File watcher functionality
* [ ] Fix generating patches
* [ ] Generated All patches
