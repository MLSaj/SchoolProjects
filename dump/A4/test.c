

#include <stdio.h>
void change_array(double arr[10]){
    for(int i = 0; i < 10; i++){
        arr[i] = 1;
    }


}

main(){
    printf("HIIIII\n");
    double arr[10] = {0};
    for(int j =0; j<10; j++){
        printf("%f\n", arr[j]);
    }
    change_array(arr);

    for(int i = 0; i <10; i++){
        printf("%f\n", arr[i]);
    }
}