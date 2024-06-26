#include <stdio.h>
#include <stdbool.h>
#include "tabl_el.h"
#include "vector.h"
#include "vector_norm.h"

bool read_tabl(vector_tabl_el *v){
        char c;
        c=getchar();
        if(c==EOF){
                return false;
        }
        tabl_el a;
        while(c!='\n' && c!=EOF){
                ungetc(c,stdin);
                if(!read_tabl_el(&a)){
                        return false;
                }
                vt_push_back(v,a);
                c=getchar();
        }
        if(c==EOF){
                return false;
        }
        return true;
}

void lin_sort_with_count(vector_tabl_el *v){
        vector_i V;
        vi_create(&V);
        for(int i=0;i<vt_size(v);i++){
                vi_push_back(&V,1);
        }
        for(int i=0;i<vt_size(v);i++){
                for(int j=i+1;j<vt_size(v);j++){
                        if(keycmp(vt_get(v,i).key,vt_get(v,j).key)<0){
                                vi_plus_one(&V,i);
                        } else if(keycmp(vt_get(v,i).key,vt_get(v,j).key)>=0){
                                vi_plus_one(&V,j);
                        }
                }
        }
        vector_tabl_el v1;
        vt_create(&v1);
        tabl_el a;
        for(int i=0;i<vi_size(&V);i++){
                vt_push_back(&v1,a);
        }
        for(int i=0;i<vi_size(&V);i++){
                vt_set(&v1,vi_get(&V,i)-1,vt_get(v,i));
        }
        for(int i=0;i<vi_size(&V);i++){
                vt_set(v,i,vt_get(&v1,i));
        }
        vt_destroy(&v1);
        vi_destroy(&V);
}

tabl_el binary_search(vector_tabl_el v, key a, int *number){
        int l=0;
        int r=v.size-1;
        int mid;
        while(r-l>1){
                mid=(r+l)/2;
                if(keycmp(a,vt_get(&v,mid).key)<0){
                        l=mid;
                } else {
                        r=mid;
                }
        }
        if(keycmp(a,vt_get(&v,l).key)==0){
                *number=l+1;
                return vt_get(&v,l);
        } else if(keycmp(a,vt_get(&v,r).key)==0){
                *number=r+1;
                return vt_get(&v,r);
        } else {
                *number=0;
                return vt_get(&v,r);
        }
}

int main(){
        printf("\n");
        vector_tabl_el v;
        vt_create(&v);
        if(!read_tabl(&v)){
                return 0;
        }
        printf("Input table:\n\n");
        print_vector(&v);
        lin_sort_with_count(&v);
        printf("Sorted table:\n\n");
        print_vector(&v);
        key a;
        tabl_el b;
        char c;
        int val;
        c=getchar();
        while(c!=EOF){
                val=0;
                ungetc(c,stdin);
                if(!read_key(&a)){
                        return 0;
                }
                b=binary_search(v,a,&val);
                if(val==0){
                        printf("No specified key in this list\n\n");
                } else {
                        printf("Line:");
                        print_tabl_el(b);
                        printf("Number of line:%d\n\n",val);
                }
                c=getchar();
        }
}
