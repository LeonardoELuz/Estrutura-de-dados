#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include<time.h>

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


//--------------------------------FUN��ES -------------------------------
void menu() {
    printf("\t***MENU***\n");
    printf("Informe uma opcao:\n");
    printf("\t1 - Inserir musica\n\t2 - Listar musicas cadastradas\n\t3 - Criar playlist\n"
           "\t4 - Listar playlists\n\t5 - Listar uma playlist\n\t6 - Embaralha playlist\n\t7 - Remove uma musica\n");
}
    //*Lista geral de m�sicas*
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
        printf("Lista de musicas vazia!\n\n");
        system("pause");
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

    //*****Playlists*****
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
        novo_no_playlist->musica = busca_musica(lista_de_musicas,ids_informados[indice]);
        novo_no_playlist->prox = nova_playlist->prox;
        nova_playlist->prox = novo_no_playlist;
    }

    insere_na_lista_de_playlist(lista_de_playlist, nova_playlist);
}

void imprime_lista_de_playlists(Lplaylists_no no_cabeca) {
    system("cls");
    printf("\t***PLAYLISTS CADASTRADAS***\n");

    if(!no_cabeca->prox) {
        printf("Nenhuma playlist cadastrada!");
    }
    else{
        Lplaylists_no inicial = no_cabeca->prox;

        while(inicial != NULL) {
            printf("ID: %d\n", inicial->id);
            printf("Nome da playlist: %s\n", inicial->nome);

            printf("Musicas:\n");
            Playlist_no *playlist = inicial->musicas->prox;
            while(playlist->musica != NULL) {
                printf("\tTitulo: %s\n", playlist->musica->titulo);
                playlist = playlist->prox;
            }
            printf("\t***\n");
            inicial = inicial->prox;
        }
        system("pause");
    }
}

void imprime_uma_playlist(Lplaylists_no lista_de_playlists) {
    system("cls");
    int id;

    fflush(stdin);
    if(!lista_de_playlists->prox){
        printf("Nenhuma playlist cadastrada!");
    }
    else {
        Lplaylists_no no_da_lista = lista_de_playlists->prox;
        printf("Informe o ID da playlist:\n");
        scanf("%d", &id);

        while(no_da_lista && no_da_lista->id != id){
            no_da_lista = no_da_lista->prox;
        }

        if (no_da_lista) {
            system("cls");
            printf("ID: %d\n", no_da_lista->id);
            printf("Nome da playlist: %s\n", no_da_lista->nome);
            printf("M�sicas:\n");
            Playlist_no *playlist = no_da_lista->musicas->prox;
            while(playlist->musica != NULL) {
                printf("\tT�tulo: %s\n", playlist->musica->titulo);
                playlist = playlist->prox;
            }
        }
        printf("\t***\n");
        system("pause");
    }
}

void shuffle(Lplaylists_no playlists, Lista_musicas lista_musicas){
    //recebe qual o id da playlist a ser embaralhada
    int id;
    int indice = 0;
    int lista_de_ids[50];
   
    fflush(stdin);
    if(!playlists->prox){
        printf("Nenhuma playlist cadastrada!");
    }
    else {

        Lplaylists_no no_da_lista = playlists->prox;
        system("cls");
        printf("Informe o ID da playlist:\n");
        scanf("%d", &id);

        while(no_da_lista != NULL && no_da_lista->id != id){//Procura pelo id na lista de playlists
            no_da_lista = no_da_lista->prox;
        }

        if (no_da_lista != NULL) {// Se o n� existir, mapeia os ids de suas m�sicas e os coloca numa lista
            Playlist_no *playlist = no_da_lista->musicas->prox;
            Playlist_no *playlist_reserva = &playlist; //no reserva para manipula��o futura
            while(playlist->musica != NULL) {
                lista_de_ids[indice++] = playlist->musica->id;
                playlist = playlist->prox;
            }

            //****Substitui as m�sicas****

            while (playlist_reserva->musica != NULL) {//Para cada n� da playlist...

                int id_aleatorio;
                int indice_aleatorio = rand() % indice; //um dos �ndices � escolhido de forma aleat�ria
                id_aleatorio = lista_de_ids[indice_aleatorio]; //Um elemento aleat�rio � escolhido da lista de ids
                Musica *musica;
                Musica_no *musicas = lista_musicas->prox;

                while(musicas != NULL && (musicas->musica->id != id_aleatorio)) {//O elemento � procurado na lista geral de m�sicas cadastradas
                    musicas = musicas->prox;
                }
                playlist_reserva->musica = musicas->musica; // A nova m�sica � atribuida ao n� da playlist
                

                //remove o id j� selecionado da lista
                for(int i = indice_aleatorio; i < indice; i++) {
                     lista_de_ids[i] = lista_de_ids[i + 1];
                }
                indice--;

                playlist_reserva = playlist_reserva->prox;
            }

        printf("Playlist embaralhada!\n");
        system("pause");
        }
    }
}

void remove_musica(Lista_musicas musicas, Lplaylists_no playlists) {
    int musica_id;
    Lplaylists_no lista_de_playlists = playlists->prox;

    system("cls");
    printf("Informe o ID da m�sica a ser apagada:\n");
    scanf("%d", &musica_id);

    while(lista_de_playlists != NULL) {
        Playlist_no *no_atual, *proximo_no;
        no_atual = lista_de_playlists->musicas;
        proximo_no = no_atual->prox;

        while(proximo_no->musica != NULL && proximo_no->musica->id != musica_id) {
            no_atual = proximo_no;
            proximo_no = proximo_no->prox;
        }
        if(proximo_no->musica != NULL) {
            no_atual->prox = proximo_no->prox;
            free(proximo_no);
        }

        lista_de_playlists = lista_de_playlists->prox;
    }

    //remove da lista de m�sicas
    Musica_no *atual, *proximo;
    atual = musicas;
    proximo = atual->prox;

    while(proximo != NULL && proximo->musica->id != musica_id) {
        atual = proximo;
        proximo = proximo->prox;
    }
    if(proximo != NULL) {
        atual->prox = proximo->prox;
        free(proximo->musica);
        free(proximo);
        printf("M�sica removida!\n");
        system("pause");
    }
    else {
        printf("M�sica n�o cadastrada!");
        system("pause");
    }
}

//--------------------------------PRINCIPAL --------------------------------------
int main(void) {
    setlocale(LC_ALL, "Portuguese");
    srand(time(0));

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
            case 5: {
                imprime_uma_playlist(lista_playlists);
                break;
            }
            case 6: {
                shuffle(lista_playlists, lista_de_musicas);
                break;
            }
            case 7: {
                remove_musica(lista_de_musicas, lista_playlists);
                break;
            }
        }

    }
    while (opcao != 8);
}
