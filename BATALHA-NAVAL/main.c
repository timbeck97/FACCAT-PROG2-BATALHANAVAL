#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int tabuleiro[20][20];

void preencheMatrizInicial();
void imprimeMatriz();
void imprimeMatrizAlvosAcertados();
void digitaPosicao(int posicao[]);
void colocaNavio(int posicao[], int valor);
int procuraNavio(int posicao[],int *pontos, int *navio1, int *navio2, int *navio3);
void navioDestruido();
int main()
{   int posicao[2];
    int pontos=0;
    int navio1=0, navio2=0, navio3=0;
    preencheMatrizInicial();


    for(int i=1;i<=3;i++){

        system("clear");
        imprimeMatriz();
        colocaNavio(posicao, i);
    }
    system("clear");
    int result=10;

    while(1){

        system("clear");
        imprimeMatriz();
        printf("Quantidade de pontos: %d\n",pontos);
        navioDestruido(navio1,navio2,navio3);
        if(result==1)printf("Acertou o navio!\n");
        else if(result==0)printf("Errou o navio!\n");
        result = procuraNavio(posicao, &pontos, &navio1, &navio2, &navio3);


    }



    return 0;
}
void navioDestruido(int navio1, int navio2, int navio3){
    int quantidade=0;
    if(navio1==5)quantidade++;
    if(navio2==5)quantidade++;
    if(navio3==5)quantidade++;
    printf("Navios destruidos: %d\n",quantidade);
}
void preencheMatrizInicial(){
    for(int i=0;i<20;i++){
        for(int j=0;j<20;j++){
            tabuleiro[i][j]=0;
        }
    }
}
void imprimeMatriz(){
    //codigo abaixo para imprimi
    printf("    ");
    for(int a=1;a<=9;a++) printf("%d ",a);
    for(int a=0;a<=9;a++) printf("%d ",a);
    printf("0");


    printf("\n");
    for(int i=0;i<20;i++){
        printf("%c - ",i+65);
        for(int j=0;j<20;j++){

            printf("");
            if(tabuleiro[i][j]==1 || tabuleiro[i][j]==2 || tabuleiro[i][j]==3)printf("x-");
            else{printf("0-");}
            //printf("%d-",tabuleiro[i][j]);
        }

    printf("\n");
    }
}
void imprimeMatrizAlvosAcertados(){

    //codigo abaixo para imprimi
    printf("    ");
    for(int a=1;a<=9;a++) printf("%d ",a);
    for(int a=0;a<=9;a++) printf("%d ",a);
    printf("0");


    printf("\n");
    for(int i=0;i<20;i++){
        printf("%c - ",i+65);
        for(int j=0;j<20;j++){

            printf("");
            if(tabuleiro[i][j]==0 || tabuleiro[i][j]==1 || tabuleiro[i][j]==2 || tabuleiro[i][j]==3)printf(" -"); //se estiver vazio ou tiver navio imprime espaço
            else if(tabuleiro[i][j]==8) printf("1-"); //se tiver 8 quer dizer que essa posicao tem navio e foi acertada pelo jogador ai imprime 1
            else if(tabuleiro[i][j]==9) printf("0-"); //se tiver 9 quer dizer que o jogador atirou e errou ai imprime 0
        }

    printf("\n");
    }
}

