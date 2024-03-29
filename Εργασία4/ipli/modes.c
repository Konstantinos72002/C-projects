#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "func.h"
int all_modes(treeptr *var_tree,listptr *line_list,int line_num,int *m_tabs,int *condition_line,listptrc *condition_list,int ln,int *arguement_array,int arg_s)
{  
    //condition_print(*condition_list);
    listptr *ptr;
    listptrc *ptrc;
    ptrc = condition_list;
    ptr = line_list;
    while((*ptr)->line_num != line_num) ptr = &(*ptr)->next;
    if(*ptr == NULL) return 1;
    char **mode; 
    int i=-1, j=0,c_tabs=0;
    if(NULL == (mode = malloc(10*sizeof(char*)))) 
    {
        printf("%d: memory error\n",line_num);
        return 0;
    }
    for(i=0;i<10;i++) 
        if(NULL == (*(mode+i) = malloc(100*sizeof(char))))
        {
            printf("%d: memory 2 eroor\n",line_num);
            return 0;
        }
        i=-1;
        while((*ptr)->line[i] != '\n' || i == -1)
        {
            i++;
            *(mode+j) = mode_recognise((*ptr)->line,&i);
            j++;
        }
        c_tabs = count_tabs((*ptr)->line);
        if(c_tabs > *m_tabs) //c_tabs > *m_tabs
        {
            printf("%d: Incorrect alignment\n",line_num);
            exit(1);
        }
        if(c_tabs == *m_tabs)
        {
            if(!strcmp(*mode,"while"))
            {
               /* int condition = condition_mode(mode,j,line_num,var_tree),cond;
                add_condition(condition_list,condition,line_num,m_tabs);
                if(condition == -1) return 0;
                else if(condition)
                {
                    (*m_tabs)++;
                    *condition_line = get_condition(*ptrc,&cond);
                    ptr = &(*ptr)->next;
                    return line_num;
                }
                else
                {                    
                    cond_0(*ptrc,c_tabs);
                    delete_condition(condition_list,m_tabs);
                    int a = c_tabs;
                    line_num++;
                    ptr = &(*ptr)->next;
                    if(*ptr == NULL && *m_tabs != 0)
                            {
                                line_num = get_condition_by_tabs(*condition_list,*m_tabs);
                                return line_num;
                            }
                    c_tabs = count_tabs((*ptr)->line);
                    printf("all good\n");
                    while(c_tabs > a)
                    {
                        line_num++;
                        ptr = &(*ptr)->next;
                        if(*ptr == NULL && *m_tabs != 0)
                            {
                                line_num = get_condition_by_tabs(*condition_list,*m_tabs);
                                return line_num;
                            }
                        c_tabs = count_tabs((*ptr)->line);
                    }
                    *condition_line = get_condition(*ptrc,&cond);
                    *m_tabs = get_tabs(*ptrc,*condition_line);
                    return --line_num;
                }*/;
            }
            else if(!strcmp(*mode,"if"))
            {
                (*m_tabs)++;
                int condition = condition_mode(mode,j,line_num,var_tree);
                if(condition == -1) return 0;
                else if(condition)
                {
                    ptr = &(*ptr)->next;
                    c_tabs = count_tabs((*ptr)->line);
                    return line_num;
                }
                else
                {
                    int a = c_tabs;
                    ptr = &(*ptr)->next;
                    if(*ptr == NULL) return line_num;
                    c_tabs = count_tabs((*ptr)->line);
                    while (c_tabs > a)
                    {
                        line_num++;
                        ptr = &(*ptr)->next;
                        if(*ptr == NULL) return line_num;
                        c_tabs = count_tabs((*ptr)->line);
                    }
                    return line_num;
                }
            }
            else if(!strcmp(*mode,"write"))
            {
                if (!write_func(mode,var_tree,line_num,j,0)) return 0;
            }
            else if(!strcmp(*mode,"writeln"))
            {
                if (!write_func(mode,var_tree,line_num,j,1)) return 0;
            }
            else if(!strcmp(*mode,"read"))
            {
                if(!read_func(*(mode+1),var_tree,line_num,j)) return 0;
            }
            else if(!strcmp(*mode,"argument") && !strcmp(*(mode+1),"size"))
            {
                if(!argument_1(mode,var_tree,line_num,j,arg_s,arguement_array)) return 0;
            }
            else if(!strcmp(*mode,"argument"))
            {
                if(!argument_2(mode,var_tree,line_num,j,arg_s,arguement_array)) return 0;;
            }
            else if(!strcmp(*mode,"random"))
            {
                if(!rand_func(mode,var_tree,line_num,j)) return 0;
            }
            else 
            {
                if(!variable_mode(mode,var_tree,line_num,j)) return 0;
            }
        }
        else
        {
            (*m_tabs)--;
            return line_num-1;
        }
        return line_num;
}