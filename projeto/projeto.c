/*
Projeto PC1
Realizado por:
-Diogo Cravo
-*inserir_nome*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>


#define NLIVROS 50
#define NLEITORES 50
#define NREQUISICOES 50


void exibir_menu();
void registar_livro();
void registar_leitor();
void requisitar_livro();
void devolver_livro();
void exibir_munu_listagens();
void requisitar_ultimas_10();
int calcular_dias_atual();
int calcular_dias_requisicao(int);
void carregar_ficheiro();
void guardar_ficheiro();
void desligar_programa();
void listagem_req();
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

typedef struct {//Estruturas para guardar as requisicoes
    int Codigo_leitor;
    char ISBN[14];
    int Dia;//Dia em que foi requisitado
    int Mes;//Mes em que foi requisitado
    int Ano;//Ano em que foi requisitado
    char Estado_entrega[14];//Estado do livro depois de entregar
}requisicoes_t;

livro_t livro[NLIVROS];
leitor_t leitor[NLEITORES];
requisicoes_t requisicao[NREQUISICOES];

int nlivro=0;
int nleitor=0;
int requisicoes_ativas=0;
int nrequisicoes=0;


int main(){
    carregar_ficheiro();
    exibir_menu();
return 0;
}


void exibir_menu(){
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
                exibir_munu_listagens();
            break;
            case 0:
                desligar_programa();
            break;
            default:
                printf("Opcao invalida. Escolha uma do menu!\n\n");
        }
    }while(num!=1 && num!=2 && num!=3 && num!=4 && num!=5 && num!=0);

}
void registar_livro(){
    char opcao;
    char isbn_verificar[14];
    int var = 0;
    int string_comprimento=0;


    do{//Codigo Verifica se o ISBN tem 13 digitos
        if(var==1){
            printf("\nISBN necessita de conter 13 digitos!\n\n");
        }
        string_comprimento = 0;
        printf("Insira o ISBN: ");
        fflush(stdin);
        gets(isbn_verificar);
        while(isbn_verificar[string_comprimento] != '\0'){
            string_comprimento++;
        }
        var = 1;
    }while(string_comprimento != 13);
    var = 0;

    //Verifica se o ISBN ja esta registado no sistema!
    for(int i=0; i<nlivro;i++){
        if(strcmp(livro[i].ISBN,isbn_verificar)==0){
            if(var == 0){
                printf("\nO ISBN insirido ja existe! \n\n");
                var = 1;
                exibir_menu();
            }
        }
    }
    strcpy(livro[nlivro].ISBN,isbn_verificar);//Permite copiar strOrigem para strDestino.
    printf("\n\tO ISBN e %s \n\n", livro[nlivro].ISBN);
    var = 0;


    fflush(stdin);
    printf("Digite o Titulo: ");
    gets(livro[nlivro].Titulo);
    printf("\n\tO Titulo e %s\n\n", livro[nlivro].Titulo);

    fflush(stdin);
    printf("Digite o Autor: ");
    gets(livro[nlivro].Autor);
    printf("\n\tO Autor e %s\n\n", livro[nlivro].Autor);

    fflush(stdin);
    printf("Digite a Editora: ");
    gets(livro[nlivro].Editora);
    printf("\n\tA Editora e %s\n\n", livro[nlivro].Editora);

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
            exibir_menu();
    }

}
void registar_leitor(){
    char opcao;
    int  leitor_verificar;
    int var = 0;

    printf("Insira o Codigo de leitor: ");
    fflush(stdin);
    scanf("%d", &leitor_verificar);
    for(int i=0; i<nleitor;i++){
        if(leitor[i].Codigo_leitor == leitor_verificar){//Verifica se o codigo leitor ja existe
            if(var == 0){
                printf("\nO Codigo de leitor insirido ja existe! \n\n");
                var = 1;
                exibir_menu();
            }
        }
    }
    leitor_verificar = leitor[nleitor].Codigo_leitor;
    printf("\n\tO Codigo de leitor e %d \n\n", leitor[nleitor].Codigo_leitor);
    var = 0;

    fflush(stdin);
    printf("Insira o Nome: ");
    gets(leitor[nleitor].Nome);
    printf("\n\tNome e %s \n\n", leitor[nleitor].Nome);

    fflush(stdin);
    printf("Insira a data de Nascimento:\n\n");
    do{
       printf("Insira o Dia: ");
       scanf("%d", &leitor[nleitor].Dia);
    }while(leitor[nleitor].Dia > 31 || leitor[nleitor].Dia < 1);
    printf("\n\tDia e %d \n\n", leitor[nleitor].Dia);

    fflush(stdin);
    do{
        printf("Insira o Mes: ");
        scanf("%d", &leitor[nleitor].Mes);
    }while(leitor[nleitor].Mes > 12 || leitor[nleitor].Mes < 1);
    printf("\n\tMes e %d \n\n", leitor[nleitor].Mes);

    fflush(stdin);
    do{
       printf("Insira o Ano: ");
       scanf("%d", &leitor[nleitor].Ano);
    }while(leitor[nleitor].Ano < 1850);
    printf("\n\tAno e %d \n\n", leitor[nleitor].Ano);

    fflush(stdin);
    printf("Insita a Localidade: ");
    gets(leitor[nleitor].Localidade);
    printf("\n\tA localidade e %s \n\n", leitor[nleitor].Localidade);

    fflush(stdin);

    do{
        printf("Insira o Contacto: ");
        scanf("%d", &leitor[nleitor].Contacto);
    }while(leitor[nleitor].Contacto < 100000000 || leitor[nleitor].Contacto > 999999999);

    printf("\n\tO Codigo de leitor e %d \n\n", leitor[nleitor].Contacto);
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
            exibir_menu();
    }


}
void requisitar_livro(){
    char estado_requisitado[12]= "requisitado";
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

                        do{
                            fflush(stdin);
                            printf("Dia:\n");
                            scanf("%d", &livro[n].dia_requisitar);
                        }while(livro[n].dia_requisitar <1 || livro[n].dia_requisitar >31);

                        do{
                            fflush(stdin);
                            printf("Mes:\n");
                            scanf("%d", &livro[n].mes_requisitar);
                        }while(livro[n].mes_requisitar <1 || livro[n].mes_requisitar >12);

                        do{
                            fflush(stdin);
                            printf("Ano:\n");
                            scanf("%d", &livro[n].ano_requisitar);
                        }while(livro[n].ano_requisitar<2000);

                        requisicao[nrequisicoes].Codigo_leitor = leitor[i].Codigo_leitor;
                        strcpy(requisicao[nrequisicoes].ISBN,livro[n].ISBN);
                        requisicao[nrequisicoes].Dia = livro[n].dia_requisitar;
                        requisicao[nrequisicoes].Mes = livro[n].mes_requisitar;
                        requisicao[nrequisicoes].Ano = livro[n].ano_requisitar;
                        strcpy(requisicao[nrequisicoes].Estado_entrega,estado_requisitado);
                        nrequisicoes++;
                        leitor[i].livrosReq++;
                        strcpy(livro[n].Estado, "requisitado");//Permite copiar strOrigem para strDestino.
                        exibir_menu();
                    }else{
                        printf("Nao esta disponivel\n\n");
                        exibir_menu();
                    }
                }
            }
            printf("Livro nao encontrado!\n\n");
            exibir_menu();
        }
    }
    printf("Codigo de Leitor invalido!\n");
    printf("Faca o seu registo antes de requisitar um livro!\n\n");
    exibir_menu();

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
            int tempo_requisitar=calcular_dias_requisicao(n);
            int tempo_atual=calcular_dias_atual();
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
            exibir_menu();
        }
    }
    printf("Dados introduzidos incorretamente!\n\n");
    printf("Pressione alguma tecla para continuar!\n\n");
    getch();
    exibir_menu();
}
void exibir_munu_listagens(){
    int num=0;
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
                exibir_munu_listagens();
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
                exibir_munu_listagens();
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
                exibir_munu_listagens();
            break;
            case 4:
                requisitar_ultimas_10();
            break;
            case 0:
                exibir_menu();
            break;
            default:
                printf("Opcao invalida. Escolha uma do menu!\n\n");
        }
    }while(num!=1 && num!=2 && num!=3 && num!=4 && num!=0);

}
void listagem_req(){
    int leitor_verificar, leitorErro = 1;
    printf("\nIntroduza o codigo de leitor a selecionar: ");
    scanf("%d", &leitor_verificar);
    for(int n=0; n<nleitor && leitorErro != 0 ;n++){
        if(leitor[n].Codigo_leitor == leitor_verificar){
            leitorErro = 0;
            printf("Codigo de Leitor valido!\n");
        } else {
            leitorErro = 1;
        }
    }
    if (leitorErro == 1) {
        printf("\nIntroduziu um codigo errado\n\n");
        exibir_munu_listagens();
    }
}
void requisitar_ultimas_10(){
    int n=0;
    int codigo=0;
    int variavel = 0;
    int nrequisicoes_por_leitor = 0;
    int num_requisicoes;

    printf("Digite o seu codigo de leitor!\n");
    fflush(stdin);
    scanf("%d", &codigo);
    if(codigo == requisicao[n].Codigo_leitor){
        for(int n=0; n<nrequisicoes;n++){//For para saber quantas requisicoes o leitor ja realizou
            nrequisicoes_por_leitor++;
        }
        num_requisicoes=nrequisicoes_por_leitor;//E necessario passar o valor das requisicoes para outra variavel porque depois quanto tiver a decrementar no ciclo for o valor tambem ira decrementar na condicao dentro do ciclo for o que nao e pretendido.
    for(int n=0; n<num_requisicoes;n++){
        nrequisicoes_por_leitor--;
        if(nrequisicoes_por_leitor<10){
            if(variavel == 0){//Variavel serve para que este texto so aparece 1 vez
                printf("\nUltimas 10 Requisicoes:\n");
                printf("Codigo de leitor: %d\n\n", requisicao[n].Codigo_leitor);
                variavel =1;
            }
            printf("ISBN: %s\n", requisicao[n].ISBN);
            printf("Data de requisicao: %d/%d/%d\n", requisicao[n].Dia,requisicao[n].Mes,requisicao[n].Ano);
            printf("Estado da entrega: %s \n\n", requisicao[n].Estado_entrega);

        }

    }
    variavel =0;
    }else{
    printf("Leitor nao registado!\n");
    }
    printf("\nPressione uma tecla para continuar!\n\n");
    getch();
    exibir_munu_listagens();
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
void desligar_programa(){
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
            exibir_menu();
    }
 }
int calcular_dias_atual(){//Calcula todos os dias desde a data 1/1/1 ate a data atual
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
int calcular_dias_requisicao(int n){
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








