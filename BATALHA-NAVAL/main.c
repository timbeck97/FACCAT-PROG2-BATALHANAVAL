#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int tabuleiro[20][20];

void digitaPosicao2(int posicao[]);

void preencheMatrizInicial();
void imprimeMatriz();
void imprimeMatriz2();
void imprimeMatrizAlvosAcertados();
void digitaPosicao(int posicao[]);
void digitaPosicao2(int posicao[]);
void colocaNavio(int posicao[], int valor);
int procuraNavio(int posicao[],int *pontos, int *navio1, int *navio2, int *navio3, int *tentativas);
void navioDestruido();
int retornaQuemGanhou(int pontos, int tentativas);
void digitaNomeJogadores(char* jogador1, char* jogador2);
void retornaJogador(int rodada, char* jogador1, char* jogador2);
int jogarNovamente();
void limpaBuffer();
void pressioneParaContinuar();
//CONSTANTES ABAIXO UTILIZADAS PARA TESTE DO ALGORITMO (AI O JOGO ENCERRA MAIS RAPIDO) mas o padrao é pontosparaganhar=15  e tentativastotais = 30
#define PONTOSPARAGANHAR 15
#define TENTATIVASTOTAIS 30

int main()
{   int posicao[2];
    int pontos=0, tentativas=0, rodada=0, continuar=1;
    int navio1=0, navio2=0, navio3=0;
    char jogador1[30], jogador2[30];
    preencheMatrizInicial();



    digitaNomeJogadores(jogador1, jogador2);

    while(continuar){
        for(int i=1;i<=3;i++){
            system("clear||cls");
            imprimeMatriz();
            printf("Jogador colocando navio: ");
            retornaJogador(rodada, jogador1, jogador2);
            colocaNavio(posicao, i);
        }
        system("clear||cls");
        imprimeMatriz();
        pressioneParaContinuar();

        int result=10;

        int quemGanhou=0;

        while(!quemGanhou){
            system("clear||cls");
            imprimeMatrizAlvosAcertados();
            printf("Jogador Atirando: ");
            retornaJogador(rodada, jogador2, jogador1);
            printf("Quantidade de pontos: %d --- Quantidade de tiros: %d\n",pontos,tentativas);
            navioDestruido(navio1,navio2,navio3);
            if(result==1)printf("Acertou o navio!\n");
            else if(result==0)printf("Errou o navio!\n");
            result = procuraNavio(posicao, &pontos, &navio1, &navio2, &navio3, &tentativas);
            quemGanhou=retornaQuemGanhou(pontos, tentativas);
            if(quemGanhou==1){
                system("clear||cls");
                imprimeMatrizAlvosAcertados();
                printf("\n--->Jogador vencedor: ");
                retornaJogador(rodada, jogador2, jogador1);
                printf("Quantidade de pontos: %d --- Quantidade de tiros: %d\n",pontos,tentativas);
                navioDestruido(navio1,navio2,navio3);

            }
            if(quemGanhou==2){
                system("clear||cls");
                imprimeMatrizAlvosAcertados();
                printf("\n--->Jogador vencedor: ");
                retornaJogador(rodada, jogador1, jogador2);

                printf("Quantidade de pontos: %d --- Quantidade de tiros: %d\n",pontos,tentativas);
                navioDestruido(navio1,navio2,navio3);


            }
        }

        continuar=jogarNovamente();
        if(continuar){
            preencheMatrizInicial();
            navio1=0, navio2=0, navio3=0, pontos=0, tentativas=0;
            rodada++;
        }

    }




    return 0;
}
void pressioneParaContinuar(){
    char escolha;
    printf("Digite V para continuar: ");
    scanf("%c",&escolha);
    limpaBuffer();
    escolha=toupper(escolha);
    if(escolha!=86){
        while(escolha!=86){
            printf("Digite uma letra válida(V): ");
            scanf("%c",&escolha);
            escolha=toupper(escolha);
            limpaBuffer();
        }
    }
}
int jogarNovamente(){
    char escolha;
    printf("Jogar novamente? (S/N): ");
    scanf("%c",&escolha);
    limpaBuffer();
    escolha=toupper(escolha);
    if(escolha!=83 || escolha!=78){
        while(escolha!=83 && escolha!=78){
            printf("Digite uma letra válida(S/N): ");
            scanf("%c",&escolha);
            escolha=toupper(escolha);
            limpaBuffer();
        }
    }
    if(escolha==83) return 1;
    else return 0;
}
void retornaJogador(int rodada, char* jogador1, char* jogador2){
    if(rodada%2==1) printf("%s\n",jogador1);
    else printf("%s\n",jogador2);
}

