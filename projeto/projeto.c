/*
Projeto PC1
Realizado por:
-Diogo Cravo
-*inserir_nome*
*/
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <conio.h>
#include <windows.h>


#define NLIVROS 50
#define NLEITORES 50
#define NREQUISICOES 50


void menu();
void registar_livro();
void registar_leitor();
void requisitar_livro();
void devolver_livro();
void listagens();
int calculo_data_requisitar(int);
int afixa_time();
void carregar_ficheiro();
void guardar_ficheiro();
void sair();

typedef struct {//Estrutura para os livros
    char ISBN[14]; //Pode armazenar até 13 dígitos incluindo '\0', (tem que ter ser char para poder guardar zeros a esquerda)
    char Titulo[50];
    char Autor[50];
    char Editora[50];
    char Estado[13];//Pode armazenar as palavras, disponível, requisitado ou inutilizado + incluindo '\0'
    int dia_requisitar;
    int mes_requisitar;
    int ano_requisitar;
}livro_t;
livro_t livro[NLIVROS];

typedef struct {//Estrutura para os leitores
    int Codigo_leitor;
    char Nome[50];
    int Dia;
    int Mes;
    int Ano;
    char Localidade[50];
    int Contacto;
    int livrosReq;
}leitor_t;
leitor_t leitor[NLEITORES];


typedef struct {//Estruturas para guardar as requisicoes
    int Codigo_leitor;
    char ISBN[14];
    int Dia;//Dia em que foi requisitado
    int Mes;//Mes em que foi requisitado
    int Ano;//Ano em que foi requisitado
    char Estado_entrega[14];//Estado do livro depois de entregar
}requisicoes_t;
requisicoes_t requisicao[NREQUISICOES];


int nlivro=0;
int nleitor=0;
int requisicoes_ativas=0;
int nrequisicoes=0;


