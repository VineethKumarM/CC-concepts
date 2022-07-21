#include <stdio.h>
#include <string.h>
/*struct data structute*/
struct Data {
int i;//1000
float f;//1004
char str[20];//1008
};
/*union data structure*/
union Data1{
    int i;
    float f;
    char str[20];
};
int main() {
union Data1 data;
data.i = 10;
data.f = 220.5;
strcpy(data.str, "C Programming");
printf("data.i : %p\n", &data.i);
printf("data.f : %p\n", &data.f);
printf("data.str : %p\n", &data.str);
return 0;
}