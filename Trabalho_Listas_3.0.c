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
    struct lplaylists_no *prox;
} *Lplaylists_no;


//Funcoes -------------------------------------------------------------------------------------------------------------
void menu() {
    printf("\t***MENU***\n");
    printf("Informe uma opcao:\n");
    printf("\t1 - Inserir musica\n\t2 - Listar musicas cadastradas\n\t3 - Criar playlist\n"
           "\t4 - Listar playlists\n");
}
    //*Lista geral*
Musica_no *cria_lista_geral() { //Cria uma cabeca de lista geral
    Musica_no *inicio = malloc(sizeof(Musica_no));
    inicio->prox = NULL;
    return inicio;
}

void insere_musica_na_lista_geral(Lista_musicas lista) {//Insere a musica criada na lista geral duplamente encadeada
    Musica_no *novo_no = malloc(sizeof(Musica_no));
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

void imprime_lista_de_musicas_geral(Musica_no *no_cabeca) {
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

Musica *busca_musica(Lista_musicas lista, int id_procurado) {
    Musica_no *procurado = lista->prox;
    while (procurado && procurado->musica->id != id_procurado){
        procurado = procurado->prox;
    }
    return procurado->musica;
}
    //

    //*Playlists*
Lplaylists_no cria_cabeca_lista_de_playlist() { //Cria uma cabeca de lista de playlists
    Lplaylists_no inicio = (Lplaylists_no) malloc(sizeof(Lplaylists_no));
    inicio->prox = NULL;
    return inicio;
}

Playlist_no *cria_cabeca_playlist (){ //Cria uma cabeca de playlist
    Playlist_no *inicio = malloc(sizeof(Playlist_no));
    inicio->prox = inicio;
    return inicio;
}

void insere_na_lista_de_playlist (Lplaylists_no lista_de_playlists, Playlist_no *playlist) {
    Lplaylists_no novo_no = (Lplaylists_no)malloc(sizeof(Lplaylists_no));
    novo_no->musicas = malloc(sizeof(Playlist_no));
    system("cls");
    printf("ID da playlist: ");
    scanf("%d", &novo_no->id);
    fflush(stdin);
    printf("Nome da playlist: ");
    gets(novo_no->nome);
    novo_no->musicas = playlist;
    novo_no->prox = lista_de_playlists->prox;
    lista_de_playlists->prox = novo_no;
}

void preenche_playlist(Lplaylists_no lista_de_playlist, Lista_musicas lista_de_musicas) {
    char entrada[100];
    char *id;
    int ids_informados[100];
    int indice = 0;
    int nro_de_ids = 0;
    Playlist_no *nova_playlist = cria_cabeca_playlist(); //Cria playlist

    //Pega os dados do usuario
    fflush(stdin);
    printf("Informe os ID's das musicas que farao parte da playlist:\n");
    gets(entrada);
    id = strtok (entrada, " "); //Extrai o primeiro id

    while (id != NULL) {
        ids_informados[indice++] = atoi(id); //Adiciona o id a lista de ids
        id = strtok(NULL, " ");
        nro_de_ids++;
    }

    //Preenche a playlist

    for(indice = 0; indice < nro_de_ids; indice++) {
        Playlist_no *novo_no_playlist = malloc(sizeof(Playlist_no));
        novo_no_playlist->musica = malloc(sizeof(Musica));
        novo_no_playlist->musica = busca_musica(lista_de_musicas,ids_informados[indice]);
        novo_no_playlist->prox = nova_playlist->prox;
        nova_playlist->prox = novo_no_playlist;
    }

    insere_na_lista_de_playlist(lista_de_playlist, nova_playlist);
}

void imprime_lista_de_playlists(Lplaylists_no no_cabeca) {
    system("cls");
    int indice = 0;
    printf("\t***PLAYLISTS CADASTRADAS***\n");

    if(!no_cabeca->prox) {
        printf("Nenhuma playlist cadastrada!");
    }
    else{
        Lplaylists_no inicial = no_cabeca->prox;

        while(inicial) {
            printf("ID: %d\n", inicial->id);
            printf("Nome da playlist: %s\n", inicial->nome);

            printf("Musicas:\n");
            Playlist_no *playlist = inicial->musicas->prox;
            while(playlist) {
                printf("\tTitulo: %s\n", playlist->musica->titulo);
                printf("----\n");
                playlist = playlist->prox;
            }
            printf("\t***");

            inicial = inicial->prox;
        }
        system("pause");
    }
}

void shuffle(){

}

remove_musica(int id, Lista_musicas musicas, Lplaylists_no playlists){
    Musica *musica;
    int achado = 0;
    while (musicas->prox != NULL && achado == 0){
        if (musicas->musica->id == id){
            musica = musicas->musica;
            achado = 1;
        } else {
            musicas = musicas->prox;
        }
    }

    if (achado == 1){
        Playlist_no *play_no = playlists;
        while (play_no != NULL){
            int excluido;
            Musica_no *no = play_no->musica;
            do {
                excluido = 0;
                if(no->musica->id == id){
                    excluido = 1;
                    no->prox = no->ant;
                } else {
                    no = no->prox;
                }
            } while (no != NULL && excluido == 0);
        }

        free(musica);

    } else {
        printf("Ops! Essa musica nao existe no nosso repositorio...");
    }

}

//Principal -----------------------------------------------------------------------------------------------------------
int main(void) {
    setlocale(LC_ALL, "Portuguese");

    Lista_musicas lista_de_musicas = cria_lista_geral();
    Lplaylists_no lista_playlists = cria_cabeca_lista_de_playlist();


    int opcao;

    do {
        system("cls");
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:{
                insere_musica_na_lista_geral(lista_de_musicas);
                break;
            }
            case 2:{
                imprime_lista_de_musicas_geral(lista_de_musicas);
                break;
            }
            case 3:{
                preenche_playlist(lista_playlists, lista_de_musicas);
                break;
            }
            case 4: {
                imprime_lista_de_playlists(lista_playlists);
                break;
            }
        }

    }
    while (opcao != 5);
}
