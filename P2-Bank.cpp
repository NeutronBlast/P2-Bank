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

boolean isUnique (int * x, int capacity, int number){
    for (int i = 0; i<=capacity; i++){
        if (number == x[i]) return FALSE;
    }
    return TRUE;
}

boolean bankAccountExists (int * x, int * y, int capacity, int number, int codbank){
    for (int i = 0; i<=capacity; i++){
        if (number == x[i] && codbank == y[i]) return TRUE;
    }
    return FALSE;
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
                            //printf("Tipo de transaccion %d\n", auxt);
                            break;
                        case 1:
                        /* Issuer's Account's ID */
                            auxid = strtol(dat, NULL, 10); 
                            //printf("Numero de cuenta del emisor %d\n",auxid);
                            break;
                        case 2:
                            auxsecondAID = strtol(dat,NULL,10);
                            //printf("Numero de cuenta de la otra persona involucrada %d\n",auxsecondAID);
                            break;
                        case 3:
                            strcpy(date,"");
                            strcpy(date,dat);
                            break;
                        case 4: 
                            char *ptr;
                            auxbal=strtod(dat, &ptr);
                            //printf("Monto %lf\n", auxbal);
                            break;
                        case 5:
                            transcode = strtol(dat,NULL,10);
                            //printf("Codigo de transaccion %d\n", transcode);
                            break;
                        case 6:
                            strcpy(description,"");
                            strcpy(description,dat);
                            break;
                        case 7:
                            auxsecondID = strtol (dat, NULL, 10);
                            //printf("Cedula de la otra persona involucrada %d\n", auxsecondID);
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
    int clients = -1, accounts = -1, transactions = -1, data = 0, j = 0, sepCount = 0;
    boolean listClients = FALSE;
    boolean listAccounts = FALSE;
    boolean listTrans = FALSE;
    boolean isThereError = FALSE;

/******************************** AUX VARS **********************************************/
    int auxi = 0;
    double auxd = 0;
    int capacity = 5;
    int auxAC = 0;
    int auxCB = 0;
    int auxTC = 0;
    int * people = (int*)malloc(sizeof(int)*capacity);
    int * accNumbers = (int*)malloc(sizeof(int)*capacity);
    int * bankIDs = (int*)malloc(sizeof(int)*capacity);
    int * transCodes = (int*)malloc(sizeof(int)*capacity);
    int usedp = 0;
    int useda = 0;
    int usedt = 0;

    while (!feof(input) && !ferror(input)){
        fgets(line, 1000, input);

    if (line[0]=='\n') continue;

/************************************* CLIENTS **************************************************/
    if (line[0]=='*' && line[1]=='C'){
        listClients = TRUE;
        listAccounts = FALSE;
        listTrans = FALSE;
        accounts = -1;
        clients = 0;
        transactions = -1;
        continue;
    }

    if ((clients == 0 && line[0]!='*' && line[1]!='C' && listClients == FALSE)){
        printf("ERROR: Debe existir una linea *C para denotar a los clientes\n");
        printf("Error en linea: %s\n",line);
        printf("Ejemplo: *C\n");
        printf("1111-Pedro Perez-Caracas-11111\n");
        return TRUE;
    }

    if (listClients == TRUE && line[0]!='*'){
        for (int i = 0; i<strlen(line); i++){
            if (line[i]=='-') sepCount++;
        }

        if ((sepCount>3 || sepCount<3) && line[0]!='*'){
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
                            printf("Simbolo detectado: %s en linea %s\n", dat, line);
                        }
                        else{
                        }
                        ptr=NULL;
                    break;
                    case 1: 
                        if (strlen(dat)>150){
                            isThereError = TRUE;
                            printf("ERROR: Nombre de cliente no puede ser mayor de 149 caracteres\n");
                            printf("Linea: %s\n",line);
                        }
                    break;
                    case 2:
                        if (strlen(dat)>200){
                            isThereError = TRUE;
                            printf("ERROR: Ciudad no puede ser mayor a 199 caracteres\n");
                            printf("Linea: %s\n",line);
                        }
                    break;
                    case 3:
                        if (strlen(dat)>30){
                            isThereError = TRUE;
                            printf("ERROR: Numero de telefono no puede ser mayor a 29 caracteres\n");
                            printf("Linea: %s\n", line);
                        } 
                        data=-1;
                        clients++;

                        /* For the array*/
                        if (usedp>0)
                            if (isUnique(people,capacity,auxi) == FALSE){
                                printf("ERROR: Numero de cedula en linea %s ya existe en el sistema\n", line);
                                return TRUE;
                            }

                        people[usedp] = auxi;
                        usedp++;
                            if (usedp == 5){
                                capacity*=2;
                                /* Expand vector capacity */
                                people = (int*)realloc(people,sizeof(int)*capacity);
                            }
                        //printf("Client[%d] = %d\n", usedp-1,auxi);
                        //listClients = FALSE;
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
        clients = -1;
        accounts = 0;
        transactions = -1;
        continue;
    }

    if ((accounts == 0 && line[0]!='*' && line[1]!='B' && listAccounts == FALSE && listClients == FALSE)){
        printf("ERROR: Debe existir una linea *B para denotar las cuentas bancarias\n");
        printf("Error en linea: %s",line);
        printf("Ejemplo: *B\n");
        printf("1111-1-2-11000\n");
        return TRUE;
    }

    if (listAccounts == TRUE && line[0]!='*'){
        for (int i = 0; i<strlen(line); i++){
            if (line[i]=='-') sepCount++;
        }

        if (sepCount>3 || sepCount<3){
            printf("ERROR: Cada dato debe estar separado por un unico guion (-)\n");
            printf("Es posible que falten o sobren datos en la siguiente linea: %s", line);
            printf("Formato: Numero de cuenta-Codigo de banco-Tipo de cuenta-Saldo\n");
            printf("Ejemplo de uso correcto: 1122-2-1-11001\n");
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
                            printf("ERROR: Numero de cuenta de el cliente debe ser un numero entero positivo mayor a cero \n");
                            printf("Simbolo detectado: %s en linea %s\n", dat, line);
                        }
                        else{
                            auxAC = auxi;
                        }
                        ptr=NULL;
                        
                    break;
                    case 1: 
                        auxi = strtol(dat, &ptr, 10);
                        if (auxi == 0 || strlen(ptr)>1){
                            isThereError = TRUE;
                            printf("ERROR: Codigo de banco debe ser un numero entero positivo mayor a cero \n");
                            printf("Simbolo detectado: %s en linea %s\n", dat, line);
                        }
                        else{
                            auxCB = auxi;
                        }
                        ptr=NULL;
                    break;
                    case 2:
                        auxi = strtol(dat, &ptr, 10);
                        if (auxi == 0 || strlen(ptr)>1){
                            isThereError = TRUE;
                            printf("ERROR: Tipo de cuenta debe ser un numero entero positivo mayor a cero \n");
                            printf("Simbolo detectado: %s en linea %s\n", dat, line);
                        }
                        if (auxi != 1 && auxi != 2){
                            isThereError = TRUE;
                            printf("ERROR: Tipo de cuenta debe ser 1: Corriente o 2: Ahorro\n");
                            printf("Se detecto el siguiente simbolo invalido: %s en la linea %s", dat,line);
                        }
                        ptr=NULL;
                    break;
                    case 3:
                        auxd=strtod(dat, &ptr);
                            if (auxd == 0 || strlen(ptr)>1){
                                isThereError = TRUE;
                                printf("ERROR: Balance de cuenta debe ser un numero entero positivo mayor a 0\n");
                                printf("Simbolo detectado: %s en linea %s\n", dat, line);
                            }
                        if (isThereError == FALSE){
                        /* For the array*/
                        if (useda>0)
                            if (bankAccountExists(accNumbers,bankIDs,capacity,auxAC,auxCB) == TRUE){
                                printf("ERROR: Numero de cuenta %d en banco %d ya existe en el sistema, linea: %s\n",auxAC, auxCB, line);
                                return TRUE;
                            }

                        accNumbers[useda] = auxAC;
                        bankIDs[useda] = auxCB;
                        useda++;
                            if (useda == 5){
                                capacity*=2;
                                /* Expand vector capacity */
                                accNumbers = (int*)realloc(accNumbers,sizeof(int)*capacity);
                                bankIDs = (int*)realloc(bankIDs,sizeof(int)*capacity);

                            }
                        //printf("%d - Bank: %d , ID: %d \n", useda-1,auxCB,auxAC);
                        }
                        data=-1;
                        accounts++;
                    break;    
                }
            strcpy(dat,"");
            data++;
            continue;
            } // End of if (line[i]=='-' || i==strlen(line))
            } //End of for
        } // End of if listAccounts == TRUE

