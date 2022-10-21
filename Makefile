# MakeFile for FileSystem

# ---------------------------Macros-----------------------------------------------
# Specifying the Compiler and DEBUG
CC=gcc
DB = gdb

# Specifying the Flags
CFLAG = -Wno-implicit

# SRC Directory
SRC = src

# Object Directory
OBJ = obj

# Bin Directory
BINDIR = bin

# Specifying the list of all Src files
SRCS = $(wildcard $(SRC)/*.c)

# Specifying the list of all Src files
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
 
# Specifying the Binary file
BIN = $(BINDIR)/FileSystem

# Export in zip file
EXPORT_NAME = FileSystem.zip

all: $(BIN)

# Binary file generated
$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@
	# ./$(BIN)

# Compile all .c and create .o using auto varibles($<) and ($@)
# What they basically means is that same as above
$(OBJ)/%.o: $(SRC)/%.c
	$(CC) -c $< -o $@

# Removing the file
clean: 
	$(RM) -r $(OBJ)/%.c $(BINDIR)/%.c
run:
	./$(BIN)
export:
	$(RM) $(EXPORT_NAME)
	zip $(EXPORT_NAME) $(BIN) src/*.c Makefile README.md

# Debugging
release: CFLAG = -g -Wall
release: clean
release: $(BIN)

debug: 
	gdb ./$(BIN)

build: clean
build: all
build: run 