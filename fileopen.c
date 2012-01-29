/* In the name of Allah, the Merciful, the Compassionate */

/* A program to test fopen and FILE */

#include <stdio.h>

main()
{
	FILE *file;
	char *buffer;
	unsigned long fileLen;

	file = fopen(testbin, "rb");

	if(!file)
	{
		fprintf(stderr, "Unable to open file %s", testbin);
		return;
	}

	fseek(testbin, 0, SEEK_END);
	fileLen = ftell(file);

	fseek(testbin, 0, SEEK_SET);

	buffer =  (char *)malloc(fileLen + 1);

	if(!buffer)
	{
		fprintf(stderr, "Memory error");
		fclose(testbin);
		
		return;
	}

	fread(buffer, fileLen, 1, testbin);

	// Suspended in favor of K & R page 162
