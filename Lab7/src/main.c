#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "lib.h"

#define SECT_SIZE 512 
int count = 0;
enum os_type {
    empty = 0x0, fat12 = 0x1, fat16 = 0x4, ext = 0x5, dosfat16 = 0x6, 
    ntfs = 0x7, winfat32 = 0xc, winfat16 = 0xe, swp = 0x82, nix = 0x83
} os_type;


void show_partitions(tPART *part, int num_parts)
{

    for (int i = 0; i < num_parts; i++) {

        printf("%d", part[i].activ);
	printf("\t");

        printf("%d-%d-%d", part[i].beg.cyl, part[i].beg.head, part[i].beg.sec);
	printf("\t");

        printf("%xh", part[i].os);
	printf("\t");

        printf("%d-%d-%d", part[i].end.cyl, part[i].end.head, part[i].end.sec);
	printf("\t");

        printf("%d", part[i].lba_beg.lba);
	printf("\t");
        if (part[i].os == 0x5) {
            int size = 0;
            for (int j = i; j < num_parts; j++)
                size += part[j].size;
            printf("%d", size);
		printf("\t");
        } else {
            printf("%d", part[i].size);
		printf("\t");
        }
	printf("\n");

    }
}

void enter_partitions(tPART *part, tCHS geo, int num_parts)
{
    int activ = 0;

    for (int i = 0; i < num_parts; i++) {
        if (!activ) 
	{
            printf("is this part is active? (y\\n): ");
            char ans = getchar();
            if (ans == 'y') {
                part[i].activ = 1;
                activ++;
            }
        }

        int exit = 0,
            ext_flg = 0;
        
        if (ext_flg) {
            part[i].lba_beg = (tLBA){part[i - 1].lba_beg.lba + 
                part[i - 1].size};
            a_lba2chs(geo, part[i].lba_beg, &part[i].beg);
            part[i].end = part[i].beg;
            continue;
        }

        if (i == 0)
            part[i].lba_beg.lba = 1;
        else {
            tLBA lba_tmp = {part[i - 1].lba_beg.lba + part[i - 1].size};
            part[i].lba_beg = lba_tmp;
        }
        
        printf("enter size: ");

        scanf("%d", &part[i].size);
	if (part[i].size == 0)

	{
		break;
	}
 	count++;
        a_lba2chs(geo, part[i].lba_beg, &part[i].beg);
        tLBA lba_tmp = {part[i].lba_beg.lba + part[i].size - 1};
        a_lba2chs(geo, lba_tmp, &part[i].end);
    }
}

int main()
{
    tCHS geo;
    printf("input c-h-s: ");
    scanf("%hd-%hd-%hd", &geo.cyl, &geo.head, &geo.sec);
	while (geo.head>15 || geo.cyl>65535 || geo.sec>255)
	{
		printf ("Error input");
		scanf("%hd-%hd-%hd", &geo.cyl, &geo.head, &geo.sec);

	}
	double disk = (double)geo.head*geo.cyl*geo.sec/2/1024/1024;
	printf ("Size = %.2lfGb\n", disk);
    printf("input num of parts: ");
    int num_parts;
    scanf("%d", &num_parts);
    getchar();
    tPART *part = (tPART*)malloc(sizeof(*part) * num_parts);
    enter_partitions(part, geo, num_parts);
    show_partitions(part, count);
    return 0;
}
