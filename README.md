# Mini Shell - mysh
A custom command-line interpreter written in C

## Features
- Command execution
- Pipelines (ls | grep foo | wc -l)
- I/O redirection (>, >>, <)
- Built-in commands: cd, exit, export

## Build
```
cd mysh
make
```

## Run
```
./bin/mysh
```
<img width="223" height="52" alt="Screenshot 2026-06-27 at 22 14 47" src="https://github.com/user-attachments/assets/94e913d5-9d4e-4e26-94be-d6293a0ad89d" />

## Known limitations
- No signal handling (Ctrl+C kills the shell)
- No memory cleanup between commands
- Input buffer limited to 256 characters
- No syntax validation
