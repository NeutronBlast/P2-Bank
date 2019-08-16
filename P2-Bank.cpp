#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {FALSE = 0, TRUE} boolean;


typedef struct trans {
    int code;
    int issuersAccsID;
    int secondPartysAN;
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

account * search (client *p, int accountID){
	account *t = p->anext;
    client * h = p;
    while (h){
        t = h->anext;
	    while (t) {
		    if ((t->id) == accountID) {
                return t;
		    }
		t = t->next;
	    }
    h=h->next;
    }
    return t;
}

void fileExists(FILE *input, client **p){
    char line[1000]; char dat[1000];
    client *ax = new client;
    client *t = *p;
    int clients = 0, accounts = 0, transactions = 0, data = 0, j=0;
    boolean listClients = FALSE;
    boolean listAccounts = FALSE;
    boolean listTrans = FALSE; 

/************************* AUX VARS *********************/
    int auxid = 0, auxt = 0, auxsecondAID = 0, transcode = 0, auxsecondID;
    char auxb [50], date [100], description[41];
    double auxbal = 0;

        while (!feof(input) && !ferror(input)){
            fgets(line, 1000, input);
            //printf("%s\n",line);
            if (line[0]=='*' && line[1]=='C'){
                ax = new client;
                accounts=0;
                transactions=0;
                listClients = TRUE;
                listAccounts= FALSE;
                listTrans = FALSE;
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
                listClients = FALSE;
                listTrans = FALSE;
                transactions = 0;
            }

            if (listAccounts == TRUE && line[0]!='*' && line[1]!='B'){
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
                            //printf("Numero de cuenta %d\n", auxid);
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
                            //printf("Balance %lf\n", auxbal);
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
                        if (accounts == 0){
                            ax->anext = acc;
                            ax->anext->tnext = NULL;
                        }
                        else {
                            acc2 = ax->anext;
                            while (acc2->next != NULL){
                                acc2 = acc2->next;
                            }
                        acc2->tnext = NULL;
                        acc2->next = acc;
                        acc->tnext = NULL;
                        }
                accounts++;
            } //End of if listAccounts == TRUE


/***************************************** TRANSACTIONS *************************************************/

            if (line[0]=='*' && line[1]=='T'){
                accounts=0;
                listAccounts=FALSE;
                listTrans = TRUE;
            }

            if (listTrans == TRUE && line[0]!='*' && line[1]!='T' && strlen(line)>1){
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
                        /*Transaction type*/
                            auxt = strtol(dat, NULL, 10);
                            printf("Tipo de transaccion %d\n", auxt);
                            break;
                        case 1:
                        /* Issuer's Account's ID */
                            auxid = strtol(dat, NULL, 10); 
                            printf("Numero de cuenta del emisor %d\n",auxid);
                            break;
                        case 2:
                            auxsecondAID = strtol(dat,NULL,10);
                            printf("Numero de cuenta de la otra persona involucrada %d\n",auxsecondAID);
                            break;
                        case 3:
                            strcpy(date,"");
                            strcpy(date,dat);
                            break;
                        case 4: 
                            char *ptr;
                            auxbal=strtod(dat, &ptr);
                            printf("Monto %lf\n", auxbal);
                            break;
                        case 5:
                            transcode = strtol(dat,NULL,10);
                            printf("Codigo de transaccion %d\n", transcode);
                            break;
                        case 6:
                            strcpy(description,"");
                            strcpy(description,dat);
                            break;
                        case 7:
                            auxsecondID = strtol (dat, NULL, 10);
                            printf("Cedula de la otra persona involucrada %d\n", auxsecondID);
                            data=-1;
                            break;
                        }

                        strcpy(dat,"");
                        data++;
                        continue;
                    } 
                } //End of for

                /*Insert at the end of the list*/
                    transaction * tt = new transaction;
                    transaction * tt2;

                    if (tt==NULL){
                            exit(1);
                    }

                    tt->type = auxt;
                    tt->issuersAccsID = auxid;
                    tt->secondPartysAN = auxsecondID;
                    strcpy(tt->date,date);
                    tt->amount = auxbal;
                    tt->code = transcode;
                    strcpy(tt->description,description);
                    tt->secondPartysId = auxsecondAID;

                    tt->next = NULL;

                    client * as = *p;
                    account * as2 = as->anext;
                    
                    as2 = search(as, auxid);

                    if (as2->tnext == NULL){
                        as2->tnext = tt;
                    }

                    else{
                        tt2 = as2->tnext;
                            while (tt2->next != NULL){
                                tt2 = tt2->next;
                            }
                        tt2->next = tt;
                    }
                as = as->next;
            } //End of if listAccounts == TRUE

            strcpy(line,"");    
        } //End of while !(eof)
    fclose(input);
}

