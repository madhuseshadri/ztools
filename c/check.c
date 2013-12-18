/*
Copyright (c) Madhukumar Seshadri
without mincing words idea is copycat of test as shell needs expressions evaluator
shell is busy piping, subshelling, expanding and it needs help .. thus 
capabilities are different and so is the implementation
-- didn't like the syntax, hence this
file / node capabilites of test need to be included 
-- mknod .. check
{ eq | is } { neq | is not } { in | not in } { geq equalorgreaterthan } 
{ ngeq | leq equalorlesserthan | nleq | gt greaterthan | ngt | lt lessthan | nlt } 

gcc -o check check.c - will get you the binary for using 

This is better than saying -z -n etc .. 

*/
#define __STDIO__ 1	//if 0, make sure VERBOSE is 0
#define VERBOSE 0
 
#ifdef __STDIO__
#include <stdio.h>
#endif

#define digits "0123456789"

/*
Todo if you remove printf stdio.h dependency is gone
Todo - cpu specific datatypes for 32bit and 64 bit will be needed to tonumber
we have it as int but it need to be unsigned 64bit 0-2**64 for positive integers
2**63 for singed integers and 32 for 32 bit system
*/

int len(const char* x) {
	int len=0; 
	while(*x++)   len++; 
	return len;
}

int cmp(const char *x, const char *y) {
	int i=0;
	int xlen=len(x); 
	int ylen=len(y); 
	if (xlen != ylen) return 0; 
	for (i=0;i<xlen;i++) { 
		if (x[i] != y[i]) return 0; 
	}
	return 1; 
}

void copy(char *original, char* clone) { 
	while ((*clone++=*original++)); 
}

int power(int x, int n) {
	int i;
	int o=1; 
	for (i=0;i<n;i++) 
		o = o * x;
	return o;
}

int _number(char x) {
	int i;
        for (i=0;i<len(digits);i++) {
                if (x==digits[i]) return i;
        }
	return i;
}

int tonumber(char* str) { 
	int i,n=0,nofs,base=0;
	int stop=-1;
	int strlen = len(str);
	if (*str == '-') 
		stop=0;
        for (i=strlen-1;i>stop;i--) {
		nofs=_number(str[i]);
		//printf("i:%d digit:%d 10base:%d \n",i,nofs, base);
		n = n + power(10,base++) * nofs;
        }
	if (stop==0)  n=n*-1;  
        return n;
}

