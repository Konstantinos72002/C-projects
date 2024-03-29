#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "func.h"

int main(int argc, char **argv)
{
    treeptr var_tree = NULL;
    listptr line_list = NULL;
    listptrc condition_list = NULL;
    FILE *ifp;
    char buf[1000],*start_of_comment,*end_of_file,**mode,operator; //ypothetoyme oti kathe grammi periexei mexri kai 1000 characters
    int i,j,value,value1,value2,result,ln=0;                                                              //100 max size of variables   
    if (argc<2)
    {
       printf("Incorrect syntax\n%s [-v] <iplfilename> [<arg1>] [<arg2>] ... [<argn>]\n",argv[0]);
       return -1;
    }
    int *arguements_array,k=0;
    if(argc != 2)
    {
        arguements_array = malloc((argc-2)*sizeof(int));
        *arguements_array = atoi(argv[--argc]);
        while (argc != 2)
        {
            *(arguements_array+(++k)) = atoi(argv[--argc]);
        }
        k++;
    }
    int num_of_argv = 1;
    if (!strcmp(argv[1],"-v")) num_of_argv = 2; 
    if ((ifp = fopen(argv[num_of_argv], "r")) == NULL)
    {
        perror("fopen source-file");
        return 1;
    }
    int tabs=0,line_num=0,clue,constant;
    while(!feof(ifp))
    {
        line_num++;
        fgets(buf, sizeof buf, ifp);
        if(feof(ifp))                                       //teleytaia grammi programmatos
        {
            char *p;
            p = (buf+strlen(buf));
            *p = '\n';
            *(p+1) = '\0';
        }
        if((start_of_comment = strstr(buf,"#")) != NULL) 
        {
            *start_of_comment = '\n';
            *(++start_of_comment) = '\0';
        }
        remove_spaces(buf);                      //ftiaxnoyme tin stixisi tis grammis diagrafontas ta perrita spaces kai tabs
        add_line(&line_list,buf,line_num);
        ln++;
    }
    line_num = 0;
    int condition_line = 0,run =1;
    listptr *ptr;
    ptr = &line_list;
    tabs = 0;
    //printf("%d %d\n",ln,line_num);
    while(*ptr != NULL && ln > line_num )
    { 
        //printf("a%d\n",line_num);
        if(!(line_num = all_modes(&var_tree,&line_list,++line_num,&tabs,&condition_line,&condition_list,ln,arguements_array,k))) return 1;
        ptr = &line_list;
        while((*ptr)->line_num != line_num) ptr = &(*ptr)->next;
    }
    fclose(ifp);
   // condition_print(condition_list);
    //treeprint(var_tree);
    //list_print(line_list);
    //for(i=0;i<1000;i++) free(**(mode+i));
    //free(*mode);
    return 0;
}