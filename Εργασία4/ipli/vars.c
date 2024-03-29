#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

treeptr create_var(treeptr p,char *var)
{
    if(p == NULL)
    {
        p = malloc(sizeof(treeptr));
        p->var_name = malloc(sizeof(var));
        p->var_name = var;
        p->var_price = 0;
        p->left = NULL;
        p->right = NULL;
    }
    else if(!strcmp(p->var_name,var));
    else if(strcmp(p->var_name,var)<0) p->left = create_var(p->left,var);
    else if(strcmp(p->var_name,var)>0) p->right= create_var(p->right,var);
    return p;
}

treeptr put_var(treeptr p,char *var,int value)
{
    if(!strcmp(p->var_name,var)) p->var_price = value;
    else if(strcmp(p->var_name,var)<0) p->left = put_var(p->left,var,value);
    else if(strcmp(p->var_name,var)>0) p->right = put_var(p->right,var,value);
    return p;
}

void treeprint(treeptr p)
{
    if(p == NULL) return;
    else 
    {
        treeprint(p->left);
        printf("%s = %d\n",p->var_name,p->var_price);
        treeprint(p->right);
    } 
}

int get_value(treeptr p,char *name)
{
    if(!strcmp(p->var_name,name)) return p->var_price;
    else if(strcmp(p->var_name,name)<0) return get_value(p->left,name);
    else if(strcmp(p->var_name,name)>0) return get_value(p->right,name);
}

int var_exist(treeptr p,char *name)
{
    if(p == NULL) return 0;
    else if(!strcmp(p->var_name,name)) return 1;
    else if(strcmp(p->var_name,name)<0) return get_value(p->left,name);
    else if(strcmp(p->var_name,name)>0) return get_value(p->right,name);
}