int main(int argc, char** argv) {
	/* if eval 
		something is something = treat as string, 3 + prog
		something is not something - treat as string, 4 + prog
		something is greater than something - treat as integer,	5 + prog
		something is lesser than something - treat as integer, 5 
		something is greater than or equal to something - treat as integer, 8 + prog
		something is lesser than or equal to something, 8 
		something is in something, 4
		something is not in something, 5 + prog

		eq | is 
		neq | is not 
		in
		not in 
		geq equalorgreaterthan
		ngeq 
		leq equalorlesserthan 
		nleq
		gt greaterthan
		ngt
		lt lessthan
		nlt
	*/
	int i=0;
	int prog=1;
	char *lhs,*rhs,*op;
	int neq,in,geq,leq,gt,lt,nlt,ngt,eq,out,notin,nleq,ngeq,pass;
	eq=neq=in=geq=leq=gt=lt=nlt=ngt=notin=nleq=geq=0;pass=out=1;
	lhs=rhs=op=NULL;
	pass=1;

	if (VERBOSE) printf("No of arguments:%d\n",argc);
	if (VERBOSE) for (i=0;i<argc;i++) printf("arg%d:%s ",i,argv[i]);
	if (VERBOSE) printf("%s","\n");

	//-- nasty code below 
	if (argc < prog + 3) { return out; }

	if (cmp(argv[2],"in")) {
		in=1;
	}
	else if (cmp(argv[2],"not") && cmp(argv[3],"in")) { 
		notin=1;
	}
	else if (argc == prog + 3) { 
		if (cmp(argv[2],"is"))
			eq=1;
	}
	else if (argc == prog + 4)  {
		if (cmp(argv[2],"is")  && cmp(argv[3],"not"))
			neq=1;
	}
	else if (argc == prog + 5) {
		if (cmp(argv[3],"lesser")) 
			lt=1;
		else 
			gt=1;
	}
	else if (argc == prog + 6) {
		if (cmp(argv[4],"lesser")) 
			nlt=1;
		else  
			ngt=1;
	}
	else if (argc == prog + 8) {
		if (cmp(argv[3],"lesser")) 
			leq=1;
		else  
			geq=1;
	}
	else if (argc == prog + 9) {
		if (cmp(argv[4],"lesser"))  
			nleq=1;
		else  
			ngeq=1;
	}
	//-- nasty code above

	if(VERBOSE) printf("List of vars neq:%d eq:%d lt:%d gt:%d geq:%d leq:%d ngeq:%d nleq:%d in:%d notin:%d\n",\
				neq,eq,lt,gt,geq,leq,ngeq,nleq,in,notin);

	if (eq) {
		lhs=argv[1]; rhs=argv[3];
		if (VERBOSE) printf("eq:lhs:%s rhs:%s\n",lhs,rhs);
		if (cmp(lhs,rhs)) out=0;
	}
	else if (neq) {
		lhs=argv[1]; rhs=argv[4];
		if (VERBOSE) printf("neq:lhs:%s rhs:%s\n",lhs,rhs);
		if (!cmp(lhs,rhs)) out=0;
	}
	else if (in) { 
		for (i=3;i<argc;i++) {
			if (VERBOSE) printf("in:lhs:%s rhs:%s\n",argv[i],argv[1]);
			if (cmp(argv[i],argv[1])) { 
					out=0; 
					break;
			}
		}
	}
	else if (notin) { 
		out=0;
		for (i=4;i<argc;i++) {
			if (VERBOSE) printf("notin:lhs:%s rhs:%s\n",argv[i],argv[1]);
			if (cmp(argv[i],argv[1]))  { out=1; break; } 
		}
	}
	else if (gt) {
		lhs=argv[1]; rhs=argv[5];
		if (VERBOSE) printf("gt:lhs:%s rhs:%s\n",lhs,rhs);
		if (tonumber(lhs) > tonumber(rhs)) out=0;
	}
	else if (lt) {
		lhs=argv[1]; rhs=argv[5];
		if (VERBOSE) printf("lt:lhs:%s rhs:%s\n",lhs,rhs);
		if (tonumber(lhs) < tonumber(rhs)) out=0;
	}
	else if (ngt) {
		lhs=argv[1]; rhs=argv[6];
		if (VERBOSE) printf("gt:lhs:%s rhs:%s\n",lhs,rhs);
		if (!(tonumber(lhs) > tonumber(rhs))) out=0;
	}
	else if (nlt) {
		lhs=argv[1]; rhs=argv[6];
		if (VERBOSE) printf("lt:lhs:%s rhs:%s\n",lhs,rhs);
		if (!(tonumber(lhs) < tonumber(rhs))) out=0;
	}
	else if (geq) {
		lhs=argv[1]; rhs=argv[8];
		if (VERBOSE) printf("geq:lhs:%s rhs:%s\n",lhs,rhs);

		if (tonumber(lhs) >= tonumber(rhs)) out=0;
	}
	else if (leq) {
		lhs=argv[1]; rhs=argv[8];
		if (VERBOSE) printf("leq:lhs:%s rhs:%s\n",lhs,rhs);
		if (tonumber(lhs) <= tonumber(rhs)) out=0;
	}
	else if (ngeq) {
		lhs=argv[1]; rhs=argv[9];
		if (VERBOSE) printf("not geq:lhs:%s rhs:%s\n",lhs,rhs);
		if (!(tonumber(lhs) <= tonumber(rhs))) out=0;
	}
	else if (nleq) {
		lhs=argv[1]; rhs=argv[9];
		if (VERBOSE) printf("not leq:lhs:%s rhs:%s\n",lhs,rhs);
		if (!(tonumber(lhs) <= tonumber(rhs))) out=0;
	}
	else { out=1; } 
	
	if (VERBOSE) printf("%d\n",out);
	return out;
}
