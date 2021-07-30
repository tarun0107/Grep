typedef struct node{
    char file[100];
    struct node* next;
}node;
typedef node* list;
void init(list *l);
void add(list *l, char c[]);
char* remov(list *l);
int isempty(list l);
void modify(list *l);
void listing(char *path1, list *l);
