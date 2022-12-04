# File System in C


### Instruction of running system
-   **$header$** directory consist of header file system
-   **$bin$** directory consist of all binary file    generated. The File system executable is named as FileSystem.out
-   **$obj$** directory consist of all object file genearated during compilation
-   **$src$** directory consist of the src file for the file system
-   **To perform the operation on file system make change in $main.c$ file in $src$ directory**




### Working Environment
-   gcc-9.5.0
-   ubuntu


### Setup Guidelines for Project
#### 1.Build the File System
```
make build
```

### 2.Removing Object and Start from Scratch
```
make clean
```

### 3.Running the File System
```
make clean
make build
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