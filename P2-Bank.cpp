#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct trans {
    int code;
    int issuersAccsID;
    double amount;
    int type;
    char date [100];
    int secondPartysId;
    char description [41];
    trans *next;
} transaction;


typedef struct acct{
    int id;
    char bank [50];
    int type;
    double balance;
    acct *next;
    transaction *tnext;
} account;


struct client{
    int id;
    char name [150];
    char city [200];
    char phone [30];
    client *next;
    account *anext;
};

void checkTransactionsMenu(){
    int op=-1;
        if (op){
            printf("    *** Consultas varias ****\n");
            printf("    \t 1. Mostrar informacion por nombre\n");
            printf("    \t 2. Mostrar transacciones de cobro\n");
            printf("    \t 3. Mostrar transacciones de pago\n");
            printf("    \t 4. Mostrar todas las transacciones\n");
            printf("    \t 5. Mostrar transacciones por rango de valores\n");
            printf("    \t 0. Regresar\n");
            scanf("%d", &op);

            switch (op)
            {
            case 1:
                /* code */
                break;

            case 2: break;
            case 3: break;
            case 4: break;
            case 5: break;

            case 0:
                system("cls");
                break;
            
            default:
                printf("Opcion fuera de rango\n");
                system("pause");
                system("cls");
                break;
            }
            
        }
}

void linkAccountMenu(){
    int op=-1;
        if (op){
            printf("    *** Clientes del sistema ****\n");
            printf("    \t 1. Agregar cliente\n");
            printf("    \t 2. Modificar cliente\n");
            printf("    \t 3. Eliminar cliente\n");
            printf("    \t 4. Agregar cuenta\n");
            printf("    \t 5. Modificar cuenta\n");
            printf("    \t 6. Eliminar cuenta\n");
            printf("    \t 0. Regresar\n");
            scanf("%d", &op);
            
            switch (op)
            {
            case 1:
                /* code */
                break;

            case 2:
                /* code */
                break;

            case 0:
                system("cls");
                break;
            
            default:
                printf("Opcion fuera de rango\n");
                system("pause");
                system("cls");
                break;
            }
        }
}

void loadFromFile(){
    char path[1024];
    FILE *fp;
        printf("Especifique ruta de archivo\n");
        scanf("%s", &path);
        fp = fopen(path, "r");
            if (fp == NULL){
                printf("No fue posible abrir el archivo\n");
            }
            else {
                printf("Archivo cargado con exito\n");
            }
}

void showMenu(){
    client *c = NULL;
    int op=-1;
        while (op){
            printf("*** Sistema de pagos y cobros P2Bank ***\n\n");
            printf("    \t 1. Cuentas\n");
            printf("    \t 2. Opciones de pagos\n");
            printf("    \t 3. Consultas varias\n");
            printf("    \t 4. Cargar datos desde archivo\n");
            printf("    \t 5. Mostrar todos los datos\n");
            //Option 5 will be used to make the output file because the program has to access the whole nested list anyway
            printf("    \t 6. Insertar datos manualmente");
            //Option 6 will be used for something in option 1, for now it's just testing
            printf("    \t 0. Salir\n");
            scanf("%d",&op);

            switch (op)
            {
            case 1:
                linkAccountMenu();
                break;

            case 2:
                break;
            
            case 3:
                checkTransactionsMenu();
                break;

            case 4:
                loadFromFile();
                break;

            case 0:
                break;
            
            default:
                printf("Opcion fuera de rango\n");
                system("pause");
                system("cls");
                break;
            }
        }
}

int main () {
    showMenu();
    system("pause");
}