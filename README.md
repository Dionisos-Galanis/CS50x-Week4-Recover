# CS50x-Week4-Recover

CS50x course - Week4 problem set - Program, which recover "erased" jpg files from a disk image, implemented in C.

Specification:

Implement a program called `recover` that recovers JPEGs from a forensic image.

- Implement your program in a file called `recover.c` in a directory called `recover`.
- Your program should accept exactly one command-line argument, the name of a forensic image from which to recover JPEGs.
- If your program is not executed with exactly one command-line argument, it should remind the user of correct usage, and `main` should return `1`.
- If the forensic image cannot be opened for reading, your program should inform the user as much, and main should return 1.
- The files you generate should each be named `###.jpg`, where `###` is a three-digit decimal number, starting with 000 for the first image and counting up.
- Your program, if it uses `malloc`, must not leak any memory.