int main(){
    int i;
    for (i = 0; i < NLEITORES; i++) {
        leitor[i].livrosReq = 0;
    }
    carregar_ficheiro();
    menu();

return 0;
}
void menu(){
    int num=0;
    char estado_requisitado[12]= "requisitado";
    requisicoes_ativas=0;
    for(int i=0; i<nlivro;i++){
        if(strcmp(livro[i].Estado, estado_requisitado) == 0){
            requisicoes_ativas++;
        }
    }

        printf("\t-- Gestao de Requisicoes de uma Biblioteca --\n\n");
        printf("Total de Livros:%d \t\t\t Total de Leitores:%d \n",nlivro,nleitor);
        printf("Total de Requisicoes ativas:%d \n\n", requisicoes_ativas);
        printf("\t1 - Registar Livro \n");
        printf("\t2 - Registar Leitor \n");
        printf("\t3 - Requisitar Livro \n");
        printf("\t4 - Devolver Livro \n");
        printf("\t5 - Listagens \n");
        printf("\t0 - Sair \n\n");

    do{
        fflush(stdin);
        printf("\t\tOPCAO: ");
        scanf("%d", &num);
        printf("\n");
        switch(num){
            case 1:
                registar_livro();
            break;
            case 2:
                registar_leitor();
            break;
            case 3:
                requisitar_livro();
            break;
            case 4:
                devolver_livro();
            break;
            case 5:
                listagens();
            break;
            case 0:
                sair();
            break;
            default:
                printf("Opcao invalida. Escolha uma do menu!\n\n");
        }
    }while(num!=1 && num!=2 && num!=3 && num!=4 && num!=5 && num!=0);

}
void registar_livro(){
    char opcao;


    fflush(stdin);
    printf("Digite o ISBN:\n");
    gets(livro[nlivro].ISBN);
    printf("O ISBN e %s \n\n", livro[nlivro].ISBN);

    fflush(stdin);
    printf("Digite o Titulo:\n");
    gets(livro[nlivro].Titulo);
    printf("O Titulo e %s\n\n", livro[nlivro].Titulo);

    fflush(stdin);
    printf("Digite o Autor:\n");
    gets(livro[nlivro].Autor);
    printf("O Autor e %s\n\n", livro[nlivro].Autor);

    fflush(stdin);
    printf("Digite a Editora:\n");
    gets(livro[nlivro].Editora);
    printf("A Editora e %s\n\n", livro[nlivro].Editora);

    strcpy(livro[nlivro].Estado, "disponivel");//Permite copiar strOrigem para strDestino.
    nlivro++;

    printf("\nDeseja registar outro Livro?\n");
    printf("Se sim, digite \"s\", se deseja voltar ao menu inicial pressione qualquer tecla!\n");

    fflush(stdin);
    scanf("%c", &opcao);
    switch(opcao){
        case 's':
        case 'S':
            registar_livro();
        break;
        default:
            menu();
    }

}
void registar_leitor(){
    char opcao;

    fflush(stdin);
    printf("Digite o Codigo de leitor:\n");
    scanf("%d", &leitor[nleitor].Codigo_leitor);
    printf("O Codigo de leitor e %d \n", leitor[nleitor].Codigo_leitor);

    fflush(stdin);
    printf("Nome:\n");
    gets(leitor[nleitor].Nome);
    printf("Nome e %s \n", leitor[nleitor].Nome);

    fflush(stdin);
    printf("Dia:\n");
    scanf("%d", &leitor[nleitor].Dia);
    printf("Dia e %d \n", leitor[nleitor].Dia);

    fflush(stdin);
    printf("Mes:\n");
    scanf("%d", &leitor[nleitor].Mes);
    printf("Mes e %d \n", leitor[nleitor].Mes);

    fflush(stdin);
    printf("Ano:\n");
    scanf("%d", &leitor[nleitor].Ano);
    printf("Ano e %d \n", leitor[nleitor].Ano);

    fflush(stdin);
    printf("Localidade:\n");
    gets(leitor[nleitor].Localidade);
    printf("A localidade e %s \n", leitor[nleitor].Localidade);

    fflush(stdin);
    printf("Contacto:\n");
    scanf("%d", &leitor[nleitor].Contacto);
    printf("O Codigo de leitor e %d \n", leitor[nleitor].Contacto);
    nleitor++;

    printf("\nDeseja registar outro Leitor?\n");
    printf("Se sim, digite \"s\", se deseja voltar ao menu inicial pressione qualquer tecla!\n");


    fflush(stdin);
    scanf("%c", &opcao);
    switch(opcao){
        case 's':
        case 'S':
            registar_leitor();
        break;
        default:
            menu();
    }


}
void requisitar_livro(){
    char estado_requisitado[14]= "Nao devolvido";
    int leitor_verificar;
    int i;

    printf("Digite o seu codigo de leitor!\n");
    fflush(stdin);
    scanf("%d", &leitor_verificar);
    for(i=0; i<nleitor;i++){
        if(leitor[i].Codigo_leitor == leitor_verificar){
            printf("Codigo de Leitor valido!\n");
            printf("Digite o Titulo do livro!\n");
            char titulo_livro[50];
            fflush(stdin);
            gets(titulo_livro);
            for(int n=0; n<nlivro; n++){
                if(strcmp(titulo_livro, livro[n].Titulo) == 0){//Permite comparar alfabeticamente duas strings. Devolve 0 - se as duas strings forem alfabeticamente iguais
                    printf("Titulo existe!\n");
                    char estado_disponivel[12]= "disponivel";
                    if(strcmp(livro[n].Estado, estado_disponivel) == 0){
                        printf("Esta disponivel\n");
                        printf("Insira a data da requisicao!\n");
                        fflush(stdin);
                        printf("Dia:\n");
                        scanf("%d", &livro[n].dia_requisitar);
                        fflush(stdin);
                        printf("Mes:\n");
                        scanf("%d", &livro[n].mes_requisitar);
                        fflush(stdin);
                        printf("Ano:\n");
                        scanf("%d", &livro[n].ano_requisitar);
                        requisicao[nrequisicoes].Codigo_leitor = leitor[i].Codigo_leitor;
                        strcpy(requisicao[nrequisicoes].ISBN,livro[n].ISBN);
                        requisicao[nrequisicoes].Dia = livro[n].dia_requisitar;
                        requisicao[nrequisicoes].Mes = livro[n].mes_requisitar;
                        requisicao[nrequisicoes].Ano = livro[n].ano_requisitar;
                        strcpy(requisicao[nrequisicoes].Estado_entrega,estado_requisitado);
                        nrequisicoes++;
                        leitor[i].livrosReq++;
                        strcpy(livro[n].Estado, "requisitado");//Permite copiar strOrigem para strDestino.
                        menu();
                    }else{
                        printf("Nao esta disponivel\n\n");
                        menu();
                    }
                }
            }
            printf("Livro nao encontrado!\n\n");
            menu();
        }
    }
    printf("Codigo de Leitor invalido!\n");
    printf("Faca o seu registo antes de requisitar um livro!\n\n");
    menu();

}
void devolver_livro(){
    char opcao;
    char isbn[14];
    char estado_disponivel[12]= "disponivel";
    printf("Insira o ISBN do livro!\n");
    fflush(stdin);
    gets(isbn);
    for(int n=0; n<nlivro;n++){
        if((strcmp(isbn, livro[n].ISBN) == 0) && (strcmp(estado_disponivel, livro[n].Estado) != 0)){
            printf("Livro devolvido!\n");
            strcpy(livro[n].Estado, "disponivel");
            int tempo_requisitar=calculo_data_requisitar(n);
            int tempo_atual=afixa_time();
            printf("O livro foi requisitado durante %d dias!\n\n",tempo_atual-tempo_requisitar);
            printf("O livro esta inutilizavel?\n");
            printf("Se sim, digite \"s\", se nao pressione qualquer tecla!\n");
            fflush(stdin);
            scanf("%c", &opcao);
            switch(opcao){
                case 's':
                case 'S':
                    for(int i=0; i<nrequisicoes;i++){
                        if(strcmp(livro[n].ISBN, requisicao[i].ISBN) == 0){
                            strcpy(requisicao[i].Estado_entrega, "inutilizavel");
                            strcpy(livro[n].Estado,"inutilizavel");
                        }
                    }
                break;
                default:
                     for(int i=0; i<nrequisicoes;i++){
                        if(strcmp(livro[n].ISBN, requisicao[i].ISBN) == 0){
                            strcpy(requisicao[i].Estado_entrega, "disponivel");
                            strcpy(livro[n].Estado,"disponivel");
                        }
                    }
                }
            printf("Pressione alguma tecla para continuar!\n\n");
            getch();
            menu();
        }
    }
    printf("Dados introduzidos incorretamente!\n\n");
    printf("Pressione alguma tecla para continuar!\n\n");
    getch();
    menu();
}

