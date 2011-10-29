/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <turiyafy (AT) gmail(DOT)com> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return -- Kaustubh Pratap Chand
 * ----------------------------------------------------------------------------
 */

#define MAX 100
#include "globals.h"

struct tape{
    char value;
    struct tape *next;
    struct tape *prev;
    };

struct tape *current;
struct tape *first;

int stack[MAX];
int top=-1;

int push(int);
int pop();
int bf_run(char*,int);
void clearall(struct tape *);
struct tape * new_cell();
