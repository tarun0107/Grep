#include<stdio.h>
#include<stdlib.h>
#include"list.h"
#include<string.h>
#include<dirent.h>
void init(list *l) {
    *l = NULL;
    return;
}
void add(list *l, char c[]) {
    node *p = *l;
    node *nn = (node *)malloc(sizeof(node));
    if(!nn)
        return;
    strcpy(nn->file, c);
    nn->next = NULL;

    if(*l == NULL) {
        *l = nn;
        return;
    }
    while(p->next)
        p = p->next;
    p->next = nn;
    return;
}
char* remov(list *l) {
    node *p = *l;
    char* str = (char *)malloc(sizeof(char) * 100);
    *l = p->next;
    strcpy(str, p->file);
    free(p);
    return str;
}
int isempty(list l) {
    if(l == NULL)
        return 1;
    else
        return 0;
}
void modify(list *l) {
    node *p = *l, *q = NULL;
    while(p) {
        if((strstr(p->file, ".o") != 0) || (strstr(p->file, ".exe") != 0) || (strstr(p->file, ".h") != 0) || (strstr(p->file, ".cbp") != 0)) {
            if(p && *l == p) {
                (*l) = p->next;
                //printf("HEre\n");
                free(p);
                return;
            }
            if(p) {
                q->next = p->next;
                //printf("HEre\n");
                free(p);

                return;
            }
        }
       // printf("Here1\n");
        q = p;
        p = p->next;
    }
    return;
}

void listing(char* path1, list *l) {
    DIR *dr = opendir(path1);
    struct dirent *p;
    if(dr == NULL) {
        printf("Error Opening Directory\n");
        return;
    }
    char path[1000], temp[1000];

    while((p = readdir(dr)) != NULL) {
        if(strcmp(p->d_name, ".") != 0 && strcmp(p->d_name, "..") != 0) {
            if(strstr(p->d_name, ".") != 0) {
                strcpy(temp, path1);
                strcat(temp, "/");
                strcat(temp, p->d_name);
                add(l, temp);
                modify(l);
            }

            else {
                strcpy(path, path1);
                strcat(path, "/");
                strcat(path, p->d_name);
                listing(path, l);
            }
        }
    }


    closedir(dr);
}