void listagens(){
    int num=0;
    int codigo=0;
    int variavel = 0;
    int semReq = 0;
        printf("\t-- Listagem --\n\n");
        printf("\t1 - Livro \n");
        printf("\t2 - Leitores \n");
        printf("\t3 - Livros Requisitados \n");
        printf("\t4 - As 10 ultimas requisicoes \n");
        printf("\t0 - Menu principal \n\n");
    do{
        fflush(stdin);
        printf("\t\tOPCAO: ");
        scanf("%d", &num);
        printf("\n");
        switch(num){
            case 1:
                for (int n = 0; n < nlivro; n++) {
                    printf("\nLivro%d:\n\n", n + 1);
                    printf("ISBN:\t\t %s\n", livro[n].ISBN);
                    printf("Titulo:\t\t %s\n", livro[n].Titulo);
                    printf("Autor:\t\t %s\n", livro[n].Autor);
                    printf("Editora:\t %s\n", livro[n].Editora);
                    printf("Estado: %s\n", livro[n].Estado);
                }
                printf("\nPressione uma tecla para continuar!\n\n");
                getch();
                listagens();
            break;
            case 2:
                for (int n = 0; n < nleitor; n++) {
                    printf("\nLeitor %d: \n\n", n + 1);
                    printf("Codigo_leitor:\t\t %d\n", leitor[n].Codigo_leitor);
                    printf("Nome:\t\t\t %s\n", leitor[n].Nome);
                    printf("Data de Nascimento:\t %d/%d/%d\n", leitor[n].Dia,leitor[n].Mes,leitor[n].Ano);
                    printf("Localidade:\t\t %s\n", leitor[n].Localidade);
                    printf("Contacto:\t\t %d\n\n", leitor[n].Contacto);
                }
                printf("\nPressione uma tecla para continuar!\n\n");
                getch();
                listagens();
            break;
            case 3:
                for(int n=0; n<nrequisicoes;n++){
                    printf("\nRequisicao %d \n\n", n+1);
                    printf("Codigo de leitor: %d\n", requisicao[n].Codigo_leitor);
                    printf("ISBN: %s\n", requisicao[n].ISBN);
                    printf("Data de requisicao: %d/%d/%d\n", requisicao[n].Dia,requisicao[n].Mes,requisicao[n].Ano);
                    printf("Estado da entrega: %s \n", requisicao[n].Estado_entrega);
                }
                printf("\n\n\tTotal de Requisicoes: %d \n\n", nrequisicoes);
                printf("\nPressione uma tecla para continuar!\n\n");
                getch();
                listagens();
            break;
            case 4:

                printf("Digite o seu codigo de leitor!\n");
                fflush(stdin);
                scanf("%d", &codigo);
                int numLeitor;
                for(int n=0; n<nrequisicoes;n++){
                    if(codigo == requisicao[n].Codigo_leitor){
                        if(variavel == 0){//Variavel serve para que este texto so aparece 1 vez
                            printf("\nUltimas 10 Requisicoes:\n");
                            printf("Codigo de leitor: %d\n\n", requisicao[n].Codigo_leitor);
                        }
                        printf("ISBN: %s\n", requisicao[n].ISBN);
                        printf("Data de requisicao: %d/%d/%d\n", requisicao[n].Dia,requisicao[n].Mes,requisicao[n].Ano);
                        printf("Estado da entrega: %s \n\n", requisicao[n].Estado_entrega);
                    } else {
                        for (int i = 0; i < nleitor; i++){              //Descobre o leitor associado ao codigo
                            if (leitor[i].Codigo_leitor == codigo) {
                                numLeitor = i;
                            }
                        }
                        if (leitor[numLeitor].livrosReq == 0){          //Verifica se o leitor requisitou algum livro
                            semReq = 1;
                        }
                    }
                    variavel =1;

                }
                if (semReq == 1){
                    printf("\nErro - Introduza um leitor com livros requisitados!\n");
                }
                printf("\nPressione uma tecla para continuar!\n\n");
                getch();
                listagens();
            break;
            case 0:
                menu();
            break;
            default:
                printf("Opcao invalida. Escolha uma do menu!\n\n");
        }
    }while(num!=1 && num!=2 && num!=3 && num!=4 && num!=0);

}
void carregar_ficheiro(){

        char estado_requisitado[12]= "requisitado";
        FILE *ficheiro;
        ficheiro = fopen("Biblioteca.txt", "r");
        fscanf(ficheiro, "\nNumero de Livros: %d\n",&nlivro);
        fscanf(ficheiro, "Numero de Leitores: %d\n", &nleitor);
        fscanf(ficheiro, "Numero de Requisicoes: %d\n\n", &nrequisicoes);
    for (int n = 0; n < nlivro; n++) {
        int n1=n+1;
        fscanf(ficheiro, "\nLivro %d:\n\n", &n1);
        fscanf(ficheiro, "ISBN: %s\n", livro[n].ISBN);
        fscanf(ficheiro, "Titulo: %s\n", livro[n].Titulo);
        fscanf(ficheiro, "Autor: %s\n", livro[n].Autor);
        fscanf(ficheiro, "Editora: %s\n", livro[n].Editora);
        fscanf(ficheiro, "Estado: %s\n", livro[n].Estado);
        if(strcmp(livro[n].Estado, estado_requisitado) == 0){
            fscanf(ficheiro, "Requisitado: %d/%d/%d\n", &livro[n].dia_requisitar,&livro[n].mes_requisitar,&livro[n].ano_requisitar);
        }
    }
    for (int n = 0; n < nleitor; n++) {
        int n1=n+1;
        fscanf(ficheiro, "\nLeitor %d: ", &n1);
        fscanf(ficheiro, "Codigo_leitor: %d\n", &leitor[n].Codigo_leitor);
        fscanf(ficheiro, "Nome: %s\n", leitor[n].Nome);
        fscanf(ficheiro, "Data de Nascimento: %d/%d/%d\n", &leitor[n].Dia,&leitor[n].Mes,&leitor[n].Ano);
        fscanf(ficheiro, "Localidade: %s\n", leitor[n].Localidade);
        fscanf(ficheiro, "Contacto: %d\n", &leitor[n].Contacto);
    }
    for(int n=0; n<nrequisicoes;n++){
        int n1=n+1;
        fscanf(ficheiro, "\nRequisicao %d \n\n", &n1);
        fscanf(ficheiro, "Codigo de leitor: %d\n", &requisicao[n].Codigo_leitor);
        fscanf(ficheiro, "ISBN: %s\n", requisicao[n].ISBN);
        fscanf(ficheiro, "Data de requisicao: %d/%d/%d\n", &requisicao[n].Dia,&requisicao[n].Mes,&requisicao[n].Ano);
        fscanf(ficheiro, "Estado da entrega: %s \n", requisicao[n].Estado_entrega);
    }
    fclose(ficheiro);
}
void guardar_ficheiro(){

        char estado_requisitado[12]= "requisitado";
        FILE *ficheiro;
        ficheiro = fopen("Biblioteca.txt", "w");
        fprintf(ficheiro, "\nNumero de Livros: %d\n",nlivro);
        fprintf(ficheiro, "Numero de Leitores: %d\n", nleitor);
        fprintf(ficheiro, "Numero de Requisicoes: %d\n\n", nrequisicoes);
    for (int n = 0; n < nlivro; n++) {
        fprintf(ficheiro, "\nLivro %d:\n\n", n + 1);
        fprintf(ficheiro, "ISBN: %s\n", livro[n].ISBN);
        fprintf(ficheiro, "Titulo: %s\n", livro[n].Titulo);
        fprintf(ficheiro, "Autor: %s\n", livro[n].Autor);
        fprintf(ficheiro, "Editora: %s\n", livro[n].Editora);
        fprintf(ficheiro, "Estado: %s\n", livro[n].Estado);
        if(strcmp(livro[n].Estado, estado_requisitado) == 0){
            fprintf(ficheiro, "Requisitado: %d/%d/%d\n", livro[n].dia_requisitar,livro[n].mes_requisitar,livro[n].ano_requisitar);
        }
    }
    for (int n = 0; n < nleitor; n++) {
        fprintf(ficheiro, "\nLeitor %d: \n\n", n + 1);
        fprintf(ficheiro, "Codigo_leitor: %d\n", leitor[n].Codigo_leitor);
        fprintf(ficheiro, "Nome: %s\n", leitor[n].Nome);
        fprintf(ficheiro, "Data de Nascimento: %d/%d/%d\n", leitor[n].Dia,leitor[n].Mes,leitor[n].Ano);
        fprintf(ficheiro, "Localidade: %s\n", leitor[n].Localidade);
        fprintf(ficheiro, "Contacto: %d\n", leitor[n].Contacto);
    }
    for(int n=0; n<nrequisicoes;n++){
        fprintf(ficheiro, "\nRequisicao %d \n\n", n+1);
        fprintf(ficheiro, "Codigo de leitor: %d\n", requisicao[n].Codigo_leitor);
        fprintf(ficheiro, "ISBN: %s\n", requisicao[n].ISBN);
        fprintf(ficheiro, "Data de requisicao: %d/%d/%d\n", requisicao[n].Dia,requisicao[n].Mes,requisicao[n].Ano);
        fprintf(ficheiro, "Estado da entrega: %s \n", requisicao[n].Estado_entrega);
    }
    fclose(ficheiro);
}
void sair(){
    char opcao;
    fflush(stdin);
    printf("\nDeseja sair?\n");
    printf("Se sim, digite \"s\", se deseja continuar digite qualquer tecla!\n");
    scanf("%c", &opcao);
    switch(opcao){
        case 's':
        case 'S':
            guardar_ficheiro();
            printf("\nO programa foi encerrado!\n");
            exit(0);
        break;
        default:
            menu();
    }
 }

