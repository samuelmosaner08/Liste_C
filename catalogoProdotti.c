#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo {
    char *nome;
    float prezzo;
    struct nodo *next;
};

int lenght(struct nodo *n){
    int l = 0;
    for(; n != NULL; n = n->next){
        l++;
    }
    return l;
}

void inserisci_primo(struct nodo **s, char *nome, float prezzo){
    struct nodo *q = (struct nodo *)malloc(sizeof(struct nodo));
    q->nome = (char*)malloc(strlen(nome) + 1);
    strcpy(q->nome, nome);
    q->prezzo = prezzo;
    q->next = *s;
    *s = q;
}

void inserisci_ultimo(struct nodo **s, char* nome, float prezzo){
    struct nodo *q = (struct nodo*)malloc(sizeof(struct nodo));
    q->nome = (char*)malloc(strlen(nome) + 1);
    strcpy(q->nome, nome);
    q->prezzo = prezzo;
    q->next = NULL;

    if(*s != NULL){
        struct nodo *r = *s;
        while(r->next != NULL){
            r = r->next;
        }
        r->next = q;
    } else {
        *s = q;
    }

}

void inserisci_index(struct nodo ** s, char *nome, float prezzo, int index){
    int l = lenght(*s);
    struct nodo *temp = *s;

    if(index == 0){
        inserisci_primo(s, nome, prezzo);
        return;
    }
    if(l > index){
        int i = 0;
        while(i < index - 1){
            temp = temp->next;
            i++;
        }
        struct nodo *nuovo = (struct nodo*)malloc(sizeof(struct nodo));
        nuovo->nome = (char*)malloc(strlen(nome) + 1);
        strcpy(nuovo->nome, nome);
        nuovo->prezzo = prezzo;
        nuovo->next = temp->next;
        temp->next = nuovo;
    }else{
        inserisci_ultimo(s, nome, prezzo);
        return;
    }
}

void rimuovi(struct nodo **s, char*nome, float prezzo){
    if(*s != NULL){
        struct nodo *q = *s;
        if(strcmp(q->nome, nome) == 0 && q->prezzo == prezzo){
            *s = (*s)->next;
            free(s);
        } else {
            while(q->next != NULL){
                if(strcmp(q->next->nome, nome) == 0 && q->next->prezzo == prezzo){
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

void print_lista(struct nodo *s){
    struct nodo *current = s;
    while(current != NULL){
        printf("%s, %f$", current->nome, current->prezzo);
        if(current->next != NULL){
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

int main(){
    struct nodo *lista = NULL;

    int n = 0;
    printf("Numero articoli iniziali: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        char nome[20];
        printf("Nome: ");
        scanf("%s", nome);
        float prezzo;
        printf("Prezzo: ");
        scanf("%f", &prezzo);
        inserisci_primo(&lista, nome, prezzo);
    }

    print_lista(lista);
    printf("Lunghezza lista = %d\n", lenght(lista));

    int scelta = 0;
    while(scelta != 5) {
        printf("\nMENU");
        printf("\n[1]Inserisci in testa");
        printf("\n[2]Inserisci in coda");
        printf("\n[3]Inserisci con indice");
        printf("\n[4]Rimuovi");
        printf("\n[5]Esci\n");

        scanf("%d", &scelta);

        switch(scelta){
            case 1: {
                char nome[20];
                printf("Nome: ");
                scanf("%s", nome);
                float prezzo;
                printf("Prezzo: ");
                scanf("%f", &prezzo);
                inserisci_primo(&lista, nome, prezzo);
                print_lista(lista);
                printf("Lunghezza lista = %d\n", lenght(lista));
                break;
            }

            case 2: {
                char nome[20];
                printf("Nome: ");
                scanf("%s", nome);
                float prezzo;
                printf("Prezzo: ");
                scanf("%f", &prezzo);
                inserisci_ultimo(&lista, nome, prezzo);
                print_lista(lista);
                printf("Lunghezza lista = %d\n", lenght(lista));
                break;
            }
            case 3: {
                char nome[20];
                printf("Nome: ");
                scanf("%s", nome);
                float prezzo;
                printf("Prezzo: ");
                scanf("%f", &prezzo);
                int index;
                printf("Indice: ");
                scanf("%d", &index);
                inserisci_index(&lista, nome, prezzo, index);
                print_lista(lista);
                printf("Lunghezza lista = %d\n", lenght(lista));
                break;

            }
            case 4: {
                char nome[20];
                printf("Articolo da rimuovere: ");
                scanf("%s", nome);
                float prezzo;
                printf("Prezzo: ");
                scanf("%f", &prezzo);
                rimuovi(&lista, nome, prezzo);
                print_lista(lista);
                printf("Lunghezza lista = %d\n", lenght(lista));
                break;
            }

            case 5:
                exit(0);
        }
    }

    // Libera la memoria
    while(lista != NULL) {
        struct nodo *temp = lista;
        lista = lista->next;
        free(temp->nome);
        free(temp);
    }

    return 0;
}
