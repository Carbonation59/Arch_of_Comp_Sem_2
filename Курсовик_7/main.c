#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "vector_dbl.h"
#include "vector_ll.h"

typedef struct{
        long long m;
        long long n;
        vector_ll cip;
        vector_ll pi;
        vector_double ye;
} matrix;


void create_matrix(matrix *matr){
        matr->m=0;
        matr->n=0;
        vll_create(&matr->cip);
        vll_create(&matr->pi);
        vd_create(&matr->ye);
}


void read_matrix(matrix *matr){
        scanf("%lli%lli",&matr->m,&matr->n);
        double a;
        long long last=0;
        vll_push(&matr->cip,0);
        for(long long i=0;i<matr->m;i++){
                for(long long j=0;j<matr->n;j++){
                        scanf("%lf",&a);
                        if(a!=0){
                                vll_push(&matr->pi,j);
                                vd_push(&matr->ye,a);
                        }
                        last=vll_size(&matr->pi);
                }
                vll_push(&matr->cip,last);
        }
        printf("\n");
}

void print_cip_ip_ye_matrix(matrix *matr){
        printf("CIP: ");
        for(long long i=0;i<vll_size(&matr->cip);i++){
                printf("%lli ",vll_get(&matr->cip,i));
        }
        printf("\nPI: ");
        for(long long i=0;i<vll_size(&matr->pi);i++){
                printf("%lli ",vll_get(&matr->pi,i));
        }
        printf("\nYE: ");
        for(long long i=0;i<vd_size(&matr->ye);i++){
                printf("%f ",vd_get(&matr->ye,i));
        }
        printf("\n\n");
}

void printf_matrix(matrix *matr){
        long long count=0;
        for(long long i=0;i<matr->m;i++){
                if(vll_get(&matr->cip,i)==vll_get(&matr->cip,i+1)){
                        for(long long i=0;i<matr->n;i++){
                                printf("0 ");
                        }
                } else {
                        for(long long j=vll_get(&matr->cip,i);j<vll_get(&matr->cip,i+1);j++){
                                if(vll_get(&matr->pi,j)==count){
                                        printf("%f ",vd_get(&matr->ye,j));
                                } else {
                                        j--;
                                        printf("0 ");
                                }
                                count++;
                        }
                        while(count<matr->n){
                                printf("0 ");
                                count++;
                        }
                        count=0;
                }
                printf("\n");
        }
        printf("\n");
}

void task(matrix *matr){
        long long max=0;
        for(long long i=0;i<matr->m;i++){
                if(vll_get(&matr->cip,i+1)-vll_get(&matr->cip,i)>max){
                        max=vll_get(&matr->cip,i+1)-vll_get(&matr->cip,i);
                }
        }
        if(max==0){
                printf("All elements of matrix are equal to zero\n\n");
        } else{
                long long sum=0;
                for(long long i=0;i<=matr->m;i++){
                        if(vll_get(&matr->cip,i+1)-vll_get(&matr->cip,i)==max){
                                printf("Number of matrix line: %lli\n",i+1);
                                for(int j=vll_get(&matr->cip,i);j<vll_get(&matr->cip,i+1);j++){
                                        sum=sum+vd_get(&matr->ye,j);
                                }
                                printf("Sum of elements of matrix line: %lli\n\n",sum);
                                sum=0;
                        }
                }
        }
}

void destroy_matrix(matrix *matr){
        matr->m=0;
        matr->n=0;
        vll_destroy(&matr->cip);
        vll_destroy(&matr->pi);
        vd_destroy(&matr->ye);
}

int main(){
        matrix matr;
        create_matrix(&matr);
        read_matrix(&matr);
        print_cip_ip_ye_matrix(&matr);
        printf_matrix(&matr);
        task(&matr);
        destroy_matrix(&matr);
}
