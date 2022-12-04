#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>
#include<math.h>

#define STACKSIZE 100
#define MAX STACKSIZE

struct stack{
	int top;
	char items[STACKSIZE];
};


void postfix(char *,char *);
int isoperand(char);
int empty(struct stack *);
void popandtest(struct stack *,char *,int *);
int prcd(char,char);
void push(struct stack *,char);
char pop(struct stack *);

double eval(char []);

int main(void)
{
	char infx[MAX]; /* infix string */
	char pstfx_str[MAX]; /* postfix string */
	int pos = 0;

	printf("Enter the infix string:\n");

	/* get infx[] */
	while ((infx[pos++] = getchar()) != '\n' && pos < (MAX - 1))
		;
	if ( infx[pos - 1] == '\n')
		infx[--pos] = '\0';
	else
		infx[pos] = '\0';
	/*end get infx[] */

	/*convert infx[] to pstfx_str[] */
	postfix(infx,pstfx_str);
	
	printf("the original infix string is %s\n",infx);
	printf("the converted postfix string is %s\n",pstfx_str);

	printf("\n%f\n",eval(pstfx_str));
}

void postfix(char infx[],char pstfx_str[])
{
	char topsymb,symb;
	int in_pos=0,pst_pos=0,und;
	struct stack opstk;
	opstk.top = -1;

	for (/*while not end of infix*/; (symb = infx[in_pos]) != '\0'; ++in_pos)
		if (isoperand(symb)) /*symbol is an operand */
			pstfx_str[pst_pos++]=symb;
		else {
			popandtest(&opstk,&topsymb,&und);
			while (!und && prcd(topsymb,symb)){
				pstfx_str[pst_pos++] = topsymb;
				popandtest(&opstk,&topsymb,&und);
			}

			if(!und)
				push(&opstk,topsymb);
			if (und || (symb != ')'))
				push(&opstk,symb);
			else /*pop the '(' and discard it */
				topsymb = pop(&opstk);
		}
	/* append any remaining operators to the pstfx_str */
	while (!empty(&opstk))
		pstfx_str[pst_pos++] = pop(&opstk);
	pstfx_str[pst_pos] = '\0';
	return;
}

/* isoperand: returns true if operand */
int isoperand(char symb)
{
	return isalnum(symb);
}

/* popandtest: pops the stack and returns and indication for underflow */
void popandtest(struct stack *ps,char *px,int *pund)
{
	if (empty(ps)){
		*pund = true;
		return;
	}
	*pund = false;
	*px = ps->items[ps->top--];
	return;
}

/* empty: returns true if the stack is empty */
int empty(struct stack *ps)
{
	if (ps->top == -1)
		return true;
	return false;
}

/* prcd: returns true if op1 > op2 */
int prcd(char op1,char op2)
{
	int OP1,OP2;
	if (op1 != ')'&& op1 != '(' && op2 != ')' && op2 != '(')
	{
		switch(op1)
	{
		case '$': OP1 = 3;
			  break;
		case '*':
		case '/': OP1 = 2;
			       break;
		case '+':
		case '-': OP1 = 1;
			       break;
	}
	switch(op2)
	{
		case '$': OP2 = 3;
			  break;
		case '*':
		case '/': OP2 = 2;
			       break;
		case '+':
		case '-': OP2 = 1;
			       break;
	}

	if (OP1>= OP2 && OP2 != 3)
		return true;
	if (OP1<OP2 || OP2 == 3)
		return false;
	}
	else
	{
		if(op1 == '(' )
			return false;
		if (op2 == '(' && op1 != ')')
			return false;
		if (op2 == ')' && op1 != '(')
			return true;
		if (op1 == ')')
			printf("op1 = )\nYou donot push ')' onto the opstk\n");
	}
}

/* push: inserts x into the stack */
void push(struct stack *ps,char x)
{
	ps->items[++(ps->top)] = x;
	return;
}

/* pop: removes and returns the top element from stack */
char pop(struct stack *ps)
{
	if (empty(ps)){
		printf("stack underflow\n");
		exit(1);
	}
	return(ps->items[ps->top--]);
}

/*-----------evaluating postfix expression------------*/

struct STACK{
	int top;
	double items[STACKSIZE];
};

double POP(struct STACK *);
void PUSH(struct STACK *,double);
double oper(int,double,double);
int EMPTY(struct STACK *);

/* eval: evaluate the postfix expression */
double eval(char expr[])
{
	struct STACK opndstk;
	int c,pos;/* int is also a signed char 
		     char c ; is also fine
		     but int c is prefered,find
		     out why?????
		     */
	double opnd1,opnd2,val;

	opndstk.top = -1;

	for(pos=0;(c = expr[pos]) != '\0'; ++pos)
		if (isdigit(c))
			/* operand-- convert the character representation */
			/* of the digit into double and push it onto */
			/* the stack */
			PUSH(&opndstk,(double) (c - '0'));
		else
		{
			/* operator */
			opnd2 = POP(&opndstk);
			opnd1 = POP(&opndstk);
			val = oper(c,opnd1,opnd2);
			PUSH(&opndstk,val);
		}
	return (POP(&opndstk));
}

double POP(struct STACK *ps)
{
	if (EMPTY(ps)){
		printf("stack underflow\n");
		exit(1);
	}
	return (ps->items[ps->top--]);
}

void PUSH(struct STACK *ps,double x)
{
	if (ps->top == STACKSIZE-1){
		printf("stack overflow\n");
		exit(1);
	}
	else
		ps->items[++(ps->top)]=x;
	return;
}

double oper(int symb,double op1,double op2)
{
	switch(symb)
	{
		case '+': return (op1 + op2);
		case '-': return (op1 - op2);
		case '*': return (op1 * op2);
		case '/': return (op1/op2);
		case '$': return (pow(op1,op2));
		default: printf("Illegal Operation\n");
			 exit(1);
	}
}

int EMPTY(struct STACK *ps)
{
	if (ps->top == -1)
		return true;
	return false;
}
