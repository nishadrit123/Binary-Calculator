#include<stdio.h>
#include<stdlib.h>
#include "bc.h"

int isempty(stack* ptr){
  if(ptr->top==-1){
    return 1;
  }
  else{
    return 0;
  }
}

stack* push(stack* s,node* val){
  if (isfull(s)){
    printf("stack overflow\n");
  }
  else{
  (s->top)++;
  s->arr[(s->top)]=val;
  }
  return s;
}

int isfull(stack* s){
  if(s->top==s->size-1){
    return 1;
  }
  else{  
    return 0;
  }
}

node* pop(stack* s){
    if (isempty(s)){
       printf("stack underflow\n");
    }
    else{
       node* val=s->arr[s->top];
       (s->top)--;
       return val;
    }
}

node* eval(char eq[], stack *s){
  int i=0;
  while (eq[i]!='\0'){
  
    if (eq[i]==' '){
      //continue;
      i++;
    }
    /*if (eq[i]>='0' && eq[i]<='9'){
      int num = eq[i]-'0';
      s=push(s,num);
    }*/
    else if (eq[i]=='+' || eq[i]=='-' || eq[i]=='*' || eq[i]=='/' || eq[i]=='^'){
      char opd=eq[i];
      node* num1 = pop(s);
      node* num2 = pop(s);
      node* val = cal(num1,num2,opd);
      s=push(s,val);
      i++;
    }
    else{
      node* h=NULL;
      while (eq[i]!=' '){
        h=append(h,eq[i]-'0');
        i++;
      }
      s=push(s,h);
    }
    //i++;
  }
  node* answer = pop(s);
  return answer;
}

node* cal(node* num1,node* num2,char opd){
  node* answ=NULL;
  if (opd=='+'){
    answ=addeval(num2,num1);
    return answ;
  }
  else if (opd=='-'){
    answ=evalsub(num2,num1);
    return answ;
  }
  else if (opd=='*'){
    answ=mul(num2,num1);
    return answ;
  }
  else if (opd=='/'){
    answ=divd(num2,num1);
    return answ;
  }
  else if (opd=='^'){
    answ=power(num2,num1);
    return answ;
  }
}

node* append(node* h,int val){
  node* qptr;
  
  if (h==NULL){
    h=(node*)malloc(sizeof(node));
    h->data=val;
    h->next=NULL;
    h->prev=NULL;
    qptr=h;
  }
  else{
    node* ptr=qptr;
    ptr->next=(node*)malloc(sizeof(node));
    ptr=ptr->next;
    ptr->data=val;
    ptr->next=NULL;
    ptr->prev=qptr;
    qptr=qptr->next;
  }
  return h;
}

node* add(node*h1,node*h2){
  node* h3=NULL;
  node* ptr1=h1;
  node* ptr2=h2;
  while (ptr1->next!=NULL){
    ptr1=ptr1->next;
  }
  while (ptr2->next!=NULL){
    ptr2=ptr2->next;
  }
  int carry=0;
  while (ptr1!=NULL || ptr2!=NULL){
  //for (int i=0;i<2;i++){
    int total=ptr1->data+ptr2->data+carry;
    int sum=total%10;
    carry=total/10;
    h3=ins(h3,sum);
    ptr1=ptr1->prev;
    ptr2=ptr2->prev;
  }
  if (carry!=0){
    h3=ins(h3,carry);
  }
  return h3;
}

node* ins(node* h,int val){
  if (h==NULL){
    h=(node*)malloc(sizeof(node));
    h->data=val;
    h->next=NULL;
    h->prev=NULL;
  }
  else{
    node*p=h;
    node*q=p;
    p->prev=(node*)malloc(sizeof(node));
    p=p->prev;
    p->data=val;
    p->next=q;
    p->prev=NULL;
    q=q->prev;
    h=p;
  }
  return h;
}

int zero(node*h1,node*h2){
  if (sz(h1)==sz(h2)){
    return 1;
  }
  return 0;
}

