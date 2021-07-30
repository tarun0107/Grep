int getline(FILE *fp, char *ch);
int search(char* word, char* line, int casesen, int wordc);
int isfile(char *file);
int iscommand(char *c);
void print_help();
void printversion();
int isdirectory(char *path);
void o_flag(char* word, char* line, int casesen);
char* f_flag(char *temp);