int afixa_time(){//Calcula todos os dias desde a data 1/1/1 ate a data atual
    time_t tempo;
    struct tm *timeinfo;
    time(&tempo);
    timeinfo=localtime(&tempo);
    int dia_atual=timeinfo->tm_mday, mes_atual=timeinfo->tm_mon+1, ano_atual=timeinfo->tm_year+1900;
    printf("Data atual: %d/%d/%d\n",dia_atual,mes_atual,ano_atual);
    int dias_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int total_dias_atual = 0;
    int i=0;
    ano_atual=ano_atual-1;
    if(ano_atual%4 ==0){//Verifica se o ano anterior e bissexto ou nao.
        //Esta conta apesar de ser (int) pode ter na conta "0.75" e "0.25", porque como o ano e bissexto a conta nunca vai conter virgulas, logo nao se vai perder informacao.
        total_dias_atual+=ano_atual*0.75*365+ano_atual*0.25*366; //Calcula todos os dias desde 1/1/1 ate ao dia 31/12 do ano anterior.
    }else{//Se nao for bissexto
        for(i=0; ano_atual%4!=0;ano_atual--){//Remove anos ate que esta num ano bissexto
            i++;
        }
        total_dias_atual+=ano_atual*0.75*365+ano_atual*0.25*366+i*365;//Calcula todos os dias desde 1/1/1 ate ao dia 31/12 do ano anterior e depois soma os anos removidos e multiplica por 365 porque sao anos nao bissextos
    }
    ano_atual+=i+1;//Soma ao ano os anos que foram removidos no ciclo for, mais 1 que foi removido no inicio. Para verificar se o ano atual e bissexto ou nao
    if (ano_atual % 4 == 0) {//Verifica se o ano atual e bissexto
        dias_mes[1] = 29; //Modifica o vetor de index 1 para 29 devido aos anos bisextos
    }
    for (i = 0; i < mes_atual - 1; i++) {//Soma os dias dos meses.
        total_dias_atual += dias_mes[i];
    }
    total_dias_atual += dia_atual;//Soma o resto dos dias
    return total_dias_atual;

}

int calculo_data_requisitar(int n){
    printf("Data de requisicao %d/%d/%d\n",livro[n].dia_requisitar,livro[n].mes_requisitar,livro[n].ano_requisitar);
    int dias_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int total_dias_requisitar = 0;
    int i=0;
    int ano = livro[n].ano_requisitar;
    int mes = livro[n].mes_requisitar;
    ano=ano-1;

    if(ano%4 ==0){
        total_dias_requisitar+=ano*0.75*365+ano*0.25*366;
    }else{
        for(i=0; ano%4!=0;ano--){
            i++;
        }
        total_dias_requisitar+=ano*0.75*365+ano*0.25*366+i*365;
    }
    ano+=i+1;
    if (ano % 4 == 0) {//Ano bissexto
        dias_mes[1] = 29;
    }
    for (i = 0; i < mes - 1; i++) {
        total_dias_requisitar += dias_mes[i];
    }
    total_dias_requisitar += livro[n].dia_requisitar;
    return total_dias_requisitar;
}








