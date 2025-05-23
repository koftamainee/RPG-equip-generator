# cpp-project-template
A template for my projects written in C++
## Comfort interface for building projects, based on CMake build system. Commands automation done via Make
```bash
$ make help

Project Build System
Targets:
  all           - Default build (Release)
  build         - Build project (BUILD_TYPE=Release)
  debug         - Build Debug version
  release       - Build Release version
  clean         - Remove build artifacts
  cleanbuild    - Clean and rebuild
  run           - Run Debug build (ARGS= for arguments)
  pwn           - Debug with pwndbg
  valgrind      - Run with Valgrind memcheck
  analyze       - Run static code analysis with clang-tidy
  help          - Show this help

Variables:
  BUILD_TYPE    - Debug/Release (default: Release)
  GENERATOR     - CMake generator (default: Ninja)
  V=1           - Verbose output
  ARGS          - Arguments for run/valgrind
```