int sz(node *h1){
  int i=0;
  while (h1!=NULL){
    i++;
    h1=h1->next;
  }
  return i;
}

node* addzero(node*h1,node*h2){
  if (sz(h1)>sz(h2)){
    while (sz(h2)!=sz(h1)){
      h2=ins(h2,0);
    }
    return h2;
  }
  else{
    while (sz(h1)!=sz(h2)){
      h1=ins(h1,0);
    }
    return h1;
  }
}

node* addeval(node* h1,node*h2){
  node* h3=NULL;
  if (sz(h1)==sz(h2)){
    h3=add(h1,h2);
  }
  else if (sz(h1)>sz(h2)){
    h2=addzero(h1,h2);
    h3=add(h1,h2);
  }
  else{
    h1=addzero(h1,h2);
    h3=add(h1,h2);
  }
  return h3;
}

int trav(node*h){
  while(h!=NULL){
    printf("%d",h->data);
    h=h->next;
  }
  printf("\n");
}

node* minus(node*h1,node*h2){
  node* h3=NULL;
  
  node* ptr1=h1;
  node* ptr2=h2;
  while (ptr1->next!=NULL){
    ptr1=ptr1->next;
  }
  while (ptr2->next!=NULL){
    ptr2=ptr2->next;
  }
  int borrow=0,sub;
  int dif;
  while (ptr1!=NULL || ptr2!=NULL){
   if (ptr1!=NULL && ptr2!=NULL){
    if (ptr1->data > ptr2->data){
      sub=ptr1->data-ptr2->data-borrow;
      //h3=ins(h3,sub);
      ptr1=ptr1->prev;
      ptr2=ptr2->prev;
      borrow=0;
    }
    else if (ptr1->data == ptr2->data && borrow ==0){
      sub=ptr1->data-ptr2->data-borrow;
      //h3=ins(h3,sub);
      ptr1=ptr1->prev;
      ptr2=ptr2->prev;
      borrow=0;
    }
    else if (ptr1->data == ptr2->data && borrow ==1){
      sub=10+ptr1->data-ptr2->data-borrow;
      //h3=ins(h3,sub);
      ptr1=ptr1->prev;
      ptr2=ptr2->prev;
      borrow =1;
    }
    else if (ptr1->data < ptr2->data) {
      sub = 10+ptr1->data-ptr2->data-borrow;
      //h3=ins(h3,sub);
      ptr1=ptr1->prev;
      ptr2=ptr2->prev;
      borrow=1;
    }
   } 
   else if (ptr1!=NULL && ptr2==NULL){
     if (ptr1->data>=1){
       sub=ptr1->data-borrow;
       //h3=ins(h3,sub);
       ptr1=ptr1->prev;
       borrow=0;
     }
     else if (ptr1->data=0 && borrow==0){
       sub=ptr1->data-borrow;
       //h3=ins(h3,sub);
       ptr1=ptr1->prev;
     }
     else{
       sub=10+ptr1->data-borrow;
       //h3=ins(h3,sub);
       ptr1=ptr1->prev;
       borrow=1;
     }
   }
   h3=ins(h3,sub);
   //h3=remzero(h3);
  }
  h3=remzero(h3);
  return h3;
}

node* remzero(node* h){
  //node* ptr=h;
  while (h->data==0 && h->next!=NULL){
    h=das(h);
    
  }
  /*if (h==NULL){
    h=(node*)malloc(sizeof(node));
    h->data=0;
    h->next=NULL;
    h->prev=NULL;
  }*/
  return h;
}

int great(node*h1,node*h2){
  if (sz(h1)>sz(h2)){
    return 1;
  }
  else if (sz(h1)<sz(h2)){
    return 0;
  }
  else{
    int f=0;
    node* p=h1;
    node* q=h2;
    while (p!=NULL && q!=NULL){
      if (p->data > q->data){
        f= 1;
        break;
      }
      else if (p->data < q->data){
        f=0;
        break;
      }
      else{
        f=1;
      }
      p=p->next;
      q=q->next;
    }
    if (f==1){
      return 1;
    }
    return 0;
  }
}

