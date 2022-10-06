#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <windows.h>

fparac(){
	float fahrenheit=0;
	printf("introduza o valor em Fahrenheit\n");
	scanf("%f",&fahrenheit);
	fahrenheit = ((fahrenheit - 32)/1.8);
	
	printf("\nvalor em celsius: %0.1f",fahrenheit);
	
}

fparak(){
	float fahrenheit=0;
	printf("introduza o valor em Fahrenheit\n");
	scanf("%f",&fahrenheit);
	fahrenheit = ((fahrenheit + 459.67)/1.8);
	
	printf("\nvalor em Kelvin: %0.1f",fahrenheit);
	
}

kparaf(){ 
    float kelvin=0;
	printf("introduza o valor em kelvin\n");
	scanf("%f",&kelvin);
	kelvin = ((kelvin *1.8)-459.67);
	
	printf("\nvalor em fahrenheit: %0.1f",kelvin);
}

kparac(){ 
    float kelvin=0;
	printf("introduza o valor em Celsius\n");
	scanf("%f",&kelvin);
	kelvin = (kelvin - 273.15);
	
	printf("\nvalor em celsius: %0.1f",kelvin);
}

cparaf(){
	float celsius=0;
	printf("introduza o valor em Celsius\n");
	scanf("%f",&celsius);
	celsius = ((celsius *1.8)+32);
	
	printf("\nvalor em fahrenheit: %0.1f",celsius);
}

cparak(){
    float celsius=0;
	printf("introduza o valor em Celsius\n");
	scanf("%f",&celsius);
	celsius = (celsius +273.15);
	
	printf("\nvalor em Kelvin: %0.1f",celsius);
	
}

int main (){
	printf ("transformação °F/°c/K");
	printf ("selecione a opc que deseja:\n");
	switch
	getch();
}
