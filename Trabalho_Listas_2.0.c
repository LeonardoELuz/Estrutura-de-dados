#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//Structs
typedef struct musica {// Tipo de dado m�sica
    int id;
    char titulo[200];
    char artista[200];
    char album[200];
    int duracao; //segundos
} Musica;

typedef struct musica_no { //N� para lista de m�sicas duplamente encadeada
    Musica *musica;
    struct musica_no *ant;
    struct musica_no *prox;
} Musica_no, *Lista_musicas;

typedef struct playlist_no { //N� para playlist do tipo lista circular
    Musica *musica;
    struct playlist_no *prox;
} Playlist_no;

typedef struct lista_playlists_no { //N� para lista simples de playlist
    int id;
    char nome[200];
    Playlist_no *musicas;
    struct lista_playlists_no *prox;
} Lista_playlists_no;

//Fun��es
void menu() {
    printf("\t***MENU***\n");
    printf("Informe uma op��o:\n");
    printf("\t1 - Inserir m�sica\n\t2 - Listar m�sicas cadastradas\n\t3 - Criar playlist\n");
}

Musica_no *cria_lista() { //Cria uma cabe�a de lista
    Musica_no *inicio = malloc(sizeof(Musica_no));
    inicio->prox = NULL;
    return inicio;
}

void insere_musica_na_lista(Lista_musicas lista) {//Insere a m�sica criada na lista duplamente encadeada
    Musica_no *novo_no = malloc(sizeof(Musica_no));
    novo_no->musica = malloc(sizeof(Musica));

    system("cls");
    printf("ID: ");
    scanf("%d", &novo_no->musica->id);
    fflush(stdin);
    printf("T�tulo: ");
    gets(novo_no->musica->titulo);
    printf("Artista: ");
    gets(novo_no->musica->artista);
    printf("�lbum: ");
    gets(novo_no->musica->album);
    printf("Dura��o(em segundos): ");
    scanf("%d", &novo_no->musica->duracao);

    novo_no->prox = lista->prox;
    novo_no->ant = lista;
    if (lista->prox) {
        lista->prox->ant = novo_no;
    }
    lista->prox = novo_no;
}

void imprime_lista_de_musicas(Musica_no *no_cabeca) {
    system("cls");
    printf("\t***MUSICAS CADASTRADAS***\n");

    if (!no_cabeca->prox) {
        printf("Lista de m�sicas vazia!\n");
    }
    else {
        Musica_no *inicial = no_cabeca->prox;

        while (inicial) {
        printf("\tID: %d\n", inicial->musica->id);
        printf("\tT�tulo:  %s\n", inicial->musica->titulo);
        printf("\tArtista: %s\n", inicial->musica->artista);
        printf("\t�lbum: %s\n", inicial->musica->album);
        printf("\tDura��o: %.2d:%.2d:%.2d\n", (inicial->musica->duracao / 3600), (inicial->musica->duracao % 3600 / 60),
            (inicial->musica->duracao % 3600 % 60));
        printf("\t\t***\n");

        inicial = inicial->prox;
        }
        system("pause");
    }
}
//Principal
int main(void) {
    setlocale(LC_ALL, "Portuguese");

    Lista_musicas lista_de_musicas = cria_lista();
    int opcao;

    do {
        system("cls");
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                insere_musica_na_lista(lista_de_musicas);
                break;
            case 2:
                imprime_lista_de_musicas(lista_de_musicas);
                break;
        }

    }
    while (opcao != 5);
}
