/* In the name of Allah, the Merciful, the Compassionate */

/* A program to test fopen and FILE */

#include <stdio.h>
#include "encode_rs.h"

int mp[15] = { 0 };

main()
{
	FILE *file,*fencoded;
	char *buffer;

	unsigned long fileLen;
	int l = 0;
	int c;
	int i;
	int count = 0;


	unsigned char msn;
	unsigned char lsn;

	int mod;

	int count2;
	int extras;
        fencoded = fopen("test","wb");

	file = fopen("testbin", "rb");

	if(!file)
	{
		printf("Unable to open file ");
		return;
	}

	fseek(file, 0, SEEK_END);
	fileLen = ftell(file);


	mod = (fileLen * 2) % 11;
	printf("fileLen = %d\tmod = %d\n", fileLen, mod);
	fseek(file, 0, SEEK_SET);

	buffer =  (char *)malloc(fileLen + 1);

	if(!buffer)
	{
		fprintf(stderr, "Memory error");
		fclose(file);

		return;
	}

	fread(buffer, fileLen, 1, file);
	fclose(file);

	for (c = 0; c < fileLen*2 ; c++)
	{

		msn =  (int)*(buffer + l) & 0x0F;
		lsn =  (int)*(buffer + l) & 0xF0;
		lsn = (lsn >> 4);
		if(c%2 == 0){
		*(mp + count) = lsn;
	/*	printf("In array %d\n", *(mp + count));
		printf("Count is %d\n", count);*/
		count++;
/*		printf("Count after increment is %d\n", count);*/
		}
		if(c%2 != 0){
		*(mp + count) = msn;
/*		printf("In array %d\n", *(mp + count)); */
		count++;l++;
		}

/*		printf("%.2X \(%X\) \(%X\)", (int)buffer[l], msn, lsn);
		 printf("\nin loop %d  %d\n", c, c%6);*/
                if ((count == 11) || (c == fileLen*2 - 1)) {
/*                        printf(" mp is \n");
                        for (i = 0; i < 11; i++)
                                printf("%d\t", mp[i]);*/
			encode( mp );
        		if(fencoded == NULL)
                		printf("failed to open file");
        		else{
                		for(i = 0;i < 15; i++){
                			printf("%d ",mp[i]);
                			fprintf(fencoded,"%d ",mp[i]);
	        		}
			}

                        printf("\n");
			count = 0;

                        for (i = 1; i < 11; i++)
                                *(mp + i) = 0;

                }


	}

	free(buffer);
}


