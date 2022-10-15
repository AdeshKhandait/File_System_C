// The All the Global Structure, File, Variable, and Macros
#define BLOCKSIZE 1024
#define NAME 256

#define DISK_NAME "./bin/DISK.vd"
FILE *DISK;
// Basic Information
// 1GB = 1000000000
// Empty = -1
// Occupied = -2

//-------------------------------------------------------------------Structures-------------------------------------------------------
// StartBlock -> Stores Information
// - Size of File System
// - Start of MetaData
// - Start of Data_Block 
// - Size of Block

struct StartBlock
{
    // Size of the File System
    unsigned long long int sizeHDD;
    unsigned long long int start_MetaData;
    unsigned long long int start_Data_Block;
    unsigned long int size_block;
};

// MetaData -> Stores the Stores Information
// 1.File Size
// 2.First Data Block
// 3.File Number
// 4.File Name

struct MetaData
{
    unsigned long long int file_size;
    long long int first_block;
    long long int file_number;
    char file_name[NAME];
};


// Disk Block
struct DiskBlock
{
    long long int Next_Disk_Block;
    long int pos;
    char Data[BLOCKSIZE];
};

//-------------------------------------------------------------------Variables-------------------------------------------------------

// Defining the MetaData Variables

// Size of sizeHDD
unsigned long long int sizeHDD;

// Size of Start Block
unsigned long long int size_StartBlock;

// HDD - Size of Start_Block
unsigned long long int sizeHDD_StartBlock;

// Size of the MetaData
unsigned long long int size_MetaData;

// Size of the DiskBlock
unsigned long long int size_DiskBlock;

// MetaData + DiskBlock
unsigned long long int size_MetaData_DiskBlock;

// Number of MetaData
unsigned long long int num_MetaData;

// Number of the DiskBlock
unsigned long long int num_DiskBlock;

unsigned long long int Space;



//-------------------------------------------------------------------Declaring the Structures-------------------------------------------------------

struct StartBlock SB;