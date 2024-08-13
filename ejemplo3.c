#include "stdio.h"
#include "math.h"

#define M_PI 3.14159265358979323846

#define STACK_SIZE 8 // Define el tamaño de la pila como 8

float stack[STACK_SIZE] = {0}; // Inicializa la pila con ceros

// Función para imprimir la pila
void printstack(void)
{
    for (int i = 0; i < STACK_SIZE; i++)
    {
        printf("%d. %f\n", STACK_SIZE - i, stack[i]);
    }
}

// Función para mover los elementos de la pila hacia arriba
void movestackup(void)
{
    for (int i = 0; i < STACK_SIZE - 1; i++)
    {
        stack[i] = stack[i + 1];
    }
    stack[STACK_SIZE - 1] = 0;
}

// Función para agregar un nuevo número a la pila
void push(float value)
{
    movestackup();
    stack[STACK_SIZE - 1] = value;
}

// Función para eliminar y devolver el valor en la parte inferior de la pila (registro 1)
float pop(void)
{
    float bottomValue = stack[STACK_SIZE - 1];
    for (int i = STACK_SIZE - 1; i > 0; i--)
    {
        stack[i] = stack[i - 1];
    }
    stack[0] = 0;
    return bottomValue;
}

// Función para limpiar (eliminar) el último número ingresado en la pila (registro 1)
void clear_last(void)
{
    for (int i = STACK_SIZE - 1; i > 0; i--)
    {
        stack[i] = stack[i - 1];
    }
    stack[0] = 0;
}

// Función para limpiar toda la pila (reiniciar todos los valores a 0)
void clear_all(void)
{
    for (int i = 0; i < STACK_SIZE; i++)
    {
        stack[i] = 0;
    }
}

// Función para convertir grados a radianes
float degrees_to_radians(float degrees)
{
    return degrees * M_PI / 180.0;
}

// Función para convertir radianes a grados
float radians_to_degrees(float radians)
{
    return radians * 180.0 / M_PI;
}

// Función para realizar operaciones
void select_operation(char op)
{
    float a, b, result;

    // Para operaciones que requieren dos operandos
    if (op == '+' || op == '-' || op == '*' || op == '/' || op == 'p')
    {
        if (stack[STACK_SIZE - 2] == 0 && stack[STACK_SIZE - 1] == 0)
        {
            printf("Error: No hay suficientes valores en la pila para realizar la operación.\n");
            return;
        }

        a = pop();
        b = pop();
    }
    else
    {
        a = pop();
    }

    switch (op)
    {
    case '+':
        result = b + a;
        break;
    case '-':
        result = b - a;
        break;
    case '*':
        result = b * a;
        break;
    case '/':
        if (a != 0)
        {
            result = b / a;
        }
        else
        {
            printf("Error: División por cero.\n");
            push(b);
            push(a);
            return;
        }
        break;
    case 'r':
        if (a >= 0)
        {
            result = sqrt(a);
        }
        else
        {
            printf("Error: No se puede calcular la raíz cuadrada de un número negativo.\n");
            push(a);
            return;
        }
        break;
    case 's':
        result = sin(degrees_to_radians(a)); // Convertir grados a radianes para cálculo
        break;
    case 'c':
        result = cos(degrees_to_radians(a)); // Convertir grados a radianes para cálculo
        break;
    case 't':
        if (fmod(a, 180.0) == 90.0 || fmod(a, 180.0) == 270.0)
        {
            // Verificar ángulos donde la tangente es indefinida
            printf("Error: Tangente indefinida para este ángulo.\n");
            push(a);
            return;
        }
        result = tan(degrees_to_radians(a)); // Convertir grados a radianes para cálculo
        break;
    case 'p':
        result = pow(b, a);
        break;
    default:
        printf("Operación no válida.\n");
        if (op == '+' || op == '-' || op == '*' || op == '/' || op == 'p')
        {
            push(b);
        }
        push(a);
        return;
    }

    push(result);
}

// Función para imprimir el menú de opciones
void print_menu(void)
{
    const char *menu[] = {
        "1. Ingresar número",
        "2. Seleccionar operación (+, -, *, /, r, s, c, t, p)",
        "3. Limpiar último número",
        "4. Limpiar todo",
        "5. Salir"};

    for (int i = 0; i < sizeof(menu) / sizeof(menu[0]); i++)
    {
        printf("%s\n", menu[i]);
    }
    printf("Seleccione una opción: ");
}

// Función main
int main()
{
    int option;
    float num;
    char op;
    int result;

    while (1)
    {
        printf("\n----------------------------------------\n");
        printstack(); // Muestra el estado actual de la pila
        print_menu(); // Muestra el menú de opciones

        // Validación de entrada de la opción
        while (1)
        {
            result = scanf("%d", &option);
            if (result == 1)
            {
                break;
            }
            else
            { // Si la entrada no es un entero
                printf("Error: Entrada inválida. Por favor, ingrese un número entero.\n");
                while (getchar() != '\n')
                    ;         // Limpiar el búfer de entrada
                print_menu(); // Vuelve a mostrar el menú
            }
        }

        switch (option)
        {
        case 1:
            printf("Ingrese un número: ");
            scanf("%f", &num);
            push(num);
            break;
        case 2:
            printf("Seleccione una operación (+, -, *, /, r, s, c, t, p): ");
            scanf(" %c", &op); // Espacio antes de %c para ignorar caracteres de nueva línea
            select_operation(op);
            break;
        case 3:
            clear_last();
            break;
        case 4:
            clear_all();
            break;
        case 5:
            printf("Saliendo...\n");
            return 0;
        default:
            printf("Error: Opción no válida. Por favor, seleccione una opción válida.\n");
            // Imprime el estado actual de la pila y el menú otra vez
            break;
        }
    }

    return 0;
}