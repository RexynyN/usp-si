#include <stdio.h>
#include <math.h>
double areaRetangulo(double l1, double l2){
 return l1 * l2;
}
double areaTriangulo(double b, double h){
 return areaRetangulo(b,h)/2;
}
double areaCirculo(double r){
 return M_PI*areaRetangulo(r,r);
}
int main(){
 int ret;
 int tri;
 double circ, x, l1,l2,b,h,r;
 printf("Entre com o valor de x:");
 if(scanf("%lf", &x) == 1){
  if(x > 0){
   //x =15;
   l1=(2*x)/3;
   l2=(7*x)/15;
   b=x/3;
   h=(4*x)/15;
   r=h;
      printf("Programa para o calculo de uma area geometrica \n");
      ret = areaRetangulo(l1,l2);
      printf("Area do retangulo = %d\n", ret);
      tri = areaTriangulo(b,h);
   printf("Area do triangulo = %d\n",tri);
   circ = areaCirculo(r)/4;
   printf("Area do 1/4 de circulo = %.2f\n",circ);
   printf("Area total = %.2f\n",ret + tri - circ);
  }else{
   printf("Dimensao Invalida \n");
  }
 }else{
  printf("Falha na leitura do valor double \n");
 }
 return 0;
}