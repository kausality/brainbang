/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <turiyafy (AT) gmail(DOT)com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return -- Kaustubh Pratap Chand
 * ----------------------------------------------------------------------------
 */
 
 
#include "bfvm.h"

int push(int data)
{
    if(top>=MAX-1){
        fputs("bfvm: Stack overflow!",stderr);
        exit(2);
    }

    stack[++top]=data;
    return 1;
}

int pop()
{
    if(top<0)
        return -1;

    return stack[top--];
}


struct tape *new_cell()
{
    struct tape *n;
    n=(struct tape*)malloc(sizeof (struct tape));
    if(!n){
        fputs("bfvm:Error allocating memory",stderr);
        exit(2);
    }

    n->value=0;
    n->next=0;
    n->prev=0;
    return n;
}

void clearall(struct tape *a)
{
    struct tape *b;
    while(a){
        b=a;
        a=a->next;
        free(b);
    }
}

int bf_run(char *buff,int size)
{
    char *code=buff;
    int idx=0,tmp;
    int nbrace=0;   /*counts the no. of loops encountered inside an unexcuted loop*/

    first=current=new_cell();


    while(idx<size){

        if(nbrace){
            if(code[idx]=='[')++nbrace;
            else if(code[idx]==']')--nbrace;
        }

        else{
            switch(code[idx]){
                case '+':
                    current->value++;
                    break;
                case '-':
                    current->value--;
                    break;
                case '>':
                    if(current->next==NULL){
                        current->next=new_cell();
                        (current->next)->prev=current;
                    }
                    current=current->next;
                    break;
                case '<':
                    if(current->prev==NULL){
                        first=current->prev=new_cell();
                        (current->prev)->next=current;
                    }
                    current=current->prev;
                    break;
                case '.':
                    putchar(current->value);
                    break;
                case ',':
                    current->value=getchar();
                    break;
                case '[':
                    //push(idx+1);
                    if(current->value==0)
                        ++nbrace;
                    else
                        push(idx+1);
                    break;
               case ']':
                    tmp=pop();
                    if(tmp!=-1){
                        if(current->value!=0){
                            push(tmp);
                            idx=tmp-1;   /*remember ++idx at the end of the loop?*/
                            break;
                        }
                    }

                    break;
            }
        }
        ++idx;
    }

    clearall(first);
}
