/* Begin in the name of Allah, the Merciful, the Compassionate */

/* 
 * A header file to contain the Galois field operations, namely
 * addition, multiplication, division and conversion from index
 * form to decimal form and vice versa
 */


#define N 15	/* Block length of the code */
#define K 11	/* Number of Information Symbols */
#define M 4	/* Number of bits in symbol */
#define T 2

/* 
 * The lookup table for converting the Galois Field elements
 * from index form to decimal form and vice versa 
 */

int multitable[] = { 1, 2, 4, 8, 3, 6, 12, 11, 5, 10, 7,
	                                      14, 15, 13, 9 };

int inverse[] = { 0, 1, 9, 14, 13, 11, 7, 6, 15, 2, 12, 5,
						10, 4, 3, 8 };


int iinverse[] = { 0, 1, 9, 13, 15, 14, 7, 10, 5, 11, 12, 
					      6, 3, 8, 4, 2 };
/*int neginverse[] = { 1, 9, 14, 13, 11, 7, 6, 15, 2, 12, 5,
						10, 4, 3, 8 };*/

/* 
 * A function to convert the Galois Field elements from decimal
 * from to index form 
 */

int dec2ind(int decimal)
{

	int ih1;
	if (decimal == 0)	/* check for the zero element */
		return -1;
	
	/* Search through the lookup table */
	for (ih1 = 0; ih1 < (N+1); ih1++)
	{
		if (multitable[ih1] == decimal)
			return ih1;
		
	}
}


/* A function to convert the Galois filed elements from index 
 * form to decimal form 
 */

int ind2dec(int index)
{
	int i;
	if (index == -1) 	/*check t=for zero element */
		return -1;
	else
		return multitable[index];
}

/* 
 * fmulti: A function which accepts two finite field elements and returns
 * their product. Modulo arithmetic is used for multiplication.
 */

int fmulti(int a, int b)
{
	/* convert to index form */
	int ai = dec2ind(a);
	int bi = dec2ind(b);
	if ( ai == -1 || bi == -1)
		return 0;
	else
	{
	int prodi = (ai + bi)%15;	/* find the modulus of the sum */

	int prod = ind2dec(prodi);	/* convert back to decimal form */
	return prod;
	}
}

/* 
 * fadd: A function which accepts two finite field elements and returns
 * their sum. The input finite field element and the return are in decimal 
 * form
 */

int fadd(unsigned int s1, unsigned int s2)
{
	unsigned int c = s1^s2;
	return c;
}


int fdiv(int d1, int d2)
{
	int id2 = finv(d2);
	if (id2 == 0)
		return -1;
	int quotient = fmulti(d1, id2);
	return quotient;
}

/* finv: A fucnction to inverse a finite field element */



int finv(int src)
{
	return inverse[src];
}

int fiinv(int src)
{
	return iinverse[src + 1];
}
