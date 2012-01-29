/* In the name of Allah, the Merciful, the Compassionate */

/* 
 * A program to encode a message with Reed-Solomon coding technique
 * 
 * Date: 13-April-2011
 * Version: 0.1_alpha
 *
 * The code specification adopted is (15,11) with 
 * 
 * n = 15 (Block length of the code)
 * k = 11 (Number of Information Symbols in the code)
 * t = 2 = (n - k) / 2; where t is the number of Symbol Errors that can 
 * be corrected
 *
 * m = 4 (Number of bits in the symbol)
 * 
 * Since n = 15, the Code Generator Polynomial g(x) consists of n - k = 2t
 * factors.
 *
 * So the Generator Polynomial in our code is a polynomial with degree 4,
 * and the roots are 4 consecutive elements of the Galois field 2^4 (m = 4).
 * The Galois Field adopted in the implementation is based on the Field
 * Generator Prime Polynomial p(x) of degree m, ie 4.
 *
 * p(x) = x^4 + x + 1
 *
 * The consecutive elements are chosen to maximize the Hamming Distance of
 * the code.
 *
 * This implementation has chosen the four consecutive roots for g(x) as 
 * a^0 = ( 1 )
 * a^1 = ( 2 )
 * a^2 = ( 4 )
 * a^3 = ( 8 )
 *
 * The Generator Polynomial g(x) = x^4 + 15x^3 + 3x^2 + x + 12
 * ie, the coefficients are 1, 15, 3, 1, 12
 *
 * Encoding Process: 
 *
 * Reed Solomon encoding is done by multiplying the Message Poly-
 * nomial m(x) of degree k - 1 with x^n-k, to accommodate n-k parity symbols.
 * In our implementation, the Message Polynomial m(x) is of degree 11, and 
 * there are 4 parity symbols. The parity symbols r(x) is the remainder ob-
 * tained when dividing the shifted m(x) with the Generatory Polynomial g(x)
 *
 * The co-effecients of the message polynomial m(x) are stored in the array
 * mp[11] and the code word is stored in array cw[15]. For testing purpose,
 * the co-effecients of the m(x) are entered manually.
 * The co-efficients chosen are 1 to 11
 */


/* 
 * The code is based on the pipelined version of division in page
 * number "12" of the BBC whitepaper. The Galois.h header file contains
 * the Galois field addition, multiplication, division, inversion etc
 * used throughout the different programs 
 */

#include <stdio.h>
#include "galois.h"


int gpoly[N + 1 - K] = { 1, 15, 3, 1, 12 }; /* Generator Polynomial coeffi
					       cients */
int mp [N];

void encode(int *mp)
{

	FILE *fileout;	/* The encoded output file */
	fileout = fopen("rscoded.rs", "w");

	/* Temporary array to store co-efficinets during division */
	int div[N];	 
	
	int *divindex;	/* A pointer to div[N] */
	divindex = &div[0]; 
	
	int pivot; 	/* A pivot during division */
	int i; 		/* Temporary variable for use as a count in loop */
	int rem; 	/* Temporary emainder obtained during division */
	int temp;
	printf("\n to be encoded ");
	for(i = 0; i < K; i++){
		mp[i] = *(mp + i);
		printf(" %d ",mp[i]);
	}
	printf("\n");

	/* Initialize div[N] with zeros */
	for (i = 0; i < N; i++)
		*(divindex+i) = 0;

	/* Initialize the message polynomial. This should be automatically */
	/*int mp[] = { 11, 2, 3, 14, 5, 6, 7, 8, 9, 10, 11 }; */

	/* The Galois Field division begins here */

	for (pivot = 0; pivot < K; pivot++) {

		rem = fadd(*(divindex + pivot), mp[pivot]);
	/*	printf ("pivot = %d\trem = %d\n",pivot,rem); */
		for(i = 1; i < (N + 1 - K); i++) {
			temp = fmulti(rem, gpoly[i]);
		/*	printf ("fprod = %d\n", temp); */
			div[pivot + i] = fadd(temp, div[pivot + i]);
		}
	}

	for ( i = K; i < N; i++)
		mp[i] = div[i];
	printf("encoded ");
	for ( i = 0; i < N; i++)
		printf(" %d ", mp[i]);
	printf("\n");
	for ( i = 0; i < N; i++)
		fputc(*(mp + i), fileout);


}

