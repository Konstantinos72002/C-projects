#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structs.h"
#include "func.h"

char* mode_recognise(char string[1000], int *p)
{
    int j=0;
    char *mode_string;                
    mode_string = malloc(100 * sizeof(char));                //100 max size of variable
    while (string[*p] == '\t') 
    {
        (*p)++;
    }
    while (string[*p] != ' ' && string[*p] != '\n' && string[*p] != '\0')    mode_string[j++] = string[(*p)++];
    mode_string[j] = '\0';
    return mode_string;
}

int count_tabs(char string[1000])
{
    int i=0,sum=0;
    while(string[i++] == '\t') sum++;
    return sum;
}

int vailable_names(char string[100])
{
    if(!strcmp(string,"while")) return 0;
    else if(!strcmp(string,"if")) return 0;
    else if(!strcmp(string,"else")) return 0;
    else if(!strcmp(string,"write")) return 0;
    else if(!strcmp(string,"writeln")) return 0;
    else if(!strcmp(string,"read")) return 0;
    else if(!strcmp(string,"argument")) return 0;
    else if(!strcmp(string,"random")) return 0;
    else if(!between_a_z_A_Z(string[0])) return 0;      //an o protos char einai diaforos apo a-z kai A-Z
    int i=1;
    while (string[i] != '\0') 
        if(!(between_a_z_A_Z((int)string[i]) || (int)string[i] == '_' || between_1_9((int)string[i]))) return 0;
        else i++;
    return 1;          //all good
}

int is_constant(char *string)
{
    int i=0,sum=0,g=1,c,s = strlen(string);
    for(c=0;c<s;c++) g*=10;
    while (string[i] != '\0')
    {
        if(between_1_9(string[i])) 
        {
            g=g/10;
            sum+=((int)string[i++]-48)*g;
            continue;
        }      
        return -1;
    }
    return sum;
}

void remove_spaces(char string[1000])
{
    int i=0,f_tabs=0,f_spaces=0,j,line_num=1;
    while(string[i] != '\n')
    {
        if(!f_spaces && string[i] == ' ')
        {
            for(j=i;string[j]!='\0';j++) string[j] = string[j+1];           //metafora tis simboloseiras mia thesi aristera
            continue;
        }
        if(!f_tabs && string[i] == '\t')             //ta tabs stin arxi ta prospernaei dioti metrane sti stoixisi
        {
            i++;
            f_spaces = 1;
            continue;
        }
        if(i)        //an den briksomaste sto proto char
        if(tab_or_space(string[i]) && tab_or_space(string[i-1]))     //tab_or_space(x) ((x) == '\t' || (x) == ' ')
            {                                                           //an brei keno h \t kai den einai gia diaxorismo leksis dld: while  x  eno while x den theme na bgalei to keno
                for(j=i;string[j]!='\0';j++) string[j] = string[j+1];           //metafora tis simboloseiras mia thesi aristera
                f_tabs = 1;
                continue;
            }
        f_tabs=1;
        f_spaces =1;
        i++;
    }
    if(tab_or_space(string[i-1])) for(j=i-1;string[j]!='\0';j++) string[j] = string[j+1];   //an to teleytaio stixeio einai keno h tab
}

int read_func(char *mode,treeptr *var_tree,int line_num,int j)
{
    int value;
    if(!(vailable_names(mode)))
    {
        printf("%d: I was waiting about a vailable variable name\n",line_num);
        return 0;
    }
    *var_tree = create_var(*var_tree,mode);
    scanf("%d",&value);
    put_var(*var_tree,mode,value);
}

