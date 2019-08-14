#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {FALSE = 0, TRUE} boolean;


typedef struct trans {
    int code;
    int issuersAccsID;
    double amount;
    int type;
    char date [100];
    int secondPartysId;
    char description [41];
    struct trans *next;
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

void fileExists(FILE *input, client **p){
    char line[1000]; char dat[1000];
    client *ax = new client;
    client *t = *p;
    int clients = 0, accounts = 0, data = 0, j=0;
    boolean listClients = FALSE;
    boolean listAccounts = FALSE;

/************************* AUX VARS *********************/
    int auxid = 0, auxt = 0;
    char auxb [50];
    double auxbal = 0;

        while (!feof(input) && !ferror(input)){
            fgets(line, 1000, input);
            //printf("%s\n",line);
            if (line[0]=='*' && line[1]=='C'){
                ax = new client;
                accounts=0;
                listClients = TRUE;
                listAccounts=FALSE;
            }

            if (listClients == TRUE && line[0]!='*' && line[1]!='C'){
                for (int i=0; i<=strlen(line); i++){
                    /* For each '-' it's a different variable to fill in the list */
                    if (line[i]!='-'){
                        dat[j]=line[i];
                        j++;
                    }
                    if (line[i]=='-' || i==strlen(line)){
                        dat[j]='\0';
                        j=0;
                        //printf("dat %s\n", dat);
                        switch (data)
                        {
                        case 0:
                            ax->id = strtol(dat, NULL, 10);
                            //printf("Cedula %d\n", ax->id);
                            break;
                        case 1: 
                            strcpy(ax->name,dat);
                            break;
                        case 2:
                            strcpy(ax->city,dat);
                            break;
                        case 3: 
                            strcpy(ax->phone,dat);
                            data=-1;
                            break;
                        }
                        strcpy(dat,"");
                        data++;
                        continue;
                    } 
                } //End of for

                if (clients==0){
                /*Insert at the beginning of the list*/
                    ax->next = *p;
                    *p = ax;
                    ax->next = NULL;
                }
                else{
                /*Insert at the end of the list*/
                    t = *p;
                    ax->next = NULL;
                        while(t->next != NULL)
                            t=t->next;
                    t->next = ax;
                }
                clients++;
                listClients=FALSE;
            } //End of if

/******************************************* ACCOUNTS *************************************************/

            if (line[0]=='*' && line[1]=='B'){
                listAccounts = TRUE;
            }

            if (listAccounts == TRUE && line[0]!='*' && line[1]!='B'){
                printf("here\n");
                for (int i=0; i<=strlen(line); i++){
                    /* For each '-' it's a different variable to fill in the list */
                    if (line[i]!='-'){
                        dat[j]=line[i];
                        j++;
                    }
                    if (line[i]=='-' || i==strlen(line)){
                        dat[j]='\0';
                        j=0;
                        //printf("dat %s\n", dat);
                        switch (data)
                        {
                        case 0:
                            auxid = strtol(dat, NULL, 10);
                            printf("Numero de cuenta %d\n", auxid);
                            break;
                        case 1: 
                            strcpy(auxb,"");
                            strcpy(auxb,dat);
                            break;
                        case 2:
                            auxt = strtol(dat,NULL,10);
                            break;
                        case 3: 
                            char *ptr;
                            auxbal=strtod(dat, &ptr);
                            printf("Balance %lf\n", auxbal);
                            data=-1;
                            break;
                        }
                        strcpy(dat,"");
                        data++;
                        continue;
                    } 
                } //End of for

                /*Insert at the end of the list*/
                    account * acc = new account;
                    account * acc2;

                    if (acc==NULL){
                            exit(1);
                        }

                    acc->id = auxid;
                    strcpy(acc->bank,auxb);
                    acc->type = auxt;
                    acc->balance = auxbal;
                    acc->next = NULL;
                        if (accounts == 0)
                            ax->anext = acc;
                        else {
                            acc2 = ax->anext;
                            while (acc2->next != NULL){
                                acc2 = acc2->next;
                            }
                        acc2->next = acc;
                        }
                accounts++;
            } //End of if listAccounts == TRUE


/***************************************** TRANSACTIONS *************************************************/

            if (line[0]=='*' && line[1]=='T'){
                accounts=0;
                listAccounts=FALSE;
                //ax->anext = new account;
                //listAccounts = TRUE;
            }

            

            strcpy(line,"");    
        } //End of while !(eof)
    fclose(input);
}

void loadFromFile(client **p){
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
                fileExists(fp, p);
                system("pause");
            }
}

void showMenu(){
    client *c = NULL;
    int op=-1;
        while (op){
            printf("\n*** Sistema de pagos y cobros P2Bank ***\n\n");
            printf("    \t 1. Cuentas\n");
            printf("    \t 2. Opciones de pagos\n");
            printf("    \t 3. Consultas varias\n");
            printf("    \t 4. Cargar datos desde archivo\n");
            printf("    \t 5. Mostrar todos los datos\n");
            //Option 5 will be used to make the output file because the program has to access the whole nested list anyway
            printf("    \t 6. Insertar datos manualmente\n");
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
                loadFromFile(&c);
                system("cls");
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