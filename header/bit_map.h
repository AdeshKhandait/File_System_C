// Variable
extern unsigned long long int map_size_MetaData;
extern unsigned long long int map_size_DiskBlock;

// Functions

    // MetaData
    void set_all_bit_MetaData();

    void check_all_bit_MetaData();

    void create_empty_bit_map_MetaData();

    void print_bit_block_MetaData(unsigned long long int number);

    void clear_bit_MetaData(unsigned long long int number);

    void set_bit_MetaData(unsigned long long int number);

    unsigned long long int search_empty_MetaData();

    //DiskBlock
    void set_all_bit_DiskBlock();

    void check_all_bit_DiskBlock();

    void create_empty_bit_map_DiskBlock();

    void print_bit_block_DiskBlock(unsigned long long int number);

    void clear_bit_DiskBlock(unsigned long long int number);

    void set_bit_DiskBlock(unsigned long long int number);

    unsigned long long int search_empty_DiskBlock(); 