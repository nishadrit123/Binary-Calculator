typedef struct node{
  struct node* prev;
  int data;
  struct node* next;
}node;

typedef struct stack{
  int size;
  int top;
  node **arr;
}stack;

typedef struct stack1{
  int size;
  int top;
  char *arr;
}stack1;

int trav(node* h);
int isempty(stack* s);
stack* push(stack* s, node* val);
node* pop(stack* s);
int isfull(stack* s);
node* eval(char eq[], stack *s);
node* cal(node* num1,node* num2,char opd);
node* append(node* h,int val);
node* add(node*h1,node*h2);
node* ins(node* h,int val);
int zero(node*h1,node*h2);
int sz(node*h1);
node* addzero(node*h1,node*h2);
node* addeval(node* h1,node*h2);
node* minus(node*h1,node*h2);
node* remzero(node* h);
int great(node*h1,node*h2);
node* das(node* h);
node* evalsub(node*h1,node*h2);
node* mul(node* h1,node*h2);
node* insae(node*h,int val);
node* divd(node*h1,node*h2);
int equal(node* h1,node*h2);
node* power(node* h1,node*h2);
node* create(node* h,char *s);
char* citp(char eq[],stack1 *s1,char *temp);  // Calculate infix to postfix
int precedence(char a);
stack1* push1(stack1* s1, char val);
char pop1(stack1* s1);
int isfull1(stack1* s1);
int isempty1(stack1* s1);