int variable_mode(char **mode,treeptr *var_tree,int line_num,int j)
{
    int constant,value,value1,value2,operator,result;
    if(!vailable_names(*mode))
            {
                printf("%d: unavailable variable name\n",line_num);
                return 0;
            }       
            else                                //<var>
            {
                *var_tree = create_var(*var_tree,*mode);
                if(j>5 || j == 4)
                {
                    printf("%d: Incorrect Suntax :<var> = <varint> or <var> = <expression>\n",line_num);
                    return 0;
                }
                if(j == 3)
                {
                    if(strcmp(*(mode+1),"=")) 
                    {
                        printf("%d: I was waiting for the '=' character\n",line_num);
                        return 0;
                    }
                    if(**(mode+2) <'0' || **(mode+2) >'9')        //an o protos xaraktiras den einai noumero
                    {
                        if(!vailable_names(*(mode+2))) 
                        {
                            printf("%d: unavailable variable name\n",line_num);
                            return 0;
                        }
                        *var_tree = create_var(*var_tree,*(mode+2));
                        value = get_value(*var_tree,*(mode+2));
                        put_var(*var_tree,*mode,value);
                    }
                    else
                    {
                        constant = is_constant(*(mode+2));
                        if(constant < 0)
                        {
                            printf("%d: unavailavble varint\n",line_num);
                            return 0;
                        }
                        put_var(*var_tree,*mode,constant);
                    }
                }
                if(j == 5)
                {
                    if(strcmp(*(mode+1),"=")) 
                    {
                        printf("%d: I was waiting for the '=' character\n",line_num);
                        return 0;
                    } 
                    if(**(mode+2) <'0' || **(mode+2) >'9')
                    {
                        if(!vailable_names(*(mode+2))) 
                        {
                            printf("%d: unavailable variable name\n",line_num);
                            return 0;
                        }
                        *var_tree = create_var(*var_tree,*(mode+2));
                        value1 = get_value(*var_tree,*(mode+2));
                    }
                    else
                    {
                        constant = is_constant(*(mode+2));
                        if(constant < 0)
                        {
                            printf("%d: unavailavble varint\n",line_num);
                            return 0;
                        }
                        value1 = constant;
                    }
                    if(!operator_exist(*(mode+3)))
                    {
                        printf("%d: I was waiting for an operator: +, -, *, /, %c\n",line_num,'%');
                        return 0;
                    }
                    else
                    operator = **(mode+3);
                    if(**(mode+4) <'0' || **(mode+4) >'9')
                    {
                        if(!vailable_names(*(mode+4))) 
                        {
                            printf("%d: unavailable variable name\n",line_num);
                            return 0;
                        }
                        *var_tree = create_var(*var_tree,*(mode+4));
                        value2 = get_value(*var_tree,*(mode+4));
                    }
                    else
                    {
                        constant = is_constant(*(mode+4));
                        if(constant < 0)
                        {
                            printf("%d: unavailavble varint\n",line_num);
                            return 0;
                        }
                        value2 = constant;   
                    }
                    if(operator == '+') result = value1 + value2;
                    else if(operator == '-') result = value1 - value2;   
                    else if(operator == '*') result = value1 * value2;
                    else if(operator == '/') result = value1 / value2;
                    else result = value1 % value2;
                    put_var(*var_tree,*mode,result); 
                }
            }
            return 1;
}

int condition_mode(char **mode,int j,int line_num,treeptr *var_tree)
{
    int value1,constant,value2,result;
    char comporer[2];
    if(j != 4)
    {
        printf("%d: I was waiting while <varint1> <compoper> <varint2>\n",line_num);
        return -1;
    }
    else
    {
        if(**(mode+1) <'0' || **(mode+1) >'9')
        {
            if(!vailable_names(*(mode+1))) 
            {
                printf("%d: Unavailable variable name\n",line_num);
                return -1;
            }
            *var_tree = create_var(*var_tree,*(mode+1));
            value1 = get_value(*var_tree,*(mode+1));
        }
        else
        {
            constant = is_constant(*(mode+1));
            if(constant < 0)
            {
                printf("%d: unavailavble varint\n",line_num);
                return -1;
            }
            value1 = constant;
        }
        if(!comporer_exist(*(mode+2))) 
        {
            printf("%d: I was waiting for a comporer: ==, !=, <=, <, >=, >\n",line_num);
            return -1;
        }
        strcpy(comporer,*(mode+2));
        if(**(mode+3) <'0' || **(mode+3) >'9')
        {
            if(!vailable_names(*(mode+3))) 
            {
                printf("%d: unavailable variable name\n",line_num);
                return -1;
            }
            *var_tree = create_var(*var_tree,*(mode+3));
            value1 = get_value(*var_tree,*(mode+3));
        }
        else
        {
            constant = is_constant(*(mode+3));
            if(constant < 0)
            {
                printf("%d: unavailavble varint\n",line_num);
                return -1;
            }
            value2 = constant;
        }
    }
    if(!strcmp(comporer,"==")) result = value1 == value2;
    else if(!strcmp(comporer,"<=")) result = value1 <= value2;   
    else if(!strcmp(comporer,">=")) result = value1 >= value2;
    else if(!strcmp(comporer,"!=")) result = value1 != value2;
    else if(!strcmp(comporer,"<")) result = value1 < value2;
    else result = value1 > value2;
    return result;
}

