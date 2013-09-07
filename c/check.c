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
*/

#define __STDIO__ 1	//if 0, make sure VERBOSE is 0
#define VERBOSE 0
 
#ifdef __STDIO__
#include <stdio.h>
#endif

#include "str.h"
#include "number.h"
#include "parse.h"

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
	*/
	sequence seq;
	char* wb = " \t\n";

	seq._w=malloc(len(argv[1]));
	seq.w = seq._w;
	
	while (parse(argv[1],wb,&seq) { 
		if (strcmp(seq.w,"in")) {
			addto(expression,0,seq.w);
			addto(expression,1,IN);
			in=1;
		}
		else if (strcmp(seq.w,"not") && !in) { 
			addto(expression,0,seq.w)
		}
		else if (strcmp(seq.w,"is")) { 
		}
		else if (strcmp(seq.w,"lesser")) { 
		} 
		else if (strcmp(seq.w,"greater")) { 
		} 
		else if (strcmp(seq.w,"than")) { 
		} 
		else if (strcmp(seq.w,"and")) { 
		} 
		else if (strcmp(seq.w,"or")) { 
		} 
	}
	//seq.w has last one

	free(seq.w);
}


	int i=0;
	int prog=1;
	char *lhs,*rhs,*op;
	int neq,in,geq,leq,gt,lt,nlt,ngt,eq,out,notin,nleq,ngeq,pass;
	eq=neq=in=geq=leq=gt=lt=nlt=ngt=notin=nleq=geq=0;pass=out=1;
	lhs=rhs=op=NULL;
	pass=1;

	if (VERBOSE) printf("No of arguments:%d\n",argc);
	if (VERBOSE) for (i;i<argc;i++) printf("arg%d:%s ",i,argv[i]);
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