int retornaQuemGanhou(int pontos, int tentativas){
    if(pontos ==PONTOSPARAGANHAR) return 1;
    if(tentativas ==TENTATIVASTOTAIS) return 2;
    return 0;
}

void navioDestruido(int navio1, int navio2, int navio3){
    int quantidade=0;
    if(navio1==5)quantidade++;
    if(navio2==5)quantidade++;
    if(navio3==5)quantidade++;
    printf("Navios destruidos: %d\n",quantidade);
}
void digitaNomeJogadores(char* jogador1, char* jogador2){
    printf("Digite o nome do jogador 1: ");
    scanf("%[^\n]",jogador1);
    limpaBuffer();
    printf("Digite o nome do jogador 2: ");
    scanf("%[^\n]",jogador2);
    limpaBuffer();
}
void preencheMatrizInicial(){
    for(int i=0;i<20;i++){
        for(int j=0;j<20;j++){
            tabuleiro[i][j]=0;
        }
    }
}
void imprimeMatriz(){
    //codigo abaixo para imprimi a matriz
    printf("    ");
    for(int a=1;a<=8;a++) printf("%d   ",a);
    printf("9  ");
    for(int a=10;a<=20;a++) printf("%d  ",a);

    printf("\n");
    for(int i=0;i<20;i++){
        printf("%c | ",i+65);
        for(int j=0;j<20;j++){
            if(tabuleiro[i][j]==1 || tabuleiro[i][j]==2 || tabuleiro[i][j]==3 || tabuleiro[i][j]==4 || tabuleiro[i][j]==5 || tabuleiro[i][j]==6)printf("x | ");
            else{printf("  | ");}
            //printf("%d-",tabuleiro[i][j]);
        }
    printf("\n");
    }
}
void imprimeMatriz2(){
    //codigo abaixo para imprimi a matriz
    printf("   ");
    for(int a=1;a<=9;a++) printf("%d ",a);
    for(int a=0;a<=9;a++) printf("%d ",a);
    printf("0");


    printf("\n");
    for(int i=0;i<20;i++){
        printf("%c |",i+65);
        for(int j=0;j<20;j++){


            if(tabuleiro[i][j]==1 || tabuleiro[i][j]==2 || tabuleiro[i][j]==3 || tabuleiro[i][j]==4 || tabuleiro[i][j]==5 || tabuleiro[i][j]==6)printf("x|");
            else{printf(" |");}
            //printf("%d-",tabuleiro[i][j]);
        }

    printf("\n");
    }
}
void imprimeMatrizAlvosAcertados(){

    //codigo abaixo para imprimi a matriz com os alvos que foram acertados ou errados
    printf("    ");
    for(int a=1;a<=8;a++) printf("%d   ",a);
    printf("9  ");
    for(int a=10;a<=20;a++) printf("%d  ",a);

    printf("\n");
    for(int i=0;i<20;i++){
        printf("%c | ",i+65);
        for(int j=0;j<20;j++){
            if(tabuleiro[i][j]==0 || tabuleiro[i][j]==1 || tabuleiro[i][j]==2 || tabuleiro[i][j]==3)printf("  | "); //se estiver vazio ou tiver navio imprime espaço
            else if(tabuleiro[i][j]==8) printf("1 | "); //se tiver 8 quer dizer que essa posicao tem navio e foi acertada pelo jogador ai imprime 1
            else if(tabuleiro[i][j]==9) printf("0 | "); //se tiver 9 quer dizer que o jogador atirou e errou ai imprime 0
        }

    printf("\n");
    }
}
void limpaBuffer(){
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}
//metodo de entrada de dadas em uma linha (ex: a1, b15, d10....)
void digitaPosicao(int posicao[]){
    char dado[3];
    int tamanho;
    printf("Digite a posicao (ex: a5)");
    scanf("%[^\n]",dado);
    limpaBuffer();
    tamanho=strlen(dado);
    dado[0]=toupper(dado[0]);
    while(tamanho!= 2 && tamanho !=3){
        printf("Digite uma posicao correta: ");
        scanf("%[^\n]",dado);
        limpaBuffer();
        tamanho=strlen(dado);
        dado[0]=toupper(dado[0]);
    }
        if(tamanho==2){ //caso tenha digitado coluna menor que 10 cai nesse if
            while((dado[0]<65 || dado[0]>84) || (dado[1]<49 || dado[1] >57)){ // verifica se o primeiro digito é letra e o segundo se é um numero de 1 a 9 (2 digitos, ex: a8)
                printf("Digite uma posicao correta: ");
                scanf("%[^\n]",dado);
                limpaBuffer();
                dado[0]=toupper(dado[0]);
            }
            posicao[0]=dado[0]-64;
            posicao[1]=dado[1]-48;
        }else if(tamanho==3){ //caso a coluna seja maior que 9 (3 digitos, exempo a15)
            while((dado[0]<65 || dado[0]>84)){ //vefica se a letra da coluna digitada é valida
                printf("Digite uma posicao correta: ");
                scanf("%[^\n]",dado);
                limpaBuffer();
                dado[0]=toupper(dado[0]);
            }
            posicao[0]=dado[0]-64; //atribui o numero da linha na posicao 1 do vetor
            while((dado[1]<48 || dado[1]>57) || (dado[2]<48 || dado[2] >57)){ //verifica se os 2 digitos da coluna sao numeros de 0 a 9
                printf("Digite uma posicao correta: ");
                scanf("%[^\n]",dado);
                limpaBuffer();

            }
            //abaixo os valores sao salvos no vetor (a coluna)
            char arr[3];
            arr[0]=dado[1];
            arr[1]=dado[2];
            arr[2]='\0';
            posicao[1]=atoi(arr);
            while(posicao[1]<10 || posicao[1]>20){ //verifica se a coluna esta entre 1 e 20 e se nao estiver pede pra digitar de novo)
                printf("Digite uma posicao correta: ");
                scanf("%[^\n]",dado);
                limpaBuffer();
                arr[0]=dado[1];
                arr[1]=dado[2];
                arr[2]='\0';
                posicao[1]=atoi(arr);
            }
        }
    //printf("linha: %d, coluna: %d\n",posicao[0],posicao[1]);
}
/*
//metodo de entrada de dados em 2 linhas en: linha : a, coluna: 10,  linha:c, coluna 15....)
void digitaPosicao2(int posicao[]){
    char linha;
    printf("Linha: ");
    scanf("%c",&linha);
    linha=toupper(linha);
    limpaBuffer();
    while(!(linha>=65 && linha<=84)){
        printf("Digite uma letra correta: ");
        scanf("%c",&linha);
        limpaBuffer();
        linha=toupper(linha);
    }
    printf("Coluna: ");
    scanf("%d",&posicao[1]);
    limpaBuffer();
    while(posicao[1]<1 || posicao[1]>20){ //verificar essa validacao quando sobrar tempo
        printf("Digite um numero entre 1 e 20: ");
        scanf("%d",&posicao[1]);
        limpaBuffer();
    }
    posicao[0]=toupper(linha)-64;
    //printf("Linha: %d, Coluna: %d\n",posicao[0],posicao[1]);

}
*/
void colocaNavio(int posicao[], int valor){
    char vh;
    printf("Digite V para vertical ou H para horizontal: ");
    scanf("%c",&vh);
    limpaBuffer();
    vh=toupper(vh);
    while(vh!=72 && vh!=86){
        printf("Digite uma letra valida: ");
        scanf("%c",&vh);
        limpaBuffer();
        vh=toupper(vh);
    }

    int linha;
    int coluna;

    int validaPosicao=0;

    do{
    digitaPosicao(posicao);
    linha=posicao[0]-1;
    coluna=posicao[1]-1;

    validaPosicao=0;
    if(vh==72){

        if(coluna<=15){ //para verificar o lado direito a coluna tem q ser menor ou igual a 15 pra n exceder o tamanho da matriz
            for(int i=coluna;i<coluna+5;i++){ //for para verificar se nao existe naviu ja nas posicoes que deseja colocar (verifica lado direito)
                if(tabuleiro[linha][i]==1 || tabuleiro[linha][i]==2 || tabuleiro[linha][i]==3) validaPosicao=1;
            }
            //---------------------------------------- abaixo é o algoritmo pra verificar o lado esquerdo
        if(validaPosicao==1){ //caso exista ja um naviu em uma das 5 posicoes ele joga flag pra true
            validaPosicao=0;
            if(coluna>=4){ //verifica se a coluna é maior igual a 5 pra n exceder a matriz
                for(int i=coluna;i>coluna-5;i--){ //for para verificar se nao existe navio ja nas posicoes que deseja colocar (verifica lado esquerdo)
                if(tabuleiro[linha][i]==1 || tabuleiro[linha][i]==2 || tabuleiro[linha][i]==3) validaPosicao=1;
            }
            if(validaPosicao==1){ //se tiver um navio na posicao esquerda tambem ele printa abaixo
                printf("Escolha uma posicao valida -----aaaaa!\n");
            }else{
                for(int i=coluna;i>coluna-5;i--){ //se n tiver navio no lado esquerdo entao ele preenche a matriz com os espaços do navio
                tabuleiro[linha][i]=valor;
                }
            }

            }else{
                printf("Escolha uma posicao valida! ----bbbbb\n"); //caso tente colocar um navio na esquerda qnd a coluna for menor ou igual a 5 ele da erro
                validaPosicao=1;
            } //----------------------------------- final da parte do lado esquerdo

        }
        else{ // codigo pra preencher o lado direito
             for(int i=coluna;i<coluna+5;i++){ //for pra preencher navio no lado direito se nao tiver nenhum navio ja
                tabuleiro[linha][i]=valor;
                }
            }
        }
        else{ //esse else executa caso a coluna seja <15  (a logica é a mesma de cima mas so vai executar caso a coluna for menor que 15)
            validaPosicao=0;
            for(int i=coluna;i>coluna-5;i--){
                if(tabuleiro[linha][i]==1 || tabuleiro[linha][i]==2 || tabuleiro[linha][i]==3) validaPosicao=1;
            }
            if(validaPosicao==1){
                printf("Escolha uma posicao valida!-----ccccc\n");
            }else{
                for(int i=coluna;i>coluna-5;i--){
                tabuleiro[linha][i]=valor;
                }
            }
        }

    //printf("valor de valida posicao----= %d\n",validaPosicao);
    }
    //abaixo o codigo caso seja vertical---------------------------------------------------
    else{
        validaPosicao=0;
        if(linha<=15){
            for(int i=linha;i<linha+5;i++){ //for para verificar se nao existe navio ja nas posicoes que deseja colocar (verifica pra baixo)
                if(tabuleiro[i][coluna]==1 || tabuleiro[i][coluna]==2 || tabuleiro[i][coluna]==3) validaPosicao=1;
            }
        if(validaPosicao==1){ //se flag==1 quer dizer que ja tem um navio no trajeto
            validaPosicao=0;
            if(linha>=4){ //para verificar pra cima tem q ver se a linha é maior que 5 ao menos
                for(int i=linha;i>linha-5;i--){ //for para verificar se nao existe navio ja nas posicoes que deseja colocar (verifica pra cima)
                if(tabuleiro[i][coluna]==1 || tabuleiro[i][coluna]==2 || tabuleiro[i][coluna]==3) validaPosicao=1;
                }
                if(validaPosicao==1){ //
                    printf("Escolha uma posicao valida!\n"); //se flag==1 entao quer dizer que ja tem um navio pra cima
                }else{
                    for(int i=linha;i>linha-5;i--){ //se nao ele preenche os espaços pra cima
                    tabuleiro[i][coluna]=valor;
                    }
                }

            }
            else{
                printf("Escolha uma posicao valida!\n");
                validaPosicao=1;
            }

        }
        else{
             for(int i=linha;i<linha+5;i++){ //caso o for la de cima nao mudou a flag entao ele executa esse else e preenche os navio pra baixo
                tabuleiro[i][coluna]=valor;
                }
            }
        }
        else{ //else que executa caso a linha for maior que 15
            validaPosicao=0;
            for(int i=linha;i>linha-5;i--){ //for para verificar se nao existe naviu ja nas posicoes que deseja colocar (verifica pra cima)
                if(tabuleiro[i][coluna]==1 || tabuleiro[i][coluna]==2 || tabuleiro[i][coluna]==3) validaPosicao=1;
            }
            if(validaPosicao==1){
                printf("Digite uma posicao que nao tenha nenhum navio\n");
            }else{
                for(int i=linha;i>linha-5;i--){
                tabuleiro[i][coluna]=valor;
                }
            }
        }
        //printf("valor de valida posicao----= %d\n",validaPosicao);
    }
    }while(validaPosicao==1);
    imprimeMatriz();
}
int procuraNavio(int posicao[],int *pontos, int *navio1, int *navio2, int *navio3, int *tentativas){ //retorna 1 se acertar alvo, 2 se o alvo

    digitaPosicao(posicao);
    int linha = posicao[0]-1;
    int coluna = posicao[1]-1;

    if(tabuleiro[linha][coluna]==1){ //se acertar um navio soma pontos, soma um acerto no navio e soma tentativa
        tabuleiro[linha][coluna]=8; // define 8 na posicao digitada para sinalizar q acertou algum navio
        *pontos=*pontos+1;
        *navio1=*navio1+1;
        *tentativas=*tentativas+1;
        return 1;
    }
    else if(tabuleiro[linha][coluna]==2){ //se acertar um navio soma pontos, soma um acerto no navio e soma tentativa
        tabuleiro[linha][coluna]=8; // define 8 na posicao digitada para sinalizar q acertou algum navio
        *pontos=*pontos+1;
        *navio2=*navio2+1;
        *tentativas=*tentativas+1;
        return 1;
    }
    else if(tabuleiro[linha][coluna]==3){ //se acertar um navio soma pontos, soma um acerto no navio e soma tentativa
        tabuleiro[linha][coluna]=8; // define 8 na posicao digitada para sinalizar q acertou algum navio
        *pontos=*pontos+1;
        *navio3=*navio3+1;
        *tentativas=*tentativas+1;
        return 1;
    }
    else if(tabuleiro[linha][coluna]==8 || tabuleiro[linha][coluna]==9){ //se digitar uma posicao que ja foi disparada antes (acertada ou errada)
        printf("Digite uma posicao que nao nao foi digitada antes (pressione enter para continuar)\n");
        getchar();
        return 3;
    }
    else if(tabuleiro[linha][coluna]==0){ //se errar soma 1 na tentativa
        tabuleiro[linha][coluna] = 9; //coloca 9 no tabuleiro pra sinalizar q foi uma posicao que errou
        *tentativas=*tentativas+1;
    }

    system("clear");
    return 0;
}