int write_func(char **mode,treeptr *var_tree,int line_num,int j,int x)              //x == 0 write, x == 1 writeln
{
    if(j != 2)
    {
        printf("%d: I was waiting about: write <varint>\n",line_num);
    }
    int value;
    if(**(mode+1) <'0' || **(mode+1) >'9')        //an o protos xaraktiras den einai noumero
    {
        if(!vailable_names(*(mode+1)) ||  **(mode+1) == '-') 
        {
            printf("%d: unavailable variable name\n",line_num);
            return 0;
        }
        *var_tree = create_var(*var_tree,*(mode+1));
        value = get_value(*var_tree,*(mode+1));
    }
    else
    {
        value = is_constant(*(mode+1));
        if(value < 0)
        {
            printf("%d: unavailavble varint\n",line_num);
            return 0;
        }
    }
    if(!x) printf("%d",value);
    else printf("%d\n",value);
    return 1;
}

int rand_func(char **mode,treeptr *var_tree,int line_num,int j)
{
    if(j!=2) 
    {
        printf("%d: I was waiting about: random <var>",line_num);
        return 0;
    }
    if(!vailable_names(*(mode+1)))
    {
        printf("%d: Unavailable var name\n",line_num);
        return 0;
    }
    *var_tree = create_var(*var_tree,*(mode+1));
    srand(time(NULL));
    put_var(*var_tree,*(mode+1),rand());
}

int argument_1(char **mode,treeptr *var_tree,int line_num,int j,int narg_s,int *arguement_array)
{
    if(j != 3)
    {
        printf("%d: I was waiting about: argument size <var>\n",line_num);
        return 0;
    }
    if(!vailable_names(*(mode+2)))
    {
        printf("%d: Unavailable variable name\n",line_num);
        return 0;
    }
    *var_tree = create_var(*var_tree,*(mode+2));
    put_var(*var_tree,*(mode+2),narg_s);
    return 1;
}

int argument_2(char **mode,treeptr *var_tree,int line_num,int j,int narg_s,int *arguement_array)
{
    int value,constant;
    if(j != 3)
    {
        printf("%d: I was waiting about: argument <>> <var>\n",line_num);
        return 0;
    }
    if(**(mode+1) <'0' || **(mode+1) >'9')
        {
            if(!vailable_names(*(mode+1))) 
            {
                printf("%d: Unavailable variable name\n",line_num);
                return 0;
            }
            *var_tree = create_var(*var_tree,*(mode+1));
            value = get_value(*var_tree,*(mode+1));
        }
        else
        {
            constant = is_constant(*(mode+1));
            if(constant < 0)
            {
                printf("%d: unavailavble varint\n",line_num);
                return 0;
            }
            value = constant;
        }
        if(narg_s == 0 || value < 1 || value > narg_s)
        {
            if(value==1) printf("%d: the %dst argument do not exist\n",line_num,value);
            else printf("%d: the %dth argument do not exist\n",line_num,value);
            return 0;
        }
        if(!vailable_names(*(mode+2)))
        {
            printf("%d: Unavailable variable name\n",line_num);
            return 0;
        }
        *var_tree = create_var(*var_tree,*(mode+2));
        put_var(*var_tree,*(mode+2),*(arguement_array+narg_s-value));
}