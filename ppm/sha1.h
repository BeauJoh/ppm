/**!
 * @author	rannou_s
 * This implementation of SHA1 uses the first method defined in the RFC3174
 * http://www.faqs.org/rfcs/rfc3174.html
 * each variables defined here follows the convention used in the
 * document of reference, so let's have a look at it, it's well explained.
 */
/*
 *  sha1.cpp & h
 *  ppm5233
 *
 *  Adapted by Beau Johnston on 20/10/09.
 *  Copyright 2009 University Of New England. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long	ulong;
typedef unsigned int	uint;
typedef unsigned char	uchar;

typedef struct		sha1_s		/* sha1 structure */
{
	uint			w[80];		/* 16 + 64, used to compute */
	uint			h[5];		/* contains H0 H1 H2 H3 H4 H5*/
	uint			a[5];		/* contains A B C D E */
}			sha1_t;

#define	W(x)		sha1->w[x]
#define	H(x)		sha1->h[x]

#define	A		sha1->a[0]
#define	B		sha1->a[1]
#define	C		sha1->a[2]
#define	D		sha1->a[3]
#define	E		sha1->a[4]

static  uint sha1_op_left_shift(uint n, uint x);
static uint sha1_f(int t, sha1_t *sha1);
static uint sha1_k(int t);
static void sha1_compute_block(uchar *input, sha1_t *sha1);
static void sha1_initialize(sha1_t *sha1);
static void sha1_set_len(char *word, int len);
static  char * sha1_get_hash(sha1_t *sha1);
char * sha1_string(const char *input);

