#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    char fmem[256];
}frame;

typedef struct
{
    frame pmem[256];
}physical_memory;

typedef struct
{
    int from[16];
    int to[16];
    int head;
}tlb;


int main(int argc, char** argv)
{
    int i;
    // allocate memory
    tlb TLB;
    TLB.head = 0;
    for(i=0;i<16;i++)
        TLB.from[i] = -1;

    int ptable[256];
    int curr_frame = 0;
    frame ftable[256];
    for(i = 0; i < 256; i++)
    {
        ptable[i] = -1;
        ftable[i] = *(frame*) malloc(sizeof(frame));
    }




    if(argc != 2)
    {
        printf("address filename required as commandline argument\n");
        return 0;
    }
    FILE* addresses = fopen(argv[1], "r");
    FILE* bstore = fopen("BACKING_STORE.bin", "r");
    int ladd, page_num, offset;
    int padd;
    int frame_num;

    // statistics
    int num_addresses = 0, num_page_faults = 0, num_tlb_hits = 0;

    fscanf(addresses, "%d", &ladd);
    while(!feof(addresses))
    {
        num_addresses++;

        page_num = (ladd >> 8) & 255;
        offset = ladd & 0x00FF;
        printf("Virtual address: %d ", ladd);

        // check tlb
        int hit = 0;
        for(i=0;i<16;i++)
            if(TLB.from[i] == page_num)
            {
                hit = 1;
                break;
            }
        if(hit == 1) // tlb hit
        {
            frame_num = TLB.from[i];
            num_tlb_hits++;
        }
        else // tlb miss
        {
            // check page table
            hit = 0;
            for(i=0;i<256;i++)
                if(ptable[page_num] != -1)
                {
                    frame_num = ptable[page_num];
                    hit = 1;
                    if(TLB.head == 16)
                        TLB.head = 0;
                    TLB.from[TLB.head] = page_num;
                    TLB.to[TLB.head++] = frame_num;
                    break;
                }
            if(hit != 1) // page fault occurred
            {
                num_page_faults++;
                // retrieve from backing store
                frame_num = curr_frame++;

                if(TLB.head == 16)
                    TLB.head = 0;
                TLB.from[TLB.head] = page_num;
                TLB.to[TLB.head++] = frame_num;

                ptable[page_num] = frame_num;

                fseek(bstore, 256 * page_num, SEEK_SET);
                fread(&ftable[frame_num], 1, 256, bstore);
            }
        }
        char value = ftable[frame_num].fmem[offset];

        padd = frame_num * 256 + offset;
        printf("Physical address: %d Value: %d\n", padd, value);
        fscanf(addresses, "%d", &ladd);
    }

    printf("Number of Translate Addresses: %d\n", num_addresses);
    printf("Page Faults: %d\n", num_page_faults);
    printf("Page Fault Rate: %.3lf\n", (double)num_page_faults/num_addresses);
    printf("TLB Hits: %d\n", num_tlb_hits);
    printf("TLB Hit Rate: %.3lf\n", (double)num_tlb_hits/num_addresses);

    return 0;

}
