File System in C without the using Linux System Call

## Setup Guidelines for Project
### 1.Build the File System
```
make
```

### 2.Removing Object and Start from Scratch
```
make clean
```

### 3.Running the File System
```
make run
```

### 4.Export the export in .zip file 
```
make export
```

### 5.Release the Final Version with fresh Compilation
```
make release
```

### 6.Debug the File System
1. Fresh Compilation of Project
```
make release
```
2. Running the GDB Debugger
```
make debug
```
3. After the GDB Started
```
run
```
4. For exitting the GDB Debugger
```
q
```