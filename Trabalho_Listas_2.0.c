#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//Structs -------------------------------------------------------------------------------------------------------------
typedef struct musica {// Tipo de dado musica
    int id;
    char titulo[200];
    char artista[200];
    char album[200];
    int duracao; //segundos
} Musica;

typedef struct musica_no { //No para lista de musicas duplamente encadeada
    Musica *musica;
    struct musica_no *ant;
    struct musica_no *prox;
} Musica_no, *Lista_musicas;

typedef struct playlist_no { //No para playlist do tipo lista circular
    Musica *musica;
    struct playlist_no *prox;
} Playlist_no;

typedef struct lplaylists_no { //No para lista simples de playlist
    int id;
    char nome[200];
    Playlist_no *musicas;
    struct lplaylists_no prox;
} *Lplaylists_no;


//Funcoes -------------------------------------------------------------------------------------------------------------
void menu() {
    printf("\t***MENU***\n");
    printf("Informe uma opcao:\n");
    printf("\t1 - Inserir musica\n\t2 - Listar musicas cadastradas\n\t3 - Criar playlist\n");
}

Musica_no *cria_lista() { //Cria uma cabeca de lista
    Musica_no *inicio = (Musica_no) malloc(sizeof(Musica_no));
    inicio->prox = NULL;
    return inicio;
}

Lplaylists_no *cria_lista_de_playlist() { //Cria uma cabeca de lista de playlists
    Lplaylists_no inicio = (Lplaylists_no) malloc(sizeof(Lplaylists_no));
    inicio->prox = NULL;
    return inicio;
}

void insere_musica_na_lista(Lista_musicas lista) {//Insere a musica criada na lista duplamente encadeada
    Musica_no *novo_no = (Musica_no) malloc(sizeof(Musica_no));
    novo_no->musica = malloc(sizeof(Musica));

    system("cls");
    printf("ID: ");
    scanf("%d", &novo_no->musica->id);
    fflush(stdin);
    printf("Titulo: ");
    gets(novo_no->musica->titulo);
    printf("Artista: ");
    gets(novo_no->musica->artista);
    printf("Album: ");
    gets(novo_no->musica->album);
    printf("Duracao(em segundos): ");
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
        printf("Lista de musicas vazia!\n");
    }
    else {
        Musica_no *inicial = no_cabeca->prox;

        while (inicial) {
        printf("\tID: %d\n", inicial->musica->id);
        printf("\tTitulo:  %s\n", inicial->musica->titulo);
        printf("\tArtista: %s\n", inicial->musica->artista);
        printf("\tAlbum: %s\n", inicial->musica->album);
        printf("\tDuracao: %.2d:%.2d:%.2d\n", (inicial->musica->duracao / 3600), (inicial->musica->duracao % 3600 / 60),
            (inicial->musica->duracao % 3600 % 60));
        printf("\t\t***\n");

        inicial = inicial->prox;
        }
        system("pause");
    }
}

cria_lista(Lplaylists_no *playlist_inicial, Musica_no *musica_inicial){
    //get parametros
    printf("cls");

    char parametros[100];

    //criar a playlist
    id = 0;
    for (len parametros){
        int id;
        se char ' '{
            insere musica(id) na playlist
            id = 0;
        } else{
            id * 10 + (int)parametros[i]
        }
    }

    //inserir no final da lista
    ultimo->prox = *playlist;
}

shuffle(Playlist_no ){ //          --------> OSSO <-------
    listax
    while prox != null{
        insere o id na listax
    }

}

remove_musica(int id){
    Musica_no musica;
    for dentro da lista geral{
        se existe {
            musica = ponteiro;
            for playlists {
                for dentro da playlist{
                    se acha{
                        exclue;
                    }
                }
            }
            tira da lista geral;
            exclue total; (free(ponteiro da musica))
        } else {
            print "ops! i did it again...";
        }
    }
}

//Principal -----------------------------------------------------------------------------------------------------------
int main(void) {
    setlocale(LC_ALL, "Portuguese");

    Lplaylists_no lista_playlists = cria_lista_de_playlist();
    Lista_musicas lista_de_musicas = cria_lista();
    int opcao;

    do {
        system("cls");
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:{
                insere_musica_na_lista(lista_de_musicas);
                break;
            }
            case 2:{
                imprime_lista_de_musicas(lista_de_musicas);
                break;
            }
            case 3:{
                cria_playlist(lista_playlists, lista_de_musicas);
                break;
            }
        }

    }
    while (opcao != 5);
}
