#include <stdio.h>

int main() {
    //Declaración de variables
    float base, height, volume;

    // Solicitar los datos y asignación
    printf("Ingrese el área de la base de la pirámide (en unidades cuadradas): ");
    scanf("%f", &base);
    
    printf("Ingrese la altura de la pirámide (en unidades): ");
    scanf("%f", &height);

    // Calcular el volumen de la pirámide
    volume = (base * height) / 3;

    // Mostrar el resultado
    printf("El volumen de la pirámide es: %.2f unidades cúbicas\n", volume);

    return 0;
}
