/** 
Some Free Software License (no time to investigate yet)

Authored by
Madhukumar Seshadri

negative index were introduced 
with neg rhs - end of the string
with neg lhs - beginning of the string
usage needs to be thought through as there is
idea of making this behave like a splitter so that 
you can ask for both parts, just one part with 'a', 'l', 'r'
problem is 3 combos of this plus 4 combos of indexes 
yields to X possibilites .. no time to manage all at this point
**/

#include <stdio.h>
#include <stdlib.h>

#define ubyte unsigned char
#define byte char  
  
#define digits "0123456789"
#define sep ':'
#define VERBOSE 0

#define	ID_DIR	0040000			/* Directory.  */
#define	ID_CHAR_DEVICE	0020000	/* Character device.  */
#define	ID_BLOCK_DEVICE	0060000	/* Block device.  */
#define	ID_REGULAR_FILE	0100000	/* Regular file.  */
#define	ID_FIFO	0010000			/* FIFO.  */
#define	ID_SYMBOLIC_LINK	0120000	/* Symbolic link.  */
#define	ID_SOCK	ET	0140000	/* Socket.  */

int len(char* x) {
	int len=0; 
	while(*x++)  {  len++; }
	return len;
} 

void w(char* filename,char* bytes) { 
	FILE* f;
	f = fopen(filename,"w");
	printf("afile by name %s has been opened. it's handle is",filename);
	fwrite(bytes,len(bytes),1,f);
	//printf("whatever fwrite crapped out");
	fclose(f);
}

void copy(char *original, char* clone) { 
	while ((*clone++=*original++)); 
}

char* sub(char *str,unsigned long start,unsigned long end) {
	printf ("%s","future feature");  
}

int compare(char* x, char *y) {
	while (x) {
		if (*x++ != *y++) {
			return -1;
		}
	}
	return 1;
}

int contains(char *container,char*  x) {
	while (container) {
		if (*container++ == *x) { 
			if (compare(container,x)) { 
				return 1;
			}
		}
	}
	return -1; 
}

int power(int x, int n) {
	int i;
	int o=1; 
	for (i=0;i<n;i++) 
		o = o * x;
	return o;
}

int _number(char x) {
	int i=-1;
        for (i=0;i<len(digits);i++) {
                if (x==digits[i]) return i;
        }
	return i;
}

int tonumber(char* str) { 
	int i,n=0,nofs,base=0;
	int strlen = len(str);
	int endat=-1;
	if (*str == '-') { 
		endat=0;
	}
    for (i=strlen-1;i>endat;i--) {
		nofs=_number(str[i]);
		//printf("i:%d digit:%d 10base:%d \n",i,nofs, base);
		n = n + power(10,base++) * nofs;
    }
	if (endat == -1)
	    return n;
	else
		return n*-1;
}

void slice (char* s,char* ask) {
	int i=0,from=0,to=len(ask);
	int fromblock=1;
	char *sfrom = malloc(to);
	char *sto = malloc(to);
	char *sf = sfrom; char *st = sto;
	//int *sfromo = (int *) sfrom;
	//int *stoo = (int *) sto;
	while(*ask) { 
		if (*ask == sep)  { 
			fromblock=0;
			ask++;
			continue; 
		}
		if (fromblock)  
			*sfrom++ = *ask++;
		else  
			*sto++ =*ask++;
	}

	if (VERBOSE) printf("from as string is %s to is %s\n",sf,st);

	char* sbegin = s; 

	if (fromblock)  { 
		// means ask was other than [:] and sf has the entire ask
		while (*s) {
			if (*s == *sf) { 
				printf("%c",' ');  
			} 
			else { 
				printf("%c",*s);
			}
			s++;
		}
		return;
	}


	if (len(st) == 0) { 
		to = len(s);
	}
	else { 
		to = tonumber(st);
	}

	if (len(sf) == 0) { 
		from=0;
	}
	else { 
		from = tonumber(sf);
	}

	if (VERBOSE) printf("from is %d to is %d\n",from,to);

	free(sf);
	free(st);

	int slen=len(s); 
	if (to < 0) {
		from = slen + to;
		to = slen;
	}
	if (from < 0) { 
		to = slen + from;
		from = 0;
	}
	for (i=from;i<to;i++) { 
		printf("%c",s[i]);
	}
}

void everyletter(char *s) {
	while (*s) { 
		printf("%c",*s++);
		if (*s)
			printf("%c",' ');
	}
}

void sizes() {
	//printf("Size of int: %x",sizeof(int));
	//printf("Size of float: %x",sizeof(float));
	//printf("Size of unsigned int: %x",sizeof(unsigned int));
	//printf("Size of long : %x",sizeof(long));
}

void main(int argc, char** argv) {
	int command=0; 
	char *str=NULL,*ask=NULL;

	if (argc < 2) { 
		printf("%s","Not enough arguments\n");
		printf("%s","Usage: slice astring from:to to get string sliced from to to\n");
		printf("%s","Usage: slice astring returns everyletter in string with space separation to use with shell for\n");
		return; 
	}
	if (argc > 1)
		str = argv[1];
	if (argc > 2)
		ask = argv[2];

	if (VERBOSE) printf("main:str is %s ask is %s\n",str,ask);
	//printf("calling w\n");
	//w(str,ask);

	if (argc == 2)
		everyletter(str);

	if (ask)
		slice (str,ask);

	return;
}
