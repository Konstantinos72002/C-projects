#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

void add_line(listptr *p,char *line, int line_num)
{ 
    while(*p != NULL) p = &((*p)->next);
    *p = malloc(sizeof(listptr));
    (*p)->line = malloc(strlen(line));
    strcpy((*p)->line,line);
    (*p)->line_num = line_num;
    (*p)->next = NULL;
}
void list_print(listptr p)
{ 
    while(p != NULL) 
    {
        printf("%d: %s",p->line_num,p->line);
        p = p->next;
    }
}
int t = 0;
void add_condition(listptrc *p,int cond,int line_num,int *tabs)
{ 
    while (*p != NULL)
    {
        if((*p)->line_num == line_num) break;
        p = &((*p)->next);
    }
    if (*p != NULL)
    {
        if((*p)->line_num == line_num)
        {
            (*p)->cond = cond;
        }
    }
    else
    {
        *p = malloc(sizeof(listptrc));
        (*p)->cond = cond;
        (*p)->line_num = line_num;
        (*p)->next = NULL;
        (*p)->tabs = ++t;
        *tabs = (*p)->tabs;
    }
}
int get_condition(listptrc p,int *cond)
{
    if(p == NULL) return 0;
    int temp = p->line_num;
    *cond = p->cond;
    while ((p = p->next) != NULL) 
    {
        temp = p->line_num;
        *cond = p->cond;
    }
    return temp;       
}
void delete_condition(listptrc *p,int *tabs)
{ 
    while(*p != NULL)
    {
        if(!((*p)->cond))
        {
            t--;
            *tabs = t;
            *p = NULL;
            break;
        }
        p = &(*p)->next;
    }
}
void condition_print(listptrc p)
{   
    while(p != NULL) 
    {
        printf("%d: %d,tabs = %d\n",p->line_num,p->cond,p->tabs);
        p = p->next;
    }
}

int get_condition_by_tabs(listptrc p,int tabs)
{
    
    while(p != NULL) 
    {
        if(p->tabs == tabs) 
            return p->line_num;
        p = p->next;
    }
}

int get_tabs(listptrc p,int ln)
{
    while(p !=NULL)
    {
        if(p->line_num == ln)
            return p->tabs;
        p = p->next;
    }
}

void cond_0(listptrc p,int tabs)
{
    while (p != NULL)
    {
        if(p->tabs == tabs) 
        {
            p->cond = 0;
        }
        p = p->next;
    }
}