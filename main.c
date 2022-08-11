#include<stdio.h>
#include<stdlib.h>
#include "bc.h"

int main(){

  //char eq[]="[ ( 46784972415 + 2467849 ) * 243784975 / 406074955073233400 ] ^ 20 - 42797845734784915315478467897944";
  //char eq[]="[ ( 46784972415 + 2467849 ) - 243784975 * { 2134879467 - 24879 } / 347472364215300 ] ^ 8";
  //char eq[]="{ 48794 ^ 6 + 14678497540 } * 147895 / 9682768333589507368114205784 - 6487947547819024718794"
  //4879461672410 + 98497542187964510 * 478497410 - 4784978454067849784057849
  //[ { ( 87945794810457948 - 17945784679481 ) + 7879467840127948024 } * 2879450 / 51713369774450995024789 ] ^ 19
  printf("Enter the infix expression :\n");
  char eq[100];
  scanf("%[^\n]%*c",eq);
  int sz=sizeof(eq)/sizeof(char);
  char temp[100];
  
  stack *s=(stack*)malloc(sizeof(stack));
  s->size=1000;
  s->top=-1;
  s->arr=(node**)malloc(s->size*sizeof(node*));  
  
  stack1 *s1=(stack1*)malloc(sizeof(stack1));
  s1->size=100;
  s1->top=-1;
  s1->arr=(char*)malloc(s1->size*sizeof(char));  
 
  char* final=citp(eq,s1,temp);
  node* answer = eval(final,s);
  printf("Postfix evaluation result is :\n");
  trav(answer);
  
  return 0;
}
