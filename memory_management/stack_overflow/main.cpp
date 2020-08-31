#include<stdio.h>
int a=1;
void myfun(int& x){
  int y=0;
  printf("\n");
  printf("&a: %p\n", &a);
  printf("&x: %p\n", &x);
  printf("&y: %p\n", &y);
  printf("sizeof(int) = %ld\n", sizeof(int));
  printf("&y - &x =  %ld \n", &y - &x);
  printf("(&y - &x)*sizeof(int) = %ld \n", (&y - &x)*sizeof(int));
  printf("&y - &a =  %ld \n", &y - &a);
  printf("(&y - &a)*sizeof(int) = %ld \n", (&y - &a)*sizeof(int));
  myfun(x);
}
int main(){
  printf("&a: %p\n", &a);
  int x=2;
  printf("&x: %p\n", &x);
  myfun(x);
  return 0;
}