boolean errorInFileStructure (FILE *input){
    char line[1000]; char dat[1000]; char *ptr = NULL;
    int clients = 0, accounts = 0, transactions = 0, data = 0, j = 0, sepCount = 0;
    boolean listClients = FALSE;
    boolean listAccounts = FALSE;
    boolean listTrans = FALSE;
    boolean isThereError = FALSE;

/******************************** AUX VARS **********************************************/
    int auxi = 0;

    while (!feof(input) && !ferror(input)){
        fgets(line, 1000, input);

    if (line[0]=='*' && line[1]=='C'){
        listClients = TRUE;
        listAccounts = FALSE;
        listTrans = FALSE;
        continue;
    }

    if ((clients == 0 && line[0]!='*' && line[1]!='C' && listClients == FALSE)){
        printf("ERROR: Debe existir una linea *C para denotar a los clientes\n");
        printf("Error en linea: %s\n",line);
        printf("Ejemplo: *C\n");
        printf("1111-Pedro Perez-Caracas-11111\n");
        return TRUE;
    }

    if (listClients == TRUE){
        for (int i = 0; i<strlen(line); i++){
            if (line[i]=='-') sepCount++;
        }

        if (sepCount>3 || sepCount<3){
            printf("ERROR: Cada dato debe estar separado por un unico guion (-)\n");
            printf("Es posible que falten o sobren datos en la siguiente linea: %s", line);
            printf("Formato: Cedula-Nombre-Ciudad-Telefono\n");
            printf("Ejemplo de uso correcto: 1111-Pedro Perez-Caracas-11111\n");
            return TRUE;
        }
        else{
            sepCount=0;
            j = 0;
        }

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
                switch (data){
                    case 0:
                        auxi = strtol(dat, &ptr, 10);
                        if (auxi == 0 || strlen(ptr)>1){
                            isThereError = TRUE;
                            printf("ERROR: Numero de cedula de el cliente debe ser un numero entero positivo mayor a cero \n");
                            printf("Simbolo detectado: %s\n", dat);
                        }
                        ptr=NULL;
                    break;
                    case 1: 
                        if (strlen(dat)>150){
                            isThereError = TRUE;
                            printf("Nombre de cliente no puede ser mayor de 149 caracteres\n");
                        }
                    break;
                    case 2:
                        if (strlen(dat)>200){
                            isThereError = TRUE;
                            printf("Ciudad no puede ser mayor a 199 caracteres\n");
                        }
                    break;
                    case 3:
                        if (strlen(dat)>30){
                            isThereError = TRUE;
                            printf("Numero de telefono no puede ser mayor a 29 caracteres\n");
                        } 
                        data=-1;
                        clients++;
                        listClients = FALSE;
                    break;    
                }
            strcpy(dat,"");
            data++;
            continue;
            } // End of if (line[i]=='-' || i==strlen(line))
            } //End of for
        } // End of if listClients == TRUE


/******************************************** ACCOUNTS **********************************************/
    if (line[0]=='*' && line[1]=='B'){
        listClients = FALSE;
        listAccounts = TRUE;
        listTrans = FALSE;
        accounts = 0;
        continue;
    }

    }
    fclose(input);
    return isThereError;
}

void loadFromFile(client **p){
    char path[1024];
    FILE *fp;
    boolean theresError = FALSE;
        printf("Especifique ruta de archivo\n");
        scanf("%s", &path);
        fp = fopen(path, "r");
            if (fp == NULL){
                printf("No fue posible abrir el archivo\n");
            }
            else {
                printf("Archivo cargado con exito\n");
                theresError = errorInFileStructure(fp);
                if (!theresError){
                    //printf("Archivo sin errores\n");
                    fp = fopen (path, "r");
                    fileExists(fp, p);
                }
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