void digitaPosicao(int posicao[]){
    char linha;
    printf("Linha: ");
    scanf("%c",&linha);
    linha=toupper(linha);
    __fpurge(stdin);
    while(!(linha>=65 && linha<=84)){
        printf("Digite uma letra correta: ");
        scanf("%c",&linha);
        __fpurge(stdin);
        linha=toupper(linha);
    }
    printf("Coluna: ");
    scanf("%d",&posicao[1]);
    __fpurge(stdin);
    while(!(posicao[1]>=1 && posicao[1]<=20)){ //verificar essa validacao quando sobrar tempo
        printf("Digite um numero entre 1 e 20: ");
        scanf("%c",&linha);
        __fpurge(stdin);
    }
    posicao[0]=toupper(linha)-64;
    //printf("Linha: %d, Coluna: %d\n",posicao[0],posicao[1]);

}
void colocaNavio(int posicao[], int valor){
    char vh;
    printf("Digite V para vertical ou H para horizontal: ");
    scanf("%c",&vh);
    __fpurge(stdin);
    vh=toupper(vh);
    while(vh!=72 && vh!=86){
        printf("Digite uma letra valida: ");
        scanf("%c",&vh);
        __fpurge(stdin);
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

        if(coluna<15){ //para verificar o lado direito a coluna tem q ser menor ou igual a 15 pra n exceder o tamanho da matriz
            for(int i=coluna;i<coluna+5;i++){ //for para verificar se nao existe naviu ja nas posicoes que deseja colocar (verifica lado direito)
                if(tabuleiro[linha][i]==1 || tabuleiro[linha][i]==2 || tabuleiro[linha][i]==3) validaPosicao=1;
            }
            //---------------------------------------- abaixo é o algoritmo pra verificar o lado esquerdo
        if(validaPosicao==1){ //caso exista ja um naviu em uma das 5 posicoes ele joga flag pra true
            validaPosicao=0;
            if(coluna>5){ //verifica se a coluna é maior igual a 5 pra n exceder a matriz
                for(int i=coluna;i>coluna-5;i--){ //for para verificar se nao existe navio ja nas posicoes que deseja colocar (verifica lado esquerdo)
                if(tabuleiro[linha][i]==1 || tabuleiro[linha][i]==2 || tabuleiro[linha][i]==3) validaPosicao=1;
            }
            if(validaPosicao==1){ //se tiver um navio na posicao esquerda tambem ele printa abaixo
                printf("Escolha uma posicao valida!\n");
            }else{
                for(int i=coluna;i>coluna-5;i--){ //se n tiver navio no lado esquerdo entao ele preenche a matriz com os espaços do navio
                tabuleiro[linha][i]=valor;
                }
            }

            }else{
                printf("Escolha uma posicao valida!\n"); //caso tente colocar um navio na esquerda qnd a coluna for menor ou igual a 5 ele da erro
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
                printf("Escolha uma posicao valida!\n");
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
        if(linha<15){
            for(int i=linha;i<linha+5;i++){ //for para verificar se nao existe navio ja nas posicoes que deseja colocar (verifica pra baixo)
                if(tabuleiro[i][coluna]==1 || tabuleiro[i][coluna]==2 || tabuleiro[i][coluna]==3) validaPosicao=1;
            }
        if(validaPosicao==1){ //se flag==1 quer dizer que ja tem um navio no trajeto
            validaPosicao=0;
            if(linha>5){ //para verificar pra cima tem q ver se a linha é maior que 5 ao menos
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
int procuraNavio(int posicao[],int *pontos, int *navio1, int *navio2, int *navio3){ //retorna 1 se acertar alvo, 2 se o alvo

    digitaPosicao(posicao);
    int linha = posicao[0]-1;
    int coluna = posicao[1]-1;

    if(tabuleiro[linha][coluna]==1){
        tabuleiro[linha][coluna]=8;
        *pontos=*pontos+1;
        *navio1=*navio1+1;
        return 1;
    }
    else if(tabuleiro[linha][coluna]==2){
        tabuleiro[linha][coluna]=8;
        *pontos=*pontos+1;
        *navio2=*navio2+1;
        return 1;
    }
    else if(tabuleiro[linha][coluna]==3){
        tabuleiro[linha][coluna]=8;
        *pontos=*pontos+1;
        *navio3=*navio3+1;
        return 1;
    }
    else if(tabuleiro[linha][coluna]==8){
        printf("Digite uma posicao que nao nao foi digitada antes (pressione enter para continuar)");
        getchar();
        return 3;
    }
    else if(tabuleiro[linha][coluna]==0){
        tabuleiro[linha][coluna] = 9;
    }

    system("clear");
    return 0;
}
