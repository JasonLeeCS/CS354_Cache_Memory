/**
 * Jason Lee (jlee967@wisc.edu)
 * 908 223 8909
 * 
 **/
#include <stdio.h>

// THE CACHE
struct LINE{
    char valid;
    int tag;
    char data[32];
};

struct SET{
    struct LINE line[1];
};

struct CACHE {
    struct SET set[8];
} cache;

// GLOBALDATA
// increment these in your function
unsigned hit_count  = 0;
unsigned miss_count = 0;
unsigned read_data_count = 0;

// SYSTEM BUS 
// call Read_Data_From_Ram to update this
char system_bus[32];



// READ DATA FROM RAM
// this function copies 32 character from the text file to
// the system_bus array aligned with the system bus
// (we will not test this with input larger than the text file)
void Read_Data_From_Ram(unsigned address) {
    address >>= 5; address <<= 5; // get align the data
    read_data_count++;
    FILE *file;
    file = fopen("alice_in_wonderland.txt", "r");
    fseek(file, address, SEEK_SET);
    for (int i = 0; i<32; i++) system_bus[i] = fgetc(file);
    return;
}


// COMPLETE THE FOLLOWING FUNCTION 
//
// this code should check to see if the data in the cache is valid and the tag matches
// if so it should return the char matching the address and increment the hit count
//
// if not it should read the data from the system bus copy it into the cache and 
// increment the miss count and return the char matching the address
// 
char Read_Data_From_Cache(unsigned address)
{
    // Calculations for tag, setIndex, and offset for the address
    char returnValue;
    unsigned tag = address >> 9;
    unsigned setIndex = 15 & (address >> 5);
    unsigned offset = address & 31;

    // Valid bit and tag bit for the wanted set
    char validBit = cache.set[setIndex].line[0].valid;
    int tagBit = cache.set[setIndex].line[0].tag;

    // If cache hit
    if((validBit != 0) && (tag == tagBit))
    {
        returnValue = cache.set[setIndex].line[0].data[offset]; // Update returnValue
        
        hit_count++;
        return returnValue;
    }

    // If cache miss, call Read_Data_From_Ram function
    Read_Data_From_Ram(address);

    for(int i = 0; i < 32; i++) // Loop to copy system bus data into cache
    {
        cache.set[setIndex].line[0].data[i] = system_bus[i];
    }

    cache.set[setIndex].line[0].tag = tagBit; // Update tag
    cache.set[setIndex].line[0].valid = 1; // Set to valid
    returnValue = cache.set[setIndex].line[0].data[offset]; // Update returnValue
    
    miss_count++; 
    return returnValue;
}

int main() {
    // INITIALIZE CACHE
    for (int i = 0; i<8; i++) cache.set[i].line[0].valid = 0;
    
    // READ SOME DATA
    char c;
    //printf("Reading character at index = %i  : data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", i, c, hit_count, miss_count,read_data_count);     
    
    // c = Read_Data_From_Cache(0); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    // c = Read_Data_From_Cache(1); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    // c = Read_Data_From_Cache(2); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    // c = Read_Data_From_Cache(3); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    // c = Read_Data_From_Cache(4); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );


    // WRITE A LOT MORE TESTS
    // printf("\n");
    
    // for(int i = 0; i < 10; i++)
    // {
    //   c = Read_Data_From_Cache(i); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    // }
    
    // printf("\n");
    
    // for(int i = 0; i < 50; i+= 10)
    // {
    //   c = Read_Data_From_Cache(i); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    // }

    // printf("\n");
    // for(int i = 0; i < 500; i+= 32)
    // {
    //   c = Read_Data_From_Cache(i); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    // }

    // printf("\n");
    // for(int i = 0; i < 1000; i+= 100)
    // {
    //   c = Read_Data_From_Cache(i); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    // }

    // printf("\n");
    // for(int i = 0; i < 10000; i+= 1000)
    // {
    //   c = Read_Data_From_Cache(i); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    // }

    // printf("\n");
    // for(int i = 0; i < 100; i+= 31)
    // {
    //   c = Read_Data_From_Cache(i); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    // }

    // printf("\n");
    // for(int i = 0; i < 100; i+= 29)
    // {
    //   c = Read_Data_From_Cache(i); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    // }

    // printf("\n");
    // for(int i = 0; i < 100; i+= 15)
    // {
    //   c = Read_Data_From_Cache(i); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    // }

    // printf("\n");
    // for(int i = 2; i < 100; i+= 12)
    // {
    //   c = Read_Data_From_Cache(i); printf("data = %c : hit count = %-3u : miss count = %-3u : read data count = %-3u\n", c, hit_count, miss_count,read_data_count );
    // }
    return 0;
}

