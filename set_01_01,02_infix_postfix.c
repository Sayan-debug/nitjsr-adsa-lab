#include <stdio.h>
#include <string.h>
char stack[100];
int top=-1;
void push(char c){
	stack[++top]=c;
}
char pop(){
	return stack[top--];
}
int precedence(char c){
	if(c=='+'||c=='-')return 1;
	else if(c=='*'||c=='/') return 2;
	else return 0;
}
void infixToPostfix(char infix[],char postfix[]){
	int i=0,j=0;
	//push('(');
	//strcat(infix,")");
	char symbol;
	// shift right to insert '(' at the beginning
    int len = strlen(infix);
    if(len < 98) { // leave space for both '(' and ')'
        for(int k = len; k >= 0; k--) {
            infix[k+1] = infix[k];
        }
        infix[0] = '(';
        infix[len+2] = '\0';
        infix[len+1] = ')';
    }
	while(infix[i]!='\0'){
		symbol=infix[i];
		if(symbol=='(')push(symbol);
		else if(symbol==')'){
			while(top!=-1&&stack[top]!='('){
				postfix[j++]=pop();
			}
			pop();
		}
		else if(symbol=='+'||symbol=='-'||symbol=='*'||symbol=='/'){
			while(top!=-1&&precedence(symbol)<=precedence(stack[top]))postfix[j++]=pop();
			push(symbol);
		}
		else postfix[j++]=symbol;
		i++;
	}
	postfix[j]='\0';
}

int evaluation(char postfix[]){
	int i=0;
	char symbol;
	while(postfix[i]!='\0'){
		symbol=postfix[i];
		if(symbol=='+'||symbol=='-'||symbol=='*'||symbol=='/'){
			int a=pop()-'0';
			int b=pop()-'0';
			switch(symbol){
				char res;
				case '+':
					res=(a+b)+'0';
					push(res);
					break;
				case '-':
					 res=(b-a)+'0';
					push(res);
					break;
				case '*':
					 res=(b*a)+'0';
					push(res);
					break;
				default:
					 res=(b/a)+'0';
					push(res);
			}
		}
		else push(symbol);
		i++;
	}
	return pop()-'0';
}
int main(){
	char infix[100];
    char postfix[100];
    int a = 1;
	printf("Enter the infix expression: ");
	scanf("%s",infix);
    while(a){
        printf("\n--- Infix to Postfix Expression ---\n");
        printf("1. Convert to postfix expression only\n2. Evaluate the infix expression\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);
		a=0;
		top=-1;
        infixToPostfix(infix,postfix);
        switch (choice)
        {
        case 1:
            printf("The postfix expression is : ");
            printf("postfix: %s\n",postfix);
            break;
        case 2:
            int res=evaluation(postfix);
			top=-1;
	        printf("Result of this expression : %d ",res);
            break;
		}
		
    }
	return 0;
}