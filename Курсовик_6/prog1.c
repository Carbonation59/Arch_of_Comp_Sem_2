#include <stdio.h>

typedef struct{
        int id;
        char gamer[20];
        char team[50];
        char country[30];
        int prize_money;
        int matches;
        int proportion_of_vict;
} statistics;

int main(int argc, char * argv[]){
        if(argc!=3){
                fprintf(stderr, "Неверное количество аргументов\n");
                return 1;
        }
        FILE *in = fopen(argv[1], "r");
        if(in==NULL){
                fprintf(stderr, "Что-то не так с файлом '%s'\n", argv[1]);
                return 2;
        }
        FILE *out = fopen(argv[2],"w");
        if(out==NULL){
                fprintf(stderr, "Что-то не так с файлом '%s'\n", argv[2]);
                fclose(in);
                return 3;
        }   
        statistics a; 
        int k=0;
        while((k=fscanf(in, "%d|%[^|]|%[^|]|%[^|]|%d|%d|%d|", &a.id, a.gamer, a.team, a.country, &a.prize_money, &a.matches, &a.proportion_of_vict)) && k==7){
                fwrite(&a,sizeof(statistics),1,out);
                if(ferror(out)!=0){
                        fprintf(stderr, "Файл для записи переполнен\n");
                        fclose(in);
                        fclose(out);
                        return 4;
                }
        }
        if(k!=-1){
                fprintf(stderr, "Не хватает аргументов в строчке '%d'\n", a.id);
                return 5;
        }
        if(ferror(in)!=0){
                fprintf(stderr, "Ошибка чтения\n");
                fclose(in);
                fclose(out);
                return 5;
        }
        fclose(in);
        fclose(out);
        return 0;
}

