#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"
#include "statistics.h"
#include "team_victories.h"

int main(int argc, char *argv[]){
        if(argc<3 || argc>5){
                fprintf(stderr, "Неверное количество аргументов\n");
                return 1;
        }
        int f_read=0;
        int f_exicute=0;
        int number_of_p=-1;
        for(int i=2;i<argc;i++){
                if(!strcmp(argv[i], "-f")){
                        f_read=1;
                } else if(!strcmp(argv[i], "-p")){
                        i++;
                        if(i<argc){
                                if((!atoi(argv[i]) && strcmp(argv[i],"0"))){
                                        fprintf(stderr, "\"%s\" не является числом\n", argv[i]);
                                        return 10;
                                }
                        } else{
                                fprintf(stderr, "После \"-p\" должно идти число\n"); 
                                return 30;
                        }
                        f_exicute=1;
                        number_of_p=atoi(argv[i]);
                } else{
                        fprintf(stderr, "\"%s\" не подходит в качестве аргумента.\n USAGE: ./<PROGRAMM NAME> <INPUT FILENAME> <KEYS{-p NUM, -f}>\n", argv[i]);
                        return 40;
                }
        }
        FILE *in=fopen(argv[1],"r");
        if(in==NULL){
                fprintf(stderr,"Ошибка чтения файла '%s'",argv[1]);
                return 2;
        }
        statistics a;
        if(f_read){
                while(fread(&a,sizeof(a),1,in)){
                        printf("%d|%s|%s|%s|%d|%d|%d|\n", a.id, a.gamer, a.team, a.country, a.prize_money, a.matches, a.proportion_of_vict);
                }
                fseek(in,0,SEEK_SET);
        }
        if(f_exicute){
                vector_tv tmp={0, NULL};
                vector_tv *v=&tmp;
                vector_tv_create(v);
                team_victories f;
                int status=0;
                while(fread(&a,sizeof(a),1,in)){
                        strcpy(f.team,a.team);
                        f.victories=(a.matches)*(a.proportion_of_vict)/100;
                        for(int i=0;i<vector_tv_size(v);i++){
                                if(!strcmp(a.team,v->buffer[i].team)){
                                        status=1;
                                        v->buffer[i].victories=v->buffer[i].victories+f.victories;
                                        break;
                                }
                        }
                        if(status!=1){
                                if(!(vector_tv_push(v, f))){
                                        fprintf(stderr, "Недостаточно места");
                                        return 3;
                                }
                        }
                        status=0;
                }
                fseek(in,0,SEEK_SET);
                int max=0;
                char most_available_team[50];
                for(int i=0;i<vector_tv_size(v);i++){
                        if(v->buffer[i].victories>max){
                                max=v->buffer[i].victories;
                                strcpy(most_available_team,v->buffer[i].team);
                        }
                }
                printf("Команда с наибольшим количеством побед(одна из): %s\n", most_available_team);
                printf("Игроки команды с количеством призовых %d или больше:\n", number_of_p);
                while(fread(&a,sizeof(a),1,in)){
                        if(!strcmp(a.team,most_available_team) && a.prize_money>=number_of_p){
                                printf("%s\n", a.gamer);
                        }
                }
                vector_tv_destroy(v);
                return 0;
        }
}
