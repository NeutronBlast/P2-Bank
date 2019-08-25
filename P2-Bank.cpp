#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum {FALSE = 0, TRUE} boolean;


typedef struct trans {
    int code;
    int secondPartysAN;
    double amount;
    int type;
    char date [100];
    int secondPartysId;
    int secondPartysCB;
    char description [41];
    trans *next;
} transaction;


typedef struct acct{
    int id;
    int bank;
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

client * clientExists (client *p, int id){
    client *t = p;
        while (t)
        {
            if (t->id == id) 
                return t;
            t=t->next;
        }
    return NULL;
}

void addClient (client ** p){
    client *ax = new client, *t = *p, *verif = NULL;
    char dat[1000]; char *ptr = NULL;
    int auxi = 0;
    boolean alrExists;

    strcpy(dat,"");
    printf("********** AGREGAR NUEVO CLIENTE **************\n");

    /* Ask for the data */
    do
    {
        printf("Numero de cedula\n");
        scanf("%s",&dat);
        auxi = strtol(dat, &ptr, 10);
            if (auxi == 0 || strlen(ptr)>1){
                printf("ERROR: Numero de cedula de el cliente debe ser un numero entero positivo mayor a cero \n");
                }
            verif = clientExists(t,auxi);
            if (verif){
                printf("ERROR: Numero de cedula ingresado ya existe en el sistema\n");
            }
    } while (auxi == 0 || strlen(ptr)>1 || verif);

    ax->id = auxi;
    
    strcpy(dat,"");
    fflush(stdin);

    do
    {
        printf("Nombre de cliente (No mayor a 149 caracteres)\n");
        scanf("%s",&dat);
            if (strlen(dat)>150){
                printf("ERROR: Nombre de cliente no puede ser mayor de 149 caracteres\n");
            }
    } while (strlen(dat)>150);
    
    strcpy(ax->name,dat);
    strcpy(dat,"");
    fflush(stdin);

    do
    {
        printf("Ciudad (No mayor a 199 caracteres)\n");
        scanf("%s",&dat);
            if (strlen(dat)>199){
                printf("ERROR: Ciudad no puede ser mayor a 199 caracteres\n");
            }
    } while (strlen(dat)>199);

    strcpy(ax->city,dat);
    strcpy(dat,"");

    do
    {
        printf("Telefono (No mayor a 29 caracteres)\n");
        scanf("%s",&dat);
            if (strlen(dat)>29){
                printf("ERROR: Numero de telefono no puede ser mayor a 29 caracteres\n");
            }
    } while (strlen(dat)>29);

    strcpy(ax->phone,dat);

    if (t==NULL){
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
            t->next->anext = NULL;
    }
}

void deleteClient (client **p, int n){
    client **ppn = p;           /* pointer to pointer to node*/
    client *pn = *p;            /* pointer to node */

    for (; pn; ppn = &pn->next, pn = pn->next) {
        if (pn->id == n) {
            *ppn = pn->next;    /* set address to next */
            delete(pn);
            break;
        }
    }
}

void modifyClient (client ** p){
    client *ax = new client, *t = *p, *verif = NULL;
    char dat[1000]; char *ptr = NULL;
    int auxi = 0, oldID = 0;
    boolean alrExists;

    strcpy(dat,"");

    // ID number to modify the person with that ID 
    do
    {
        printf("Numero de cedula de cliente a modificar\n");
        scanf("%s",&dat);
        auxi = strtol(dat, &ptr, 10);
            if (auxi == 0 || strlen(ptr)>1){
                printf("ERROR: Numero de cedula de el cliente debe ser un numero entero positivo mayor a cero \n");
                }
            verif = clientExists(t,auxi);
            if (!verif){
                printf("ERROR: Numero de cedula ingresado no existe en el sistema\n");
            }
    } while (auxi == 0 || strlen(ptr)>1 || !verif);

    // Ask for the data 
    oldID = auxi;

    do
    {
        printf("Nuevo numero de cedula\n");
        scanf("%s",&dat);
        auxi = strtol(dat, &ptr, 10);
            if (auxi == 0 || strlen(ptr)>1){
                printf("ERROR: Numero de cedula de el cliente debe ser un numero entero positivo mayor a cero \n");
                }
            verif = clientExists(t,auxi);
            if (verif && verif->id == auxi){
                printf("Numero de cedula ingresado es el mismo que estaba anteriormente en este cliente\n");
                ax->id = verif->id;
                break;
            }
            if (verif){
                printf("ERROR: Numero de cedula ingresado ya existe en el sistema\n");
            }
    } while (auxi == 0 || strlen(ptr)>1 || verif);

    ax->id = auxi;
    do
    {
        printf("Nuevo nombre de cliente (No mayor a 149 caracteres)\n");
        scanf("%s",&dat);
            if (strlen(dat)>150){
                printf("ERROR: Nombre de cliente no puede ser mayor de 149 caracteres\n");
            }
    } while (strlen(dat)>150);
    
    strcpy(ax->name,dat);
    strcpy(dat,"");
    fflush(stdin);

    do
    {
        printf("Nueva ciudad (No mayor a 199 caracteres)\n");
        scanf("%s",&dat);
            if (strlen(dat)>199){
                printf("ERROR: Ciudad no puede ser mayor a 199 caracteres\n");
            }
    } while (strlen(dat)>199);

    strcpy(ax->city,dat);
    strcpy(dat,"");

    do
    {
        printf("Nuevo telefono (No mayor a 29 caracteres)\n");
        scanf("%s",&dat);
            if (strlen(dat)>29){
                printf("ERROR: Numero de telefono no puede ser mayor a 29 caracteres\n");
            }
    } while (strlen(dat)>29);

    strcpy(ax->phone,dat);

    ax->next = NULL;
    ax->anext = NULL;

    if (t->id == oldID && t->next == NULL){
        (*p) = ax;
    }
    else if (t->id == oldID && t->next != NULL){
        t->id = auxi;
        strcpy(t->name,ax->name);
        strcpy(t->city,ax->city);
        strcpy(t->phone,ax->phone);
    }
	else{
		while ((t->next != NULL) && (t->next->id != oldID)) { 
			t = t->next;
		}
    if (ax->anext != NULL)
        ax->anext = t->next->anext;

    if (ax->anext != NULL){
            ax->anext->tnext = t->next->anext->tnext;
        }
    ax->next = t->next->next;
    deleteClient(&t,t->next->id);
	t->next = ax;
    }
}

account * search (client *p, int accountID, int codbank){
	account *t = NULL;
    if (p->anext != NULL)
        t = p->anext;

    client * h = p;

    while (h){
        if (h->anext != NULL){
            t = h->anext;
	        while (t) {
		        if ((t->id) == accountID && t->bank == codbank) {
                    return t;
		        }
		    t = t->next;
	        }
        }
    h=h->next;
    }
    return t;
}

account * searchbyCID (client *p, int accountID, int codbank){
    account *t = NULL;
    if (p->anext != NULL)
        t = p->anext;

    client * h = p;

    if (h){
        if (h->anext != NULL){
            t = h->anext;
	        while (t) {
		        if ((t->id) == accountID && t->bank == codbank) {
                    return t;
		        }
		    t = t->next;
	        }
        }
    }
    return t;
}

account * isIDUnique (client *p, int accountID, int codbank){
	account *t = NULL;
    if (p->anext != NULL)
        t = p->anext;

    client * h = p;

    while (h){
        if (h->anext != NULL){
            t = h->anext;
	        while (t) {
		        if ((t->id) == accountID && t->bank == codbank) {
                    return t;
		        }
		    t = t->next;
	        }
        }
    h=h->next;
    }
    return t;
}

void addAccount (client ** p){
    client *t = *p, *verif = NULL;
    char dat[1000]; char *ptr = NULL;
    int auxi = 0;
    double auxd = 0;
    boolean alrExists;

    strcpy(dat,"");

    /* Ask for the data */
    printf("********** AGREGAR NUEVA CUENTA **************\n");

    do
    {
        printf("Numero de cedula asociado\n");
        scanf("%s",&dat);
        auxi = strtol(dat, &ptr, 10);
            if (auxi == 0 || strlen(ptr)>1){
                printf("ERROR: Numero de cedula de el cliente debe ser un numero entero positivo mayor a cero \n");
                }
            verif = clientExists(t,auxi);
            if (!verif){
                printf("ERROR: Numero de cedula ingresado no existe en el sistema\n");
            }
    } while (auxi == 0 || strlen(ptr)>1 || !verif);
    
    strcpy(dat,"");
    fflush(stdin);

    /* New data */

    do
    {
        printf("Numero de cuenta\n");
        scanf("%s",&dat);
        auxi = strtol(dat, &ptr, 10);
            if (auxi == 0 || strlen(ptr)>1){
                printf("ERROR: Numero de cuenta de el cliente debe ser un numero entero positivo mayor a cero \n");
                }
    } while (auxi == 0 || strlen(ptr)>1);

    account * acc = new account;
    account * acc2;
    account *verify = NULL;
    strcpy(dat,"");
    ptr = NULL;
    acc->id = auxi;

    //Bank code

    do
    {
        printf("Codigo de banco\n");
        scanf("%s",&dat);
        auxi = strtol(dat, &ptr, 10);
            if (auxi == 0 || strlen(ptr)>1){
                printf("ERROR: Codigo de banco debe ser un numero entero positivo mayor a cero \n");
            }
            verify = isIDUnique(t,acc->id,auxi);
            if (verify){
                printf("ERROR: Codigo de banco y numero de cuenta asociados ya existen en el sistema\n");
            }
    } while (auxi == 0 || strlen(ptr)>1 || verify);
    acc->bank = auxi;
    strcpy(dat,"");
    ptr = NULL;

    //Account type
    do
    {
        printf("Tipo de cuenta\n");
        scanf("%s",&dat);
        auxi = strtol(dat, &ptr, 10);
            if (auxi == 0 || strlen(ptr)>1){
                printf("ERROR: Tipo de cuenta debe ser un numero entero positivo mayor a cero \n");
                printf("1: Cuenta corriente 2: Cuenta de ahorro\n");
            }
            else if (auxi != 1 && auxi != 2){
                printf("ERROR: Tipo de cuenta debe ser 1: Corriente o 2: Ahorro\n");
            }
    } while (auxi == 0 || strlen(ptr)>1 || (auxi!=1 && auxi!=2));
    
    acc->type = auxi;
    strcpy(dat,"");
    fflush(stdin);
    ptr = NULL;

    //Balance
    do
    {
        printf("Saldo\n");
        scanf("%s",&dat);
        auxd=strtod(dat, &ptr);
            if (auxd == 0 || strlen(ptr)>1){
                printf("ERROR: Saldo de cuenta debe ser un numero positivo mayor a cero \n");
            }
    } while (auxd == 0 || strlen(ptr)>1);

    acc->balance = auxd;
    strcpy(dat,"");

    /*Insert at the end of the list*/
        if (acc==NULL){
            exit(1);
        }

        if (verif->anext == NULL) 
        {
            verif->anext = acc;
            acc->next = NULL;
            acc->tnext = NULL;
        }

        else{
        acc->next = NULL;
        acc2 = verif->anext;
            while (acc2->next != NULL){
                acc2 = acc2->next;
            }
        acc2->tnext = NULL;
        acc2->next = acc;
        acc->tnext = NULL;
        }

}

void deleteAccount (client **p, int n, int accid, int codbank){
    client *t = *p;
    account * h = NULL;
    
    if (t){
        h = t->anext;
        if (t->id == n){
            if (h){
                if (h->id == accid && h->bank == codbank){
                    (*p)->anext = (*p)->anext->next;
                    delete(h);
                }
            else{
                while (h->next && h->next->id != accid && h->next->bank != codbank)
                    h = h->next;
            if (h->next){
                account * ax = h->next;
                h->next = h->next->next;
                delete(ax);
            }
            }
            }
        }
    }
}

void modifyAccount (client ** p){
    client *t = *p, *verif = NULL;
    account * ax = new account, *verify = NULL;
    char dat[1000]; char *ptr = NULL;
    int auxi = 0, cID = 0, oldID = 0, oldCB = 0, auxi2 = 0; 
    double auxd = 0;
    boolean ignore = FALSE;

    strcpy(dat,"");

    // ID number to modify the person with that ID 
    do
    {
        printf("Numero de cedula de cliente a modificar\n");
        scanf("%s",&dat);
        auxi = strtol(dat, &ptr, 10);
            if (auxi == 0 || strlen(ptr)>1){
                printf("ERROR: Numero de cedula de el cliente debe ser un numero entero positivo mayor a cero \n");
                }
            verif = clientExists(t,auxi);
            if (!verif){
                printf("ERROR: Numero de cedula ingresado no existe en el sistema\n");
            }
    } while (auxi == 0 || strlen(ptr)>1 || !verif);

    cID = auxi;
    strcpy(dat,"");

    do{
        printf("Numero de cuenta\n");
        scanf("%s",&dat);
        oldID = strtol(dat, &ptr, 10);
            if (oldID == 0 || strlen(ptr)>1){
                printf("ERROR: Numero de cuenta de el cliente debe ser un numero entero positivo mayor a cero \n");
            }

        strcpy(dat,"");
        printf("Codigo de banco\n");
        scanf("%s",&dat);
        oldCB = strtol(dat, &ptr, 10);
            if (oldCB == 0 || strlen(ptr)>1){
                printf("ERROR: Codigo de banco de cuenta debe ser un numero entero positivo mayor a cero \n");
            }
        verify = searchbyCID(verif,oldID,oldCB);

            if (!verify){
                printf("ERROR: Numero cuenta ingresado asociado a este numero de cedula no existe en el sistema\n");
            }
        } while (oldID == 0 || oldCB == 0 || strlen(ptr)>1 || !verify);
    

    /* New data */
    do
    {
        printf("Nuevo numero de cuenta\n");
        scanf("%s",&dat);
        auxi = strtol(dat, &ptr, 10);
            if (auxi == 0 || strlen(ptr)>1){
                printf("ERROR: Numero de cuenta de el cliente debe ser un numero entero positivo mayor a cero \n");
                }

        strcpy(dat,"");
        printf("Nuevo codigo de banco\n");
        scanf("%s",&dat);
        auxi2 = strtol(dat, &ptr, 10);
            if (auxi2 == 0 || strlen(ptr)>1){
                printf("ERROR: Numero de cuenta de el cliente debe ser un numero entero positivo mayor a cero \n");
                }
            verify = searchbyCID(verif,auxi,auxi2);
            if (verify && verify->id == auxi && verify->bank == auxi2){
                printf("Numero de cedula ingresado es el mismo que estaba anteriormente en este cliente\n");
                ax->id = verify->id;
                ax->bank = verify->bank;
                break;
            }

    } while (auxi == 0 || auxi2 == 0 || strlen(ptr)>1);

    ptr = NULL;
    ax->id = auxi;
    ax->bank = auxi2;
    

    //Account type 

    do
    {
        printf("Nuevo tipo de cuenta\n");
        scanf("%s",&dat);
        auxi = strtol(dat, &ptr, 10);
            if (auxi == 0 || strlen(ptr)>1){
                printf("ERROR: Tipo de cuenta debe ser un numero entero positivo mayor a cero \n");
            }
            
            if (auxi != 1 && auxi != 2){
                printf("ERROR: Tipo de cuenta debe ser 1: Corriente o 2: Ahorro\n");
            }
    } while (auxi == 0 || strlen(ptr)>1 || (auxi != 1 && auxi != 2));
    
    ptr = NULL;
    ax->type = auxi;
    strcpy(dat,"");
    fflush(stdin);

    //Balance
    do
    {
        printf("Nuevo saldo\n");
        scanf("%s",&dat);
        auxd=strtod(dat, &ptr);
            if (auxd == 0 || strlen(ptr)>1){
                printf("ERROR: Balance de cuenta debe ser un numero entero positivo mayor a 0\n");
            }
    } while (auxd == 0 || strlen(ptr)>1);

    ax->balance = auxd;
    strcpy(dat,"");
    ptr = NULL;

    ax->next = NULL;
    ax->tnext = NULL;

    if (t)
        if (t->id != cID)
		    while ((t != NULL) && (t->id != cID)) { 
			    t = t->next;
		    }

    account *h = t->anext;

    if (h->id == oldID && h->bank == oldCB && h->next == NULL){
        t->anext = ax;
    }
    else if (h->id == oldID && h->bank == oldCB && h->next != NULL){
        ax->next = h->next;
        t->anext = ax;
    }
    else {
        while ((h->next != NULL && h->next->id != oldID && h->next->bank != oldCB)){
            h = h->next;
        }
        ax->next = h->next->next;
        deleteAccount(&t, t->id, h->next->id, h->next->bank);
        h->next = ax;
    }
}



void linkAccountMenu(client ** p){
    int op=-1, auxi = 0, auxAC = 0, auxCB = 0;
    char * ptr = NULL; char dat [1000];
    client * t = *p, *verif =  NULL;
    account *verify =  NULL;
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
                addClient(&t);
                printf("Cliente agregado con exito\n");
                system("pause");
                system("cls");
                break;

            case 2:
                modifyClient(&t);
                printf("Cliente modificado con exito\n");
                system("pause");
                system("cls");
                break;
            
            case 3:
            strcpy(dat,"");
                do
                {
                    printf("Numero de cedula\n");
                    scanf("%s",&dat);
                    auxi = strtol(dat, &ptr, 10);
                        if (auxi == 0 || strlen(ptr)>1){
                            printf("ERROR: Numero de cedula de el cliente debe ser un numero entero positivo mayor a cero \n");
                        }
                        verif = clientExists(t,auxi);

                        if (!verif){
                            printf("ERROR: Numero de cedula ingresado no existe en el sistema\n");
                        }
                } while (auxi == 0 || strlen(ptr)>1 || !verif);

                if (t->id == auxi){
                    (*p) = (*p)->next;
                    printf("Cliente eliminado con exito\n");
                    system("pause");
                    system("cls");
                    return;
                }
                deleteClient(&t,auxi);
                printf("Cliente eliminado con exito\n");
                system("pause");
                system("cls");
                break;

            case 4:
                addAccount(&t);
                printf("Cuenta añadida con exito\n");
                system("pause");
                system("cls");
                break;

            case 5:
                modifyAccount(&t);
                printf("Cuenta modificada con exito\n");
                system("pause");
                system("cls");
                break;

            case 6:
            strcpy(dat,"");
                do
                {
                    printf("Numero de cedula\n");
                    scanf("%s",&dat);
                    auxi = strtol(dat, &ptr, 10);
                        if (auxi == 0 || strlen(ptr)>1){
                            printf("ERROR: Numero de cedula de el cliente debe ser un numero entero positivo mayor a cero \n");
                        }
                        verif = clientExists(t,auxi);

                        if (!verif){
                            printf("ERROR: Numero de cedula ingresado no existe en el sistema\n");
                        }
                } while (auxi == 0 || strlen(ptr)>1 || !verif);
                

                do
                {
                    printf("Numero de cuenta\n");
                    scanf("%s",&dat);
                    auxAC = strtol(dat, &ptr, 10);
                        if (auxAC == 0 || strlen(ptr)>1){
                            printf("ERROR: Numero de cuenta de el cliente debe ser un numero entero positivo mayor a cero \n");
                        }

                    printf("Codigo de banco\n");
                    scanf("%s",&dat);
                    auxCB = strtol(dat, &ptr, 10);
                        if (auxAC == 0 || strlen(ptr)>1){
                            printf("ERROR: Codigo de banco de cuenta debe ser un numero entero positivo mayor a cero \n");
                        }
                        verify = searchbyCID(verif,auxAC,auxCB);

                        if (!verify){
                            printf("ERROR: Numero cuenta ingresado asociado a este numero de cedula no existe en el sistema\n");
                        }
                } while (auxAC == 0 || strlen(ptr)>1 || !verify);

                deleteAccount(&t,auxi,auxAC,auxCB);
                printf("Cuenta eliminada con exito\n");
                system("pause");
                system("cls");
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
    int auxid = 0, auxt = 0, auxsecondAID = 0, transcode = 0, auxsecondID = 0, auxb = 0, capacity = 5,
    useda = 0;
    int * accNumbers = (int*)malloc(sizeof(int)*capacity);
    int * bankIDs = (int*)malloc(sizeof(int)*capacity);
    char date [100], description[41];
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
                    t->next->anext = NULL;
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
                useda = 0;
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
                            auxb = strtol(dat,NULL,10);
                            break;
                        case 2:
                            auxt = strtol(dat,NULL,10);
                            break;
                        case 3: 
                            char *ptr;
                            auxbal=strtod(dat, &ptr);
                            //printf("Balance %lf\n", auxbal);
                        accNumbers[useda] = auxid;
                        bankIDs[useda] = auxb;
                        useda++;
                            if (useda == 5){
                                capacity*=2;
                                /* Expand vector capacity */
                                accNumbers = (int*)realloc(accNumbers,sizeof(int)*capacity);
                                bankIDs = (int*)realloc(bankIDs,sizeof(int)*capacity);
                            }

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
                    acc->bank = auxb;
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
                    tt->secondPartysAN = auxsecondID;
                    strcpy(tt->date,date);
                    tt->amount = auxbal;
                    tt->code = transcode;
                    strcpy(tt->description,description);
                    tt->secondPartysId = auxsecondAID;

                    tt->next = NULL;

                    client * as = *p;
                    account * as2 = as->anext;

                int ai = 0;
                as2 = NULL;    
                while (!as2){
                    as2 = search(as, auxid,bankIDs[ai]);
                    ai++;
                }

                tt->secondPartysCB = bankIDs[ai-1];

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

int getTCode (client * p){
    int cont = 0;
    client * t = p;
    account *a = NULL;
    transaction *h = NULL;

        while (t){
            if (t->anext){
                a = t->anext;
                while (a){
                    if (a->tnext){
                        h = a->tnext;
                        while (h){
                            cont++;
                            h = h->next;
                        }
                    }
                    a = a->next;
                }
            }
            t = t->next;
        }
    return cont+1;
}

void processPayment (client ** p, transaction * t, int Iaid, int Iacb){
    client *h = *p;
    transaction * tt2;

    if (t==NULL){
        exit(1);
    }

    t->next = NULL;

    account * as2 = NULL;    
    
    while (!as2){
        as2 = search(h, Iaid, Iacb);
    }

    if (t->type == 1)
        as2->balance = as2->balance-t->amount;
    else as2->balance = as2->balance+t->amount;

    if (as2->tnext == NULL){
        as2->tnext = t;
    }

    else{
        tt2 = as2->tnext;
            while (tt2->next != NULL){
                tt2 = tt2->next;
            }
        tt2->next = t;
    }
    h = h->next;
}

void makePayment(client **p){
    client * t = *p, *verif = NULL;
    account *verify = NULL;
    transaction *op = new transaction, *op2 = new transaction;
    char dat[1000]; char *ptr =  NULL;
    int auxi = 0, create = -1, auxi2 = 0;
    boolean advance = TRUE;
    double auxd = 0;

    /* Data transaction */

    int Iid = 0, Iad = 0, Icb = 0, Rid = 0, Rad = 0, Rcb = 0, Tc = 0;
    double Ta = 0;
    char sttime[41];
    time_t currentTime = time(NULL);
    struct tm *qtime = localtime(&currentTime);

    strcpy(dat,"");

    printf("\n************ REALIZAR PAGO ***************\n\n");


    /* Issuer person's ID */
    do
    {
        printf("Ingrese su numero de cedula\n");
        scanf("%s",&dat);
        auxi = strtol(dat, &ptr, 10);
        verif = clientExists(t,auxi);
            if (!verif){
                printf("\n\nERROR: Numero de cedula ingresado no existe en el sistema\n");

                /* Would you like to link a new client to the system */

                printf("Desea crear un nuevo cliente?\n");
                printf("1. Si\n");
                printf("2. No\n");
                printf("0. Intentar de nuevo\n\n");
                scanf("%d", &create);

                switch (create)
                {
                case 1:
                    addClient(&t);
                    printf("**************Cliente agregado con exito****************\n\n");
                    break;

                case 2:
                    return;
                    break;

                case 0: break;
                
                default:
                    printf("Opcion fuera de rango\n");
                    break;
                }
            }
    } while (!verif);

    Iid = auxi;
    ptr = NULL;

    /* Issuer's account ID */

    strcpy(dat,"");
    create = -1;

    do{
        printf("Numero de cuenta\n");
        scanf("%s",&dat);
        auxi = strtol(dat, &ptr, 10);

        strcpy(dat,"");
        printf("Codigo de banco\n");
        scanf("%s",&dat);
        auxi2 = strtol(dat, &ptr, 10);
        verify = searchbyCID(verif,auxi,auxi2);

            if (!verify){
                printf("\n\nERROR: Numero cuenta ingresado asociado a este numero de cedula no existe en el sistema\n");

                /* Would you like to link a new account to the system */

                printf("Desea crear una nueva cuenta?\n");
                printf("1. Si\n");
                printf("2. No\n");
                printf("0. Intentar de nuevo\n\n");
                scanf("%d", &create);

                switch (create)
                {
                case 1:
                    addAccount(&t);
                    printf("\n**************Cuenta agregada con exito****************\n\n");
                    break;

                case 2:
                    return;
                    break;

                case 0: break;
                
                default:
                    printf("Opcion fuera de rango\n");
                    break;
                }
            }
        } while (!verify);

    Icb = auxi2; Iad = auxi;
    ptr = NULL;
    create = -1;

    /* Transaction's amount */

    do {
        advance = TRUE;
        printf("Monto de la transaccion\n");
        scanf("%s", &dat);

        auxd = strtod(dat, &ptr);
            if (auxd == 0 || strlen(ptr)>1){
                printf("Monto de la transaccion debe ser un numero positivo mayor a cero\n");
            }
            if (verify->balance < auxd){
                printf("Saldo insuficiente para este monto de transaccion\n");
                advance = FALSE;
            }
    } while (auxd == 0 || strlen(ptr)>1 || advance == FALSE);

    Ta = auxd;
    ptr = NULL;

    /* Receiver person's ID */
    do
    {
        printf("Ingrese numero de cedula del receptor\n");
        scanf("%s",&dat);
        auxi = strtol(dat, &ptr, 10);
        verif = clientExists(t,auxi);
            if (!verif){
                printf("\n\nERROR: Numero de cedula ingresado no existe en el sistema\n");

                /* Would you like to link a new client to the system */

                printf("Desea crear un nuevo cliente?\n");
                printf("1. Si\n");
                printf("2. No\n");
                printf("0. Intentar de nuevo\n\n");
                scanf("%d", &create);

                switch (create)
                {
                case 1:
                    addClient(&t);
                    printf("**************Cliente agregado con exito****************\n\n");
                    break;

                case 2:
                    return;
                    break;

                case 0: break;
                
                default:
                    printf("Opcion fuera de rango\n");
                    break;
                }
            }
    } while (!verif);

    Rid = auxi;
    ptr = NULL;

    /* Receiver's account ID */

    strcpy(dat,"");
    create = -1;

    do{
        printf("Numero de cuenta del receptor\n");
        scanf("%s",&dat);
        auxi = strtol(dat, &ptr, 10);

        strcpy(dat,"");
        printf("Codigo de banco\n");
        scanf("%s",&dat);
        auxi2 = strtol(dat, &ptr, 10);
        verify = searchbyCID(verif,auxi,auxi2);

            if (!verify){
                printf("ERROR: Numero cuenta ingresado asociado a este numero de cedula no existe en el sistema\n");

                /* Would you like to link a new account to the system */

                printf("Desea crear una nueva cuenta?\n");
                printf("1. Si\n");
                printf("2. No\n");
                printf("0. Intentar de nuevo\n\n");
                scanf("%d", &create);

                switch (create)
                {
                case 1:
                    addAccount(&t);
                    printf("\n**************Cuenta agregada con exito****************\n\n");
                    break;

                case 2:
                    return;
                    break;

                case 0: break;
                
                default:
                    printf("Opcion fuera de rango\n");
                    break;
                }
            }
        } while (!verify);

    Rcb = auxi2; Rad = auxi;
    ptr = NULL;
    create = -1;

    strcpy(dat,"");

    /* Description */

    do{
        printf("Descripcion de la operacion\n");
        scanf("%s",&dat);
            if (strlen(dat)>40){
                printf("ERROR: Descripcion de la transaccion no puede sobrepasar los 40 caracteres\n");
            }
    } while (strlen(dat)>40);

    create = -1;
    
    /* Date */

    strcpy(sttime,ctime(&currentTime));
    Tc = getTCode(t);

    /* Show data and confirm */
    printf("********** DATOS DE LA TRANSACCION **************\n");
    printf("Por favor compruebe sus datos antes de continuar\n");

    printf("Cedula del emisor %d\n", Iid);
    printf("Numero de cuenta del emisor %d\n", Iad);
    printf("Cedula del receptor %d\n", Rid);
    printf("Numero de cuenta del receptor %d\n", Rad);
    printf("Monto %lf\n", Ta);
    printf("Descripcion %s\n", dat);
    printf("Fecha %s\n", sttime);
    printf("Codigo de la transaccion %d\n\n",Tc);

    printf("Son los datos correctos?\n");
    printf("1. Si\n");
    printf("2. No\n");
    printf("0. Cancelar transaccion\n");
    scanf("%d",&create);


    switch (create)
    {
    case 1:
        op->secondPartysAN = Rad;
        op->secondPartysId = Rid;
        op->secondPartysCB = Rcb;
        op->type = 1; //Payment
        strcpy(op->description,dat);
        strcpy(op->date,sttime);
        op->code = Tc;
        op->amount = Ta;

        processPayment(&t,op,Iad,Icb);
        
        /* Receiver */

        op2->secondPartysAN = Iad;
        op2->secondPartysId = Iid;
        op2->secondPartysCB = Icb;
        op2->type = 2; //Get paid
        strcpy(op2->description,dat);
        strcpy(op2->date,sttime);
        op2->code = Tc+1;
        op2->amount = Ta;

        processPayment(&t,op2,Rad,Rcb);
        break;

    case 2: break;

    case 3: break;
    
    default:
        break;
    }
} 

transaction * isCodeValid (account *p, int n){
    transaction *t = NULL;
        if (p->tnext){
            t = p->tnext;
        }

    if (!t){
        return NULL;
    }

    else while (t){
        if (t->code == n) return t;
        t=t->next;
    }
    return NULL;
}

void showAllMovements (account *p){
    transaction *t = NULL;
    if (p->tnext){
        t = p->tnext;
    }

    printf("\n************ MOVIMIENTOS ***************\n\n");
    if (!t){
        printf("No hay movimientos en esta cuenta\n");
        return;
    }

    else while (t){
        printf("--------------------------------------------------------------------\n");
        printf("Codigo de transaccion: %d\n",t->code);
        printf("Monto: %lf\n",t->amount);
        if (t->type == 1)
            printf("Tipo de transaccion: Pago\n");
        else
            printf("Tipo de transaccion: Cobro\n");
        printf("Fecha: %s\n",t->date);
        printf("Numero de cedula del receptor: %d\n",t->secondPartysId);
        printf("Numero de cuenta del receptor: %d\n",t->secondPartysAN);
        printf("Descripcion: %s\n",t->description);
        printf("--------------------------------------------------------------------\n");
        t=t->next;
    }
}

void deleteTransaction (transaction ** p, int n){
    transaction **ppn = p;           /* pointer to pointer to node*/
    transaction *pn = *p;            /* pointer to node */

    for (; pn; ppn = &pn->next, pn = pn->next) {
        if (pn->code == n) {
            *ppn = pn->next;    /* set address to next */
            delete(pn);
            break;
        }
    }

}

void updateBalance (client ** p, int id, int aid, int codbank, int type, double s){
    client *t = *p;
    account *h = NULL;

    while (t){
        if (t->id == id)
            break;
    t=t->next;
    }

    if (t->anext) h=t->anext;

    while (h){
        if (h->id == aid && h->bank == codbank){
            if (type == 1) h->balance+=s;
            else h->balance-=s;
        }
        h=h->next;
    }
}

void deleteTransaction(client **p){
    char dat[1000]; char *ptr = NULL;
    client *verif = NULL, *t = *p;
    account *verify = NULL;
    transaction *target = NULL;
    int auxi = 0, auxi2 = 0, Rid = 0, Raid = 0, Rcb = 0, Iid = 0, Iaid = 0, Icb = 0, auxcod = 0;

    strcpy(dat,"");
    printf("\n************ ELIMINAR TRANSACCION ***************\n\n");

    do
    {
        printf("Numero de cedula asociado\n");
        scanf("%s",&dat);
        auxi = strtol(dat, &ptr, 10);
            if (auxi == 0 || strlen(ptr)>1){
                printf("ERROR: Numero de cedula de el cliente debe ser un numero entero positivo mayor a cero \n");
                }
            verif = clientExists(t,auxi);
            if (!verif){
                printf("ERROR: Numero de cedula ingresado no existe en el sistema\n");
            }
    } while (auxi == 0 || strlen(ptr)>1 || !verif);
    
    strcpy(dat,"");
    fflush(stdin);

    /* Account data */

    do
    {
        printf("Numero de cuenta\n");
        scanf("%s",&dat);
        auxi = strtol(dat, &ptr, 10);
            if (auxi == 0 || strlen(ptr)>1){
                printf("ERROR: Numero de cuenta de el cliente debe ser un numero entero positivo mayor a cero \n");
                }

    strcpy(dat,"");
    //Bank code

        printf("Codigo de banco\n");
        scanf("%s",&dat);
        auxi2 = strtol(dat, &ptr, 10);
            if (auxi2 == 0 || strlen(ptr)>1){
                printf("ERROR: Codigo de banco debe ser un numero entero positivo mayor a cero \n");
            }
            verify = searchbyCID(verif,auxi,auxi2);

            if (!verify){
                printf("ERROR: Numero de cuenta asociado a esta cedula no existe en el sistema\n");
            }
    } while (auxi == 0 || strlen(ptr)>1 || !verify);
    strcpy(dat,"");
    ptr = NULL;

    /* Transaction code */

    do
    {
        printf("A continuacion se mostraran todas las transacciones realizadas por esta cuenta, escriba el codigo de la transaccion que desea eliminar\n");
        showAllMovements(verify);
        scanf("%d",&auxi);
        target = isCodeValid(verify,auxi);
            if (!target){
                printf("ERROR: Codigo de transaccion no es valido\n");
            }
    } while (!target);
    
    /* Update accounts */

    Iid = verif->id;
    Iaid = verify->id;
    Icb = verify->bank;
    Rid = target->secondPartysId;
    Raid = target->secondPartysAN;
    Rcb = target->secondPartysCB;
    auxcod = target->code;
    
    if (target->type == 1){
        updateBalance(&t,verif->id,verify->id,verify->bank,target->type,target->amount);
        deleteTransaction(&verify->tnext,target->code);
        verif = clientExists(t,Rid);
        verify = searchbyCID(verif,Raid,Rcb);
        transaction * target2 = NULL;
        target2 = isCodeValid(verify,auxcod+1);
        updateBalance(&t,verif->id,verify->id,verify->bank,target->type,target->amount);
        if (target2)
            deleteTransaction(&verify->tnext,target2->code);
        return;
    }

    else {
        updateBalance(&t,verif->id,verify->id,verify->bank,target->type,target->amount);
        deleteTransaction(&verify->tnext,target->code);
        verif = clientExists(t,Rid);
        verify = searchbyCID(verif,Raid,Rcb);
        transaction * target2 = NULL;
        target2 = isCodeValid(verify,target->code-1); 
        updateBalance(&t,verif->id,verify->id,verify->bank,target->type,target->amount);
        if (target2)
            deleteTransaction(&verify->tnext,target2->code);
        return;
    }
}

void transactionOptions(client **p){
    client *t = *p;
    int op=-1;
        if (op){
            printf("    *** Transacciones ****\n");
            printf("    \t 1. Realizar pago\n");
            printf("    \t 2. Eliminar transaccion\n");
            printf("    \t 0. Regresar\n");
            scanf("%d",&op);

            switch (op)
            {
            case 1:
                makePayment(&t);
                break;

            case 2:
                deleteTransaction(&t);
                printf("Transaccion eliminada con exito\n");
                break;

            case 0: return;
                break;
            default:
                printf("Opcion fuera de rango\n");
                break;
            }
        }

}

boolean nameFits (char * name, char * name2){
    for (int i = 0; i<=strlen(name); i++){
        if (name[i]!=name2[i]) return FALSE;
    }
    return TRUE;
}

void dataName(client *p, char * name){
    int totalAccounts = 0;
    double totalBalance = 0;
    boolean canShow = FALSE;

    if (p){
        printf("********** DATOS DE CLIENTE **************\n");
        while (p){
            totalAccounts=0;
            totalBalance=0;
            canShow = nameFits(name,p->name);
                if (canShow==TRUE){
                    printf("Cedula: %d\n",p->id);
                    printf("Nombre: %s\n",p->name);
                    printf("Direccion: %s\n",p->city);
                    printf("Telefono: %s\n",p->phone);
                
                if (p->anext){
                    printf("\n\n********** CUENTAS BANCARIAS **************\n\n");

                        while(p->anext){
                            totalAccounts++;
                            totalBalance+=p->anext->balance;
                            printf("-------------------------------------------\n");
                            printf("Numero de cuenta: %d\n",p->anext->id);
                            printf("Codigo de banco: %d\n",p->anext->bank);
                            
                                if (p->anext->type == 1){
                                    printf("Tipo de cuenta: Corriente\n");
                                }
                                else printf("Tipo de cuenta: Ahorro\n");
                            printf("Saldo: %lf\n",p->anext->balance);
                            printf("-------------------------------------------\n");
                            p->anext=p->anext->next;
                        }

                    printf("\nTotal de cuentas bancarias asociadas: %d\n",totalAccounts);
                    printf("Saldo total: %lf\n", totalBalance);
                }

                else if (!p->anext){
                    printf("No hay cuentas bancarias asociadas a %s\n", p->name);
                }
            }        
            p=p->next;
        }
    }

    else if (!p){
        printf("No existe ningun cliente con el nombre %s\n",name);
    }
}

transaction * findCodePos (client *p, int n){
    account * a = NULL;
    transaction *t = NULL;
        if (p->anext){
            a = p->anext;
                while (a){
                    if (a->tnext){
                        t = a->tnext;
                        while (t){
                            if (t->code == n) 
                                return t;
                            t=t->next;
                        }
                    }
                    a=a->next;
                }
            }
    return NULL;
}

void swap(double *A, double *B)
{
	double aux = 0;
	aux = *A;
	*A = *B;
	*B = aux;
}

void swap2(int *A, int *B)
{
	int aux = 0;
	aux = *A;
	*A = *B;
	*B = aux;
}

void swap3(long long int *A, long long int *B)
{
	long long int aux = 0;
	aux = *A;
	*A = *B;
	*B = aux;
}

void orderByAmount (double * amount, int * codes, int capacity){
    int min = 0;
	for (int i = 0; i <= capacity; i++)                     //Loop for ascending ordering
	{
        min = i;
		for (int j = 0; j <= capacity; j++)             //Loop for comparing other values
		{
            if (amount[min]>amount[j])
                min = j;
            if (min != i){
                swap(&amount[min],&amount[i]);
                swap2(&codes[min],&codes[i]);
            }
		}
	}
}

void orderByDate (long long int * dates, int * codes, int capacity){
    int min = 0;
	for (int i = 0; i <= capacity; i++)                     //Loop for ascending ordering
	{
        min = i;
		for (int j = 0; j <= capacity; j++)             //Loop for comparing other values
		{
            if (dates[min]>dates[j])
                min = j;
            if (min != i){
                swap3(&dates[min],&dates[i]);
                swap2(&codes[min],&codes[i]);
            }
		}
	}
}

void Rtransactions (int *codes, int capacity, client *p, client * fullList){
    int i = 0;
    transaction * aux = NULL;
    client * aux2 = NULL;
    double total = 0;

    if (codes){
        printf("********** DATOS DE TRANSACCIONES **************\n");
        for (i=0; i<=capacity; i++){
            aux = findCodePos(p,codes[i]);
                if (aux){
                    printf("-------------------------------------------\n");
                    printf("Monto: %lf\n",aux->amount);
                    printf("Codigo de transaccion: %d\n",aux->code);
                    printf("Fecha: %s\n",aux->date);
                    printf("Descripcion: %s\n",aux->description);
                    printf("Cedula del receptor: %d\n",aux->secondPartysId);
                    aux2 = clientExists(fullList,aux->secondPartysId);
                    printf("Nombre del receptor: %s\n",aux2->name);
                    printf("Numero de cuenta del receptor: %d\n",aux->secondPartysAN);
                    printf("-------------------------------------------\n");
                    total+=aux->amount;
                }
            }
            printf("Total: %lf\n",total);
        }
}

int identificarmes(char linea[]) {
	/*Month to number*/
	if ((linea[0] == 'J') && (linea[1] == 'a')) /*Enero*/
		return 1;
	else if (linea[0] == 'F') /*Febrero*/
		return 2;
	else if ((linea[0] == 'M') && (linea[1] == 'a') && (linea[2] == 'r')) /*Marzo*/
		return 3;
	else if ((linea[0] == 'A') && (linea[1] == 'p')) /*Abril*/
		return 4;
	else if ((linea[0] == 'M') && (linea[1] == 'a') && (linea[2] == 'y')) /*Mayo*/
		return 5;
	else if ((linea[0] == 'J') && (linea[1] == 'u') && (linea[2] == 'n')) /*Junio*/
		return 6;
	else if ((linea[0] == 'J') && (linea[1] == 'u') && (linea[2] == 'l')) /*Julio*/
		return 7;
	else if ((linea[0] == 'A') && (linea[1] == 'u')) /*Agosto*/
		return 8;
	else if (linea[0] == 'S') /*Septiembre*/
		return 9;
	else if (linea[0] == 'O') /*Octubre*/
		return 10;
	else if (linea[0] == 'N') /*Noviembre*/
		return 11;
	else if (linea[0] == 'D') /*Diciembre*/
		return 12;

	else return 0;
}

long long int conversion(char * date) {
	int i = 0;
	long long int tot = 0;
	int a, mes, dia, hora;
	long int min, seg;
	char y[6], mo[5], d[3], h[3], m[3], s[3];
    strcpy(y,"");
    strcpy(mo,"");
    strcpy(d,"");
    strcpy(h,"");
    strcpy(m,"");
    strcpy(s,"");

	strncpy(y, &(date[20]), 5);
	a = atoi(y);

	/*Years to hours*/
	tot = a * 8760;
	strncpy(mo, &(date[4]), 3);
    mo[3]='\0';


    /*Months to hours*/
	mes = identificarmes(mo);
    mes = mes*730;
	tot = tot + mes;

	if (date[9] == ' '){
		strncpy(d, &(date[9]), 1);
        d[1]='\0';
    }
	else{
		strncpy(d, &(date[8]), 2);
        d[2]='\0';
    }
	dia = atoi(d);

	/*Days to hours*/
    dia= dia *24;
	tot = tot;
	strncpy(h, &(date[11]), 2);
    h[2]='\0';
	hora = atoi(h);
	tot = tot + hora;
	strncpy(m, &(date[14]), 2);
    m[2]='\0';
	min = atol(m);
	min = min / 60;
	tot = tot + min;
	strncpy(s, &(date[17]), 2);
    s[2]='\0';
	seg = atol(s);
	seg = seg / 3600;
	tot = tot + seg;
	return tot;
}

void getTR (client *t, client * fullList, int capacity, double * amount, long long int *dates, int * codes, int mode, int whatToOrder){
    client * aux = NULL;
    account * a = NULL;
    transaction * q = NULL;
    codes = (int*)malloc(sizeof(int)*capacity);
    amount = (double*)malloc(sizeof(double)*capacity);
    dates = (long long int*)malloc(sizeof(long long int)*capacity);
    int i = 0;

    if (mode == 1){
        /*Mode 1: Order by amount*/
        if (t->anext){
            a = t->anext;
            while (a){
                if (a->tnext){
                    q = a->tnext;
                    while (q){
                        if (q->type == 2 && whatToOrder == 1){
                            codes[i]=q->code;
                            amount[i]=q->amount;
                            i++;
                            if (i == capacity){
                                capacity*=2;
                                /* Expand vector capacity */
                                codes = (int*)realloc(codes,sizeof(int)*capacity);
                                amount = (double*)realloc(amount,sizeof(double)*capacity);
                            }

                        } /* 1: Order transactions as receiver */

                        if (q->type == 1 && whatToOrder == 2){
                            codes[i]=q->code;
                            amount[i]=q->amount;
                            i++;
                            if (i == capacity){
                                capacity*=2;
                                /* Expand vector capacity */
                                codes = (int*)realloc(codes,sizeof(int)*capacity);
                                amount = (double*)realloc(amount,sizeof(double)*capacity);
                            }
                        } /* 2: Order transactions as giver */
                        q=q->next;
                    }
                }
                a=a->next;
            }
        }
        orderByAmount(amount, codes, i-1);
        Rtransactions(codes,i-1,t, fullList);
    } /*Order by amount*/

    else if (mode == 2){
        /*Mode 2: Order by date*/
        if (t->anext){
            a = t->anext;
                while(a){
                    if (a->tnext){
                        q = a->tnext;
                            while(q){
                                if (q->type == 2 && whatToOrder == 1){
                                    codes[i]=q->code;
                                    /* Convert string date to integer time_t */
                                    dates[i]=conversion(q->date);
                                    i++;
                                        if (i == capacity){
                                            capacity*=2;
                                            /* Expand vector capacity */
                                            codes = (int*)realloc(codes,sizeof(int)*capacity);
                                            dates = (long long int*)realloc(dates,sizeof(long long int)*capacity);
                                        }
                                    }

                                if (q->type == 1 && whatToOrder == 2){
                                    codes[i]=q->code;
                                    /* Convert string date to integer time_t */
                                    dates[i]=conversion(q->date);
                                    i++;
                                        if (i == capacity){
                                            capacity*=2;
                                            /* Expand vector capacity */
                                            codes = (int*)realloc(codes,sizeof(int)*capacity);
                                            dates = (long long int*)realloc(dates,sizeof(long long int)*capacity);
                                        }
                                }
                                q=q->next;
                            }
                    }
                    a=a->next;
                }
        }
    orderByDate(dates, codes, i-1);
    Rtransactions(codes,i-1,t, fullList);
    } /*Order by date*/
}



void checkTransactionsMenu(client *p){
    int op=-1, auxi = 0, capacity = 1000, op2=-1;
    int * codes = NULL;
    long long int * dates = NULL;
    double * amounts = NULL;
    char dat [1000]; char *ptr = NULL;
    client * verif = NULL;
    strcpy(dat,"");

        if (op){
            printf("    *** Consultas varias ****\n");
            printf("    \t 1. Mostrar informacion por nombre\n");
            printf("    \t 2. Mostrar transacciones de cobro\n");
            printf("    \t 3. Mostrar transacciones de pago\n");
            printf("    \t 4. Mostrar todas las transacciones\n");
            printf("    \t 5. Mostrar transacciones por rango de valores\n");
            printf("    \t 0. Regresar\n");
            scanf("%d", &op);
            fflush(stdin);

            switch (op)
            {
            case 1:
                printf("Ingrese nombre de cliente\n");
                gets(dat);
                dataName(p,dat);
                break;

            case 2: 
                do
                {
                    printf("Numero de cedula de cliente\n");
                    scanf("%s",&dat);
                    auxi = strtol(dat, &ptr, 10);
                        if (auxi == 0 || strlen(ptr)>1){
                            printf("ERROR: Numero de cedula de el cliente debe ser un numero entero positivo mayor a cero \n");
                            }
                        verif = clientExists(p,auxi);
                        if (!verif){
                            printf("ERROR: Numero de cedula ingresado no existe en el sistema\n");
                        }
                } while (auxi == 0 || strlen(ptr)>1 || !verif);

                ptr = NULL;
                do
                {
                    printf("\nComo le gustaria que se ordenaran los datos?\n");
                    printf("1. Por monto\n");
                    printf("2. Por fecha\n");
                    printf("0. Regresar\n");
                    scanf("%s",&dat);
                    op2 = strtol(dat,&ptr,10);

                        if(op2 != 1 && op2 != 2 && op2 != 0){
                            printf("Opcion fuera de rango\n");
                        }
                } while (op2 != 1 && op2 != 2 && op2 != 0);
                
                switch (op2)
                {
                case 1:
                    getTR(verif,p,capacity,amounts,dates,codes,1,1);
                    break;

                case 2: 
                    getTR(verif,p,capacity,amounts,dates,codes,2,1);
                    break;
                }
                break;
            case 3:                 
                do
                {
                    printf("Numero de cedula de cliente\n");
                    scanf("%s",&dat);
                    auxi = strtol(dat, &ptr, 10);
                        if (auxi == 0 || strlen(ptr)>1){
                            printf("ERROR: Numero de cedula de el cliente debe ser un numero entero positivo mayor a cero \n");
                            }
                        verif = clientExists(p,auxi);
                        if (!verif){
                            printf("ERROR: Numero de cedula ingresado no existe en el sistema\n");
                        }
                } while (auxi == 0 || strlen(ptr)>1 || !verif);

                ptr = NULL;
                do
                {
                    printf("\nComo le gustaria que se ordenaran los datos?\n");
                    printf("1. Por monto\n");
                    printf("2. Por fecha\n");
                    printf("0. Regresar\n");
                    scanf("%s",&dat);
                    op2 = strtol(dat,&ptr,10);

                        if(op2 != 1 && op2 != 2 && op2 != 0){
                            printf("Opcion fuera de rango\n");
                        }
                } while (op2 != 1 && op2 != 2 && op2 != 0);
                
                switch (op2)
                {
                case 1:
                    getTR(verif,p,capacity,amounts,dates,codes,1,2);
                    break;

                case 2: 
                    getTR(verif,p,capacity,amounts,dates,codes,2,2);
                    break;
                }
                break;
            break;
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

void showMenu(){
    client *c = NULL;
    int op=-1;
        while (op){
            printf("\n*** Sistema de pagos y cobros P2Bank ***\n\n");
            printf("    \t 1. Cuentas y clientes\n");
            printf("    \t 2. Transacciones\n");
            printf("    \t 3. Consultas varias\n");
            printf("    \t 4. Cargar datos desde archivo\n");
            printf("    \t 5. Mostrar todos los datos\n");
            //Option 5 will be used to make the output file because the program has to access the whole nested list anyway
            printf("    \t 0. Salir\n");
            scanf("%d",&op);

            switch (op)
            {
            case 1:
                linkAccountMenu(&c);
                system("pause");
                system("cls");
                break;

            case 2:
                transactionOptions(&c);
                system("pause");
                system("cls");
                break;
            
            case 3:
                checkTransactionsMenu(c);
                system("pause");
                system("cls");
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