node* das(node*h){
  if (h->next!=NULL){
   node* ptr=h;
   h=h->next;
   h->prev=NULL;
   //node* sptr=h->next;
   //sptr->prev=NULL;
   free(ptr);
   //h=sptr;
   return h;
  }
  else{
    h=NULL;
    return h;
  }
}

node* evalsub(node*h1,node*h2){
  node* h3=NULL;
  if (great(h1,h2)){
    h3=minus(h1,h2);
  }
  else{
    h3=minus(h2,h1);
    int x=h3->data;
    h3=das(h3);
    h3=ins(h3,-1*x);
    return h3;
  }
}

node* mul(node* h1,node*h2){
  node*h3=NULL;
  node* h=(node*)malloc(sizeof(node));
  /*h->data=0;
  h->next=NULL;
  h->prev=NULL;*/
  
  //node* ptr1=h1;
  node* ptr2=h2;
  /*while (ptr1->next!=NULL){
    ptr1=ptr1->next;
  }*/
  while (ptr2->next!=NULL){
    ptr2=ptr2->next;
  }
  int i=0;
  while (ptr2!=NULL){
    node*temp1=NULL;
    int x=ptr2->data;
    int carry=0;
    node* ptr1=h1;
    while (ptr1->next!=NULL){
      ptr1=ptr1->next;
    }
    node* temp=NULL;
    while (ptr1!=NULL){
      int ans=x*ptr1->data+carry;
      int rem=ans%10;
      temp=ins(temp,rem);
      carry=ans/10;
      ptr1=ptr1->prev;
    }
    if (carry!=0){
      temp=ins(temp,carry);
    }
    for (int k=0;k<i;k++){
      temp=insae(temp,0);
    }
    temp1=h3;
    h3=NULL;
    h3=addeval(temp1,temp);
    ptr2=ptr2->prev;
    i++;
  }
  return h3;
}

node* insae(node*h,int val){
  node* ptr= (node*)malloc(sizeof(node));
  node* sptr=h;
  while(sptr->next!=NULL){
    sptr=sptr->next;
  }
  sptr->next=ptr;
  ptr->next=NULL;
  ptr->data=val;
  ptr->prev=sptr;
  return h;
}

node* divd(node*h1,node*h2){
  node* x=h1;
  node* y=h2;
  node* i=NULL;
  node* one=NULL;
  i=(node*)malloc(sizeof(node));
  i->data=0;
  i->next=NULL;
  i->prev=NULL;
  one=(node*)malloc(sizeof(node));
  one->data=1;
  one->next=NULL;
  one->prev=NULL;
  /*char s1="0";
  char s2="1";
  i=create(i,s1);
  one=create(one,s2);*/
  while (great(x,y)){       
  x=evalsub(x,y);
  //trav(x);
  i=addeval(i,one);   
  }
  return i;
}


int equal(node* h1,node*h2){
  int f=0;
  node* p=h1;
  node* q=h2;
  if (sz(h1) != sz(h2)){
    return 0;
  }
  while (p!=NULL && q!=NULL){
    if (p->data==q->data){
      f=1;
    }
    else{
      f=0;
      break;
    }
    p=p->next;
    q=q->next;
  }
  if (f==1){
    return 1;
  }
  return 0;
}

node* power(node* h1,node*h2){
  node* h3=NULL;
  char *s1="0";
  node*i=NULL;
  i=create(i,s1);
  char *s2="1";
  node* ans=NULL;
  ans=create(ans,s2);
  char* s3="1";
  node* one=NULL;
  one=create(one,s3);
  
  while(!equal(i,h2)){
    ans=mul(ans,h1);
    //trav(temp3);
    i=addeval(i,one);
  }
  //temp3=h3;
  return ans;
}

