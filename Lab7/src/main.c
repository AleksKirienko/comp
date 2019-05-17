#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "lib.h"

#define SECT_SIZE 512 
int count = 0;

double disk;
void show_partitions(tPART *part, int num_parts)
{

    for (int i = 0; i < num_parts; i++) {

        printf("%d", part[i].activ);
	printf("\t");

        printf("%d-%d-%d", part[i].beg.cyl, part[i].beg.head, part[i].beg.sec);
	printf("\t");


        printf("%d-%d-%d", part[i].end.cyl, part[i].end.head, part[i].end.sec);
	printf("\t");

        printf("%d", part[i].lba_beg.lba);
	printf("\t");

	printf("%d", part[i].size);
		printf("\t");

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
            char ans[3];
            scanf("%s", ans);
            if (ans[0] == 'y') {
                part[i].activ = 1;
                activ++;
            }
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
        count++;
        part[i].size = disk;
        a_lba2chs(geo, part[i].lba_beg, &part[i].beg);
        tLBA lba_tmp = {part[i].lba_beg.lba + part[i].size - 1};
        a_lba2chs(geo, lba_tmp, &part[i].end);
		break;
	}
    disk-= part[i].size;
 	count++;
    if (disk <= 0)
    {
        break;
    }
        a_lba2chs(geo, part[i].lba_beg, &part[i].beg);
        tLBA lba_tmp = {part[i].lba_beg.lba + part[i].size - 1};
        a_lba2chs(geo, lba_tmp, &part[i].end);
    }
    if (activ == 0)
        part[count-1].activ = 1;
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
	disk = (double)geo.head*geo.cyl*geo.sec;
	printf ("Size = %.2lfGb\n", disk/2/1024/1024);
    printf("input num of parts: ");
    int num_parts;
    scanf("%d", &num_parts);
    getchar();
    tPART *part = (tPART*)malloc(sizeof(*part) * num_parts);
    enter_partitions(part, geo, num_parts);
    show_partitions(part, count);
    return 0;
}