/******************************************** TRANSACTIONS **********************************************/
    if (line[0]=='*' && line[1]=='T'){
        listClients = FALSE;
        listAccounts = FALSE;
        listTrans = TRUE;
        transactions = 0;
        continue;
    }

    if ((transactions == 0 && line[0]!='*' && line[1]!='T' && 
    listAccounts == FALSE && listClients == FALSE && listTrans == FALSE)){
        printf("ERROR: Debe existir una linea *T para denotar las transacciones\n");
        printf("Error en linea: %s",line);
        printf("Ejemplo: *T\n");
        printf("2-1122-4444-Mon Apr 10 18:00:00 2018-200-2-Compra online-4444\n");
        return TRUE;
    }

    if (listTrans == TRUE && line[0]!='*'){
        for (int i = 0; i<strlen(line); i++){
            if (line[i]=='-') sepCount++;
        }

        if (sepCount>7 || sepCount<7){
            printf("ERROR: Cada dato debe estar separado por un unico guion (-)\n");
            printf("Es posible que falten o sobren datos en la siguiente linea: %s", line);
            printf("Formato: Tipo de transaccion-Numero de cuenta emisor-Cedula de receptor-");
            printf("Fecha-Monto-Codigo de transaccion-Descripcion-Numero de cuenta de receptor\n");
            printf("1-1111-5555-Sun Feb 15 22:00:00 2018-800-13-reparacion de computador-5555\n");
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
                            printf("ERROR: Tipo de transaccion debe ser numero entero positivo mayor a cero \n");
                            printf("Simbolo detectado: %s en linea %s\n", dat, line);
                        }
                        if (auxi != 1 && auxi != 2){
                            isThereError = TRUE;
                            printf("ERROR: Tipo de transaccion debe ser 1: Pago o 2: Cobro\n");
                            printf("Se detecto el siguiente simbolo invalido: %s en la linea %s", dat,line);
                        }
                        ptr=NULL;
                    break;
                    case 1:
                    auxi = strtol(dat, &ptr, 10);
                        if (auxi == 0 || strlen(ptr)>1){
                            isThereError = TRUE;
                            printf("ERROR: Numero de cuenta del emisor debe ser numero entero positivo mayor a cero \n");
                            printf("Simbolo detectado: %s en linea %s\n", dat, line);
                        }
                    ptr=NULL;
                    break;
                    case 2:
                        auxi = strtol(dat, &ptr, 10);
                        if (auxi == 0 || strlen(ptr)>1){
                            isThereError = TRUE;
                            printf("ERROR: Cedula del receptor debe ser numero entero positivo mayor a cero \n");
                            printf("Simbolo detectado: %s en linea %s\n", dat, line);
                        }
                    ptr=NULL;
                    break;
                    case 3:
                        char auxs[40];
                        boolean dateFormatError;
                        strncpy(auxs, dat, 3);
                        auxs[3]='\0';
                        /* Day */
                        if (strcmp("Mon",auxs) != 0 && strcmp("Tue",auxs) != 0 && strcmp("Wed",auxs) != 0
                        && strcmp("Thu",auxs) != 0 && strcmp("Fri",auxs) != 0 && strcmp("Sat",auxs) != 0
                        && strcmp("Sun",auxs) != 0){
                            dateFormatError = TRUE;
                        }
                        
                        strcpy(auxs,"");
                        strncpy(auxs, dat+4, 3);
                        auxs[3]='\0';
                        
                        /* Month */
                        if (strcmp("Jan",auxs) != 0 && strcmp("Feb",auxs) != 0 && strcmp("Mar",auxs) != 0
                        && strcmp("Apr",auxs) != 0 && strcmp("May",auxs) != 0 && strcmp("Jun",auxs) != 0
                        && strcmp("Jul",auxs) != 0 && strcmp("Aug",auxs) != 0 && strcmp("Sep",auxs) != 0
                        && strcmp("Oct",auxs) != 0 && strcmp("Nov",auxs) != 0 && strcmp("Dec",auxs) != 0){
                            dateFormatError = TRUE;
                        }

                        /* Date */
                        strcpy(auxs,"");
                        strncpy(auxs, dat+8, 2);
                        auxs[2]='\0';

                        if (auxs[0]==' ' || auxs[0]=='0'){
                            if (auxs[1]<48 || auxs[1]>57)
                                dateFormatError = TRUE;
                            ptr=NULL;
                        }
                        else{
                            auxi = strtol(auxs, &ptr, 10);
                                if (auxi == 0 || auxi>31){
                                    dateFormatError = TRUE;
                                }
                            ptr=NULL;

                        }

                        /* Hour */

                        strcpy(auxs,"");
                        strncpy(auxs, dat+11, 2);
                        auxs[2]='\0';


                        if (auxs[0]=='0' || auxs[1]=='0'){
                            ptr=NULL;
                        }
                        else{
                            auxi = strtol(auxs, &ptr, 10);
                                if (auxi == 0 || auxi>23){
                                    dateFormatError = TRUE;
                                }
                            ptr=NULL;
                        }

                        /* Minutes */

                        strcpy(auxs,"");
                        strncpy(auxs, dat+14, 2);
                        auxs[2]='\0';

                        if (auxs[0]=='0' || auxs[1]=='0'){
                            ptr=NULL;
                        }
                        else{
                            auxi = strtol(auxs, &ptr, 10);
                                if (auxi == 0 || auxi>59){
                                    dateFormatError = TRUE;
                                }
                            ptr=NULL;
                        }

                        /* Seconds */

                        strcpy(auxs,"");
                        strncpy(auxs, dat+17, 2);
                        auxs[2]='\0';

                        if (auxs[0]=='0' || auxs[1]=='0'){
                            ptr=NULL;
                        }
                        else{
                            auxi = strtol(auxs, &ptr, 10);
                                if (auxi == 0 || auxi>59){
                                    dateFormatError = TRUE;
                                }
                            ptr=NULL;
                        }

                        /* Year */

                        strcpy(auxs,"");
                        strncpy(auxs, dat+20, 4);
                        auxs[4]='\0';

                        auxi = strtol(auxs, &ptr, 10);
                            if (auxi == 0){
                                dateFormatError = TRUE;
                            }
                        ptr=NULL;

                        if (dateFormatError == TRUE){
                            printf("Formato de fecha invalido. Ejemplo valido: Sun Aug 14 14:00:00\n");
                            printf("Simbolo invalido detectado en linea: %s\n",line);
                        }
                    break;

                    case 4: 
                        auxd=strtod(dat, &ptr);
                            if (auxd == 0 || strlen(ptr)>1){
                                isThereError = TRUE;
                                printf("ERROR: Monto de transaccion debe ser un numero entero positivo mayor a 0\n");
                                printf("Simbolo detectado: %s en linea %s\n", dat, line);
                            }
                        ptr=NULL;
                    break;
                    case 5:
                        auxi = strtol(dat, &ptr, 10);
                        if (auxi == 0 || strlen(ptr)>1){
                            isThereError = TRUE;
                            printf("ERROR: Codigo de transaccion debe ser un numero entero positivo mayor a cero \n");
                            printf("Simbolo detectado: %s en linea %s\n", dat, line);
                        }
                        else{
                            auxTC = auxi;
                        }

                        ptr=NULL;
                    break;
                    case 6:
                        if (strlen(dat)>40){
                            isThereError = TRUE;
                            printf("ERROR: Descripcion de la transaccion no debe sobrepasar los 40 caracteres\n");
                            printf("Detectado en linea %s\n",line);
                        }
                    break;    
                    case 7:
                        auxi = strtol(dat, &ptr, 10);
                        if (auxi == 0 || strlen(ptr)>1){
                            isThereError = TRUE;
                            printf("ERROR: Numero de cuenta de receptor debe ser un numero entero positivo mayor a cero \n");
                            printf("Simbolo detectado: %sEn linea %s\n", dat, line);
                        }
                        ptr=NULL;

                    /* For the array*/
                        if (usedt>0)
                            if (isUnique(transCodes,capacity,auxTC) == FALSE){
                                printf("ERROR: Codigo de transaccion %d ya existe en el sistema, linea %s \n", auxTC, line);
                                return TRUE;
                            }

                        transCodes[usedt] = auxTC;
                        usedt++;
                            if (usedt == 5){
                                capacity*=2;
                                /* Expand vector capacity */
                                transCodes = (int*)realloc(transCodes,sizeof(int)*capacity);
                            }
                        //printf("Trans[%d] = %d\n", usedp-1,auxTC);
                        data=-1;
                        transactions++;
                    break;
                }
            strcpy(dat,"");
            data++;
            continue;
            } // End of if (line[i]=='-' || i==strlen(line))
            } //End of for
        } // End of if listTrans == TRUE

    }
    fclose(input);
    //printf("Clients total %d\n",usedp);
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
            system("pause");
            }
}

void showMenu(){
    client *c = NULL;
    int op=-1;
        while (op){
            printf("\n*** Sistema de pagos y cobros P2Bank ***\n\n");
            printf("    \t 1. Cuentas y clientes\n");
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