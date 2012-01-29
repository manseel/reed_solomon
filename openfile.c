/* In the name of Allah, the Merciful, the Compassionate */

/* A program to test fopen and FILE */

#include <stdio.h>

main()
{
	FILE *file;
	char *buffer;
	//FILE 
	unsigned long fileLen;

	int c;

	//unsigned char lsn;
	unsigned char msn;
	unsigned char lsn;

	file = fopen("testbin", "rb");

	if(!file)
	{
		printf("Unable to open file ");
		return;
	}

	fseek(file, 0, SEEK_END);
	fileLen = ftell(file);

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

	for (c = 0; c < fileLen; c++)
	{
		//printf("%.2X ", (int)buffer[c]);
		msn =  (int)buffer[c] & 0x0F;
		lsn =  (int)buffer[c] & 0xF0;
		lsn = (lsn >> 4);
		//printf("%.2X \(%X\) \(%X\)", (int)buffer[c], msn, lsn);
		printf("%.2X \(%d\) \(%d\)", (int)buffer[c], msn, lsn);
		
		
		if (c % 4 == 3)
			printf (" ");

		if (c % 16 == 15)
		{
			printf("\n");
		}
		
	}

	free(buffer);
}

	
