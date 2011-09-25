// file: pk128.cpp
// date: 4/8/2005
// programmer: huey jiang    huey_jiang@hotmail.com
// this version was made basing on Alex Pukall's C version
// and tested on VC++ 6.0
// PC1 in 128-bits
/*
 *  pc1.cpp
 *  ppm5233
 *
 *  Adapted by Beau Johnston on 20/10/09.
 *  Copyright 2009 University Of New England. All rights reserved.
 *
 */

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>


class PukallCipher
{
public:
	
	unsigned short pkax,pkbx,pkcx,pkdx,pksi,pktmp,x1a2;
	unsigned short pkres,pki,inter,cfc,cfd,compte;
	unsigned short x1a0[8];
	unsigned char cle[17];
	short pkc, plainlen, ascipherlen;
	
	char *plainText, *ascCipherText;
	PukallCipher();
	void pkfin(void);
	void pkcode(void);
	void pkassemble(void);
	
	void ascii_encrypt128(const char *in, const char *key);
	void ascii_decrypt128(const char *in, const char *key);
};