node* create(node* h,char *s){
   h= (node*)malloc(sizeof(node));
   h->data=s[0]-'0';
   h->next=NULL;
   h->prev=NULL;
   node* p=h;
   int i=1;
   while (s[i]!='\0'){
     node*q=p;
     p->next=(node*)malloc(sizeof(node));
     p=p->next;
     p->data=s[i]-'0';
     p->next=NULL;
     p->prev=q;
     q=q->next;
     i++;
   }
   return h;
}

char* citp(char eq[],stack1 *s1,char *temp){
  int i=0, j=0;  // i for equation j for temp
  while (eq[i]!='\0'){
    if ((eq[i]=='+' || eq[i]=='-' || eq[i]=='*' || eq[i]=='/' || eq[i]=='^')){
      int new=precedence(eq[i]);
      int old=precedence(s1->arr[s1->top]);
      if (new>old){
        s1=push1(s1,eq[i]);  
        i++;
      }
      else{
          char z= pop1(s1);
          temp[j]=z;
          j++;
          temp[j]=' ';
          j++;          
      }        
    }
    else if (eq[i]=='(' || eq[i]=='[' || eq[i]=='{' || eq[i]=='<'){
      s1=push1(s1,eq[i]);  
      i++;
    }
    else if (eq[i]==')' || eq[i]==']' || eq[i]=='}' || eq[i]=='>'){
      char temp1=s1->arr[s1->top];
      if (temp1=='(' || temp1=='[' || temp1=='{' || temp1=='<'){
        char xyz=pop1(s1);
        i++;
      }
      else{
        char spec=pop1(s1);
        temp[j]=spec;
        j++;
        temp[j]=' ';
        j++;
      }
    }
    else if (eq[i]==' ' && (eq[i-1] =='+' || eq[i-1]=='-' || eq[i-1]=='*' || eq[i-1]=='/' || eq[i-1]=='^')){
      //temp[j]=eq[i];
      i++;
      //j++;
    }
   else if (eq[i]==' ' && (eq[i-1] =='(' || eq[i-1]=='[' || eq[i-1]=='{' || eq[i-1]=='<')){
      //temp[j]=eq[i];
      i++;
      //j++;
    }
    else if (eq[i]==' ' && (eq[i-1]!='+' || eq[i-1]!='-' || eq[i-1]!='*' || eq[i-1]!='/' || eq[i-1]!='^')){
      temp[j]=eq[i];
      i++;
      j++;
    }
    else{
     //if (eq[i+1]!=' '){
      temp[j]=eq[i];
      j++;
      i++;      
     //}
    }
  }
  temp[j]=' ';
  j++;
  while (!isempty1(s1)){
    int last=pop1(s1);
    temp[j]=last;
    j++;
    temp[j]=' ';
    j++;
  }
  temp[j]='\0';
  
  return temp;
  
  /*int k=0;
  while (temp[k]!='\0'){
    printf("%c ",temp[k]);
    k++;
  }*/
}

int precedence(char a){
  if (a=='^'){
    return 3;
  }
  else if (a=='*' || a=='/'){
    return 2;
  }
  else if (a=='+' || a=='-'){
    return 1;
  }
  return 0;
}

stack1* push1(stack1* s,char val){
  if (isfull1(s)){
    printf("stack overflow\n");
  }
  else{
  (s->top)++;
  s->arr[(s->top)]=val;
  }
  return s;
}

char pop1(stack1* s){
    if (isempty1(s)){
       printf("stack underflow\n");
    }
    else{
       char val=s->arr[s->top];
       (s->top)--;
       return val;
    }
}

int isempty1(stack1* ptr){
  if(ptr->top==-1){
    return 1;
  }
  else{
    return 0;
  }
}

int isfull1(stack1* s){
  if(s->top==s->size-1){
    return 1;
  }
  else{  
    return 0;
  }
}
