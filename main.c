#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Mount {
    char name[80];
    char connections[40][80];
    int NOC;
};


struct Mount create (){
    struct Mount *s;
    s = malloc(sizeof(struct Mount));
    s->NOC = 0;
    return *s;
};

void start_init (struct Mount *s, int am){
    int brek = 1;
    int check = 0;
    char ans[80];
    printf("Enter names of mounts\n");
    for (unsigned int i = 0; i < am; i++){
        scanf("%s", s[i].name);
    }
    for (unsigned int i = 0; i < am; i++){
        printf("Enter connections for mount %s or '0' to exit \n", s[i].name);
        while (check < am - 1){
            scanf("%s", &ans);
            if (strcmpi("0", ans) == 0){
                break;
            }
            for (unsigned int j = 0; j < am; j++){
                if (strcmpi(ans, s[i].name) == 0){
                    printf("Mount can't be assigned to itself\n");
                    break;
                } else if (strcmpi(ans, s[j].name) == 0){
                    for (unsigned int l = 0; l < s[j].NOC; l++){
                        if (strcmpi(s[i].name, s[j].connections[l]) == 0){
                            printf("This mount is already assigned\n");
                            brek = 0;
                        }
                    }
                    if (brek){
                        strcpy(s[i].connections[check], ans);
                        check++;
                        s[i].NOC++;
                    }
                }
                brek = 1;
            }
        }
        check = 0;
    }
}

void Construction(struct Mount *s, int am){
    FILE *f;
    f = fopen("graphs/graph.gv", "w");
    if (f == NULL){
        printf("Error: Not opened\n");
        exit(2);
    }
    fputs("graph graphname {\n", f);
    for (unsigned int i = 0; i < am; i++){
        fputs(s[i].name, f);
        fputs(";\n", f);
    }
    for (unsigned int i = 0; i < am; i++){
        for (unsigned int j = 0; j < s[i].NOC; j++){
            fputs(s[i].name, f);
            fputs("--", f);
            fputs(s[i].connections[j], f);
            fputs(";\n", f);
        }
    }
    fputs("}", f);
    if (fclose(f) == EOF){
        printf("Error: Not closed\n");
        exit(3);
    }
}

void adjacency(struct Mount *s, int am){
    int mounts = am;
    int ribbons = 0;
    for (unsigned int i = 0; i < am; i++){
        ribbons += s[i].NOC;
    }
    if (ribbons > ((am-1)*(am - 2))/2){
        printf("This graph is connected one\n");
    } else {
        printf("This graph isn't connected one\n");
    }
}

int main (void){
    int amount;
    int off = 1;
    char answer[80];
    struct Mount *p;
    printf("Enter number of mounts\n");
    while (scanf("%d", &amount) != 1){
        scanf("%*[^\n]");
    }
    if (!(p = malloc(amount * sizeof(struct Mount)))){
        printf("memory allocation error");
        exit(1);
    }
    for (unsigned int i = 0; i < amount; i++){
        p[i] = create(amount);
    }
    start_init(p, amount);
    Construction(p, amount);
    adjacency(p, amount);
    free(p);
    return 0;
}
