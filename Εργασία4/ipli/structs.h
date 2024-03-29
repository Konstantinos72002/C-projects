#define tab_or_space(x) ((x) == '\t' || (x) == ' ')
#define between_a_z_A_Z(x)   ((x)>=65 && (x)<=90 || (x)>=97 && (x)<=122)
#define between_1_9(x)         ((x)>='0' && (x)<='9')
#define operator_exist(x) (!strcmp(x,"+") || !strcmp(x,"-") || !strcmp(x,"/") || !strcmp(x,"*") || !strcmp(x,"%"))
#define comporer_exist(x) ((!strcmp(x,"==") || !strcmp(x,"!=") || !strcmp(x,">=") || !strcmp(x,"<=") || !strcmp(x,">")) || !strcmp(x,"<"))
typedef struct tree *treeptr;
struct tree
{
    char *var_name;
    int var_price;
    treeptr left;
    treeptr right;
};

typedef struct list *listptr;
struct list
{
    int line_num;
    char *line;
    listptr next;
};

typedef struct list_c *listptrc;
struct list_c
{
    int cond;
    int line_num;
    int tabs;
    listptrc next;
};