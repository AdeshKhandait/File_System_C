// The All the Global Structure, File, Variable, and Macros
#define BLOCKSIZE 1024
#define NAME 256

#define DISK_NAME "./bin/DISK.vd"
FILE *DISK;

#define SET_BIT(BF, N) BF |= ((__uint128_t)0x0000000000000001 << N)
#define CLR_BIT(BF, N) BF &= ~((__uint128_t)0x0000000000000001 << N)
#define IS_BIT_SET(BF, N) ((BF>>N) & 01)


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
