#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    char fmem[256];
}frame;

typedef struct
{
    int from[16];
    int to[16];
    int head;
}tlb;


int main(int argc, char** argv)
{
    int clock = 129;

    int i;
    // allocate memory
    tlb TLB;
    TLB.head = 0;
    for(i=0;i<16;i++)
        TLB.from[i] = -1;

    int ptable_from[128];
    int ptable_to[128];
    int ptable_time[128];
    frame ftable[256];
    for(i = 0; i < 128; i++)
    {
        ptable_from[i] = -1;
        ptable_to[i] = i;
        ptable_time[i] = i;
    }
    for(i=0;i<256;i++)
        ftable[i] = *(frame*) malloc(sizeof(frame));

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
            for(i=0;i<128;i++)
                if(ptable_from[i] == page_num)
                {
                    frame_num = ptable_to[i];
                    hit = 1;
                    if(TLB.head == 16)
                        TLB.head = 0;
                    TLB.from[TLB.head] = i;
                    TLB.to[TLB.head++] = frame_num;
                    break;
                }
            if(hit != 1) // page fault occurred
            {
                num_page_faults++;
                // retrieve from backing store

                // select page to replace
                int min = 0xFFFFF;
                int min_page = -1;
                for(i=0;i<128;i++)
                    if(ptable_time[i] < min)
                    {
                        min = ptable_time[i];
                        min_page = i;
                    }
                frame_num = ptable_to[min_page];

                ptable_time[min_page] = clock++;

                if(TLB.head == 16)
                    TLB.head = 0;

                TLB.from[TLB.head] = page_num;
                TLB.to[TLB.head++] = frame_num;

                ptable_from[min_page] = page_num;
                ptable_to[min_page] = frame_num;

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
