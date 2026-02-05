#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo{
    char* titolo;
    char* autore;
    int durata;
    struct nodo *next;
};

int lenght(struct nodo *s){
    int l = 0;
    for(; s != NULL; s = s->next){
        l++;
    }

    return l;
}

void inserisci_testa(struct nodo **s, char* titolo, char* autore, int durata){
    struct nodo *p = (struct nodo *)malloc(sizeof(struct nodo));

    p->titolo = (char*)malloc(strlen(titolo) + 1);
    strcpy(p->titolo, titolo);
    p->autore = (char*)malloc(strlen(autore) + 1);
    strcpy(p->autore, autore);
    p->durata = durata;
    p->next = *s;
    *s = p;
}

void inserisci(struct nodo *s, struct nodo *t){
    if(t != NULL && s != NULL){
        t->next = s->next;
        s->next = t;
    }

}

void rimuovi(struct nodo **s, char* titolo){
    if(*s != NULL){
        struct nodo *q = *s;

        if(strcmp(q->titolo, titolo) == 0){
            *s = (*s)->next;
            free(s);
        } else {
            while(q->next != NULL){
                if(strcmp(q->next->titolo, titolo) == 0){
                    struct nodo *r = q->next;
                    q->next = q->next->next;
                    free(r);
                    return;
                } if(q->next != NULL){
                    q = q->next;
                }
            }
        }
    }
}

void stampa_lista(struct nodo *s){
    struct nodo *current = s;
    while(current != NULL){
        printf("Titolo: %s, Autore: %s, Durata: %d", current->titolo, current->autore, current->durata);
        if(current->next != NULL){
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}


int main(){
    struct nodo *playlist = NULL;

    int n = 0;
    printf("Numero canzoni iniziali: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        char titolo[50];
        printf("Titolo: ");
        scanf("%49s", titolo);
        char autore[50];
        printf("Autore: ");
        scanf("%49s", autore);
        int durata;
        printf("Durata: ");
        scanf("%d", &durata);
        printf("\n");
        inserisci_testa(&playlist, titolo, autore, durata);
    }

    printf("PLAYLIST\n");
    stampa_lista(playlist);
    printf("Lunghezza playlist: %d\n", lenght(playlist));


    int scelta;
    while(scelta != 3){
        printf("\n----- MENU -----");
        printf("\n[1]Inserisci canzone");
        printf("\n[2]Rimuovi canzone");
        printf("\n[3]Esci\n");
        scanf("%d", &scelta);

        switch(scelta){
            case 1: {
                char titolo[50];
                printf("Titolo: ");
                scanf("%49s", titolo);
                char autore[50];
                printf("Autore: ");
                scanf("%49s", autore);
                int durata;
                printf("Durata: ");
                scanf("%d", &durata);
                printf("\n");
                if(playlist != NULL){
                        struct nodo *temp = (struct nodo*)malloc(sizeof(struct nodo));
                        temp->titolo = strdup(titolo);
                        temp->autore = strdup(autore);
                        temp->durata = durata;

                        inserisci(playlist, temp);
                } else {
                    inserisci_testa(&playlist, titolo, autore, durata);
                }
                printf("PLAYLIST\n");
                stampa_lista(playlist);
                printf("Lunghezza playlist: %d\n", lenght(playlist));
                break;
            }
            case 2: {
                char titolo[50];
                printf("Titolo da rimuovere: ");
                scanf("%49s", titolo);
                rimuovi(&playlist, titolo);

                printf("PLAYLIST\n");
                stampa_lista(playlist);
                printf("Lunghezza playlist: %d\n", lenght(playlist));
                break;
            }
            case 3: {
                exit(0);
            }
            default: {
                printf("valore non valido");

            }
        }
    }


    while(playlist != NULL){
        struct nodo *temp = playlist;
        temp = temp->next;
        free(temp->titolo);
        free(temp->autore);
        free(temp);
    }

    return 0;
}
