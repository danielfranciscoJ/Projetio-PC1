/*
Projeto PC1
Realizado por:
-Diogo Cravo nº2222030
-Daniel Jesus nº22
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
void exibir_menu_listagens();
void requisitar_ultimas_10();
int calcular_dias_atual();
int calcular_dias_requisicao(int);
void carregar_ficheiro();
void guardar_ficheiro();
void desligar_programa();


typedef struct {//Estrutura para os livros
    char ISBN[14]; //Pode armazenar até 13 dígitos incluindo '\0', (tem que ter ser char para poder guardar zeros a esquerda)
    char Titulo[50];
    char Autor[50];
    char Editora[50];
    char Estado[13];//Pode armazenar as palavras, disponível, requisitado ou inutilizavel + incluindo '\0'
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
    char Estado_entrega[13];//Estado do livro depois de entregar
}requisicoes_t;

livro_t livro[NLIVROS];
leitor_t leitor[NLEITORES];
requisicoes_t requisicao[NREQUISICOES];

int nlivro=0;
int nleitor=0;
int requisicoes_ativas=0;
int nrequisicoes=0;


int main(){
/*  Descrição: Chama a funcao 'carregar_ficheiro()' que carrega informacoes de um ficheiro
para o programa e de seguida chama a funcao 'exibir_menu()' que imprime o menu no monitor.
    Entradas: Nao tem
    Saidas: Nao tem
*/
    carregar_ficheiro();
    exibir_menu();
return 0;
}
void exibir_menu(){
/*  Descrição: Imprime o menu no monitor
    Entradas: Nao tem
    Saidas: Nao tem
*/

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
                exibir_menu_listagens();
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
/*  Descrição: Permite registar informação referente a um livro
    Entradas: Nao tem
    Saidas: Nao tem
*/
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
/*  Descrição: Permite registar informação referente a um leitor
    Entradas: Nao tem
    Saidas: Nao tem
*/
    char opcao;
    int  leitor_verificar;
    int var = 0;
    int verificar_data=0;

    //Codigo necessario para saber o ano atual
    time_t tempo;
    struct tm *timeinfo;
    time(&tempo);
    timeinfo=localtime(&tempo);
    int ano_atual=timeinfo->tm_year+1900;

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
    leitor[nleitor].Codigo_leitor= leitor_verificar;
    printf("\n\tO Codigo de leitor e %d \n\n", leitor[nleitor].Codigo_leitor);
    var = 0;

    fflush(stdin);
    printf("Insira o Nome: ");
    gets(leitor[nleitor].Nome);
    printf("\n\tNome e %s \n\n", leitor[nleitor].Nome);

    do{
        if(var == 1){
            printf("Data de Nascimento invalida!\n\n");
        }
        verificar_data=0;
        fflush(stdin);
        printf("Insira a data de Nascimento:\n\n");
        do{
           printf("Insira o Dia: ");
           scanf("%d", &leitor[nleitor].Dia);
        }while(leitor[nleitor].Dia > 31 || leitor[nleitor].Dia < 1);//Pede ao utilizador um dia entre o intervalo de 1 a 31
        printf("\n\tDia e %d \n\n", leitor[nleitor].Dia);

        fflush(stdin);
        do{
            printf("Insira o Mes: ");
            scanf("%d", &leitor[nleitor].Mes);
        }while(leitor[nleitor].Mes > 12 || leitor[nleitor].Mes < 1); //Pede ao utilizador um mes entre o intervalo de 1 a 12
        printf("\n\tMes e %d \n\n", leitor[nleitor].Mes);

        fflush(stdin);
        do{
           printf("Insira o Ano: ");
           scanf("%d", &leitor[nleitor].Ano);
        }while(leitor[nleitor].Ano < 1850 || leitor[nleitor].Ano > ano_atual); //Pede ao utilizador um ano entre o intervalo 1850 e o ano atual
        printf("\n\tAno e %d \n\n", leitor[nleitor].Ano);

        //Verifica se no mes de fevereiro foi introduzido mais de 29 dias em anos bissextos
        if(leitor[nleitor].Ano %4 == 0){
            if(leitor[nleitor].Mes == 2){
                if(leitor[nleitor].Dia > 29){
                     verificar_data = 1;
                     var=1;
                }
            }
        }
        //Verifica se no mes de fevereiro foi introduzido mais de 28 dias em anos nao bissextos
         if(leitor[nleitor].Ano %4 == 1){
            if(leitor[nleitor].Mes == 2){
                if(leitor[nleitor].Dia> 28){
                    verificar_data = 1;
                    var=1;
                }
            }
        }
        //Verifica se em abril, junho, setembro ou novembro tem mais de 30 dias
        if(leitor[nleitor].Mes == 4 || leitor[nleitor].Mes == 6 || leitor[nleitor].Mes == 9 || leitor[nleitor].Mes == 11){
            if(leitor[nleitor].Dia> 30){
                verificar_data = 1;
                var=1;
            }
        }
    }while(verificar_data==1);
    var = 0;

    printf("\tData de Nascimento: %d/%d/%d \n\n", leitor[nleitor].Dia, leitor[nleitor].Mes, leitor[nleitor].Ano);

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
/*  Descrição: Permite requisitar um livro
    Entradas: Nao tem
    Saidas: Nao tem
*/
    char isbn[14];
    int verificar_data = 0;
    int verificar_leitor = 0;

    printf("Digite o seu codigo de leitor: ");
    fflush(stdin);
    scanf("%d", &verificar_leitor);
    for(int i=0; i<nleitor;i++){
        if(leitor[i].Codigo_leitor == verificar_leitor){
            printf("\nDigite o ISBN do livro: ");
            fflush(stdin);
            gets(isbn);
            for(int n=0; n<nlivro; n++){
                if(strcmp(isbn, livro[n].ISBN) == 0){//Verifica se o livro esta registado
                    if(strcmp(livro[n].Estado, "disponivel") == 0 && strcmp(livro[n].Estado, "inutilizavel") != 0 ){//Verifica a disponibilidade do livro
                        printf("\nO livro esta disponivel!\n");
                        printf("\nInsira a data da requisicao!\n");

                        do{//Realiza o pedido da data de requisicao ate que a data seja valida!
                            if(verificar_data == 1){
                                printf("\nData Invalida!\n");
                                verificar_data = 0;
                            }
                            do{//Pede um numero do dia da requisicao ate estar entre 1 e 31
                                fflush(stdin);
                                printf("\nDia: ");
                                scanf("%d", &livro[n].dia_requisitar);
                            }while(livro[n].dia_requisitar <1 || livro[n].dia_requisitar >31);

                            do{//Pede um numero do mes da requisicao ate estar entre 1 e 12
                                fflush(stdin);
                                printf("\nMes: ");
                                scanf("%d", &livro[n].mes_requisitar);
                            }while(livro[n].mes_requisitar <1 || livro[n].mes_requisitar >12);

                            do{//Pede um numero do ano de requisicao ate ser maior que 2000
                                fflush(stdin);
                                printf("\nAno: ");
                                scanf("%d", &livro[n].ano_requisitar);
                            }while(livro[n].ano_requisitar<2000);

                            //Verifica se no mes de fevereiro foi introduzido mais de 29 dias em anos bissextos
                            if(livro[n].ano_requisitar %4 == 0){
                                if(livro[n].mes_requisitar == 2){
                                    if(livro[n].dia_requisitar > 29){
                                         verificar_data = 1;
                                    }
                                }
                            }
                            //Verifica se no mes de fevereiro foi introduzido mais de 28 dias em anos nao bissextos
                             if(livro[n].ano_requisitar %4 == 1){
                                if(livro[n].mes_requisitar == 2){
                                    if(livro[n].dia_requisitar> 28){
                                        verificar_data = 1;
                                    }
                                }
                            }
                            //Verifica se em abril, junho, setembro ou novembro tem mais de 30 dias
                            if(livro[n].mes_requisitar == 4 || livro[n].mes_requisitar == 6 || livro[n].mes_requisitar == 9 || livro[n].mes_requisitar == 11){
                                if(livro[n].dia_requisitar> 30){
                                    verificar_data = 1;
                                }
                            }
                        }while(verificar_data==1);
                        verificar_data = 0;

                        printf("\n\tData de requisicao: %d/%d/%d\n",livro[n].dia_requisitar, livro[n].mes_requisitar, livro[n].ano_requisitar);
                        printf("\nRequisicao realizada com sucesso!\n\n");

                        requisicao[nrequisicoes].Codigo_leitor = leitor[i].Codigo_leitor;
                        strcpy(requisicao[nrequisicoes].ISBN,livro[n].ISBN);
                        requisicao[nrequisicoes].Dia = livro[n].dia_requisitar;
                        requisicao[nrequisicoes].Mes = livro[n].mes_requisitar;
                        requisicao[nrequisicoes].Ano = livro[n].ano_requisitar;
                        strcpy(requisicao[nrequisicoes].Estado_entrega,"requisitado");
                        nrequisicoes++;
                        leitor[i].livrosReq++;
                        strcpy(livro[n].Estado, "requisitado");//Permite copiar strOrigem para strDestino.
                        printf("Pressione alguma tecla para continuar!\n\n");
                        getch();
                        exibir_menu();
                    }else{
                        printf("\nO livro nao esta disponivel!\n\n");
                        printf("Pressione alguma tecla para continuar!\n\n");
                        getch();
                        exibir_menu();
                    }
                }
            }
            printf("\nISBN invalido!\n");
            printf("Faca o registo do livro antes de o requisitar!\n\n");
            printf("Pressione alguma tecla para continuar!\n\n");
            getch();
            exibir_menu();
        }
    }
    printf("\nCodigo de Leitor invalido!\n");
    printf("Faca o registo do leitor antes de requisitar um livro!\n\n");
    printf("Pressione alguma tecla para continuar!\n\n");
    getch();
    exibir_menu();

}
void devolver_livro(){
/*  Descrição: Permite devolver um livro
    Entradas: Nao tem
    Saidas: Nao tem
*/
    int n=0;
    int verificar_isbn=0;
    char opcao;
    char isbn[14];

    printf("Insira o ISBN do livro: ");
    fflush(stdin);
    gets(isbn);
    for(int i=0; i<nlivro;i++){
        if(strcmp(isbn, livro[i].ISBN) == 0){
            n=i;
            verificar_isbn=1;
        }else{
            if(verificar_isbn !=1){
                verificar_isbn=0;
            }
        }
    }
    if(verificar_isbn==0){
        printf("\nISBN invalido!\n");
        printf("\nPressione alguma tecla para continuar!\n\n");
        getch();
        exibir_menu();
    }
    if(strcmp(livro[n].Estado, "requisitado") == 0){
        printf("\nLivro devolvido!\n\n");
        strcpy(livro[n].Estado, "disponivel");
        int tempo_requisitar=calcular_dias_requisicao(n);//a variavel tempo_requisitar armazena o valor retornado da funcao "calcular_dias_requisicao"
        int tempo_atual=calcular_dias_atual();////a variavel tempo_atual armazena o valor retornado da funcao "calcular_dias_atual"
        printf("O livro foi requisitado durante %d dias!\n\n",tempo_atual-tempo_requisitar);//imprime no monitor o numero de dias que o livro esteve requisitado
        printf("O livro esta inutilizavel?\n");
        printf("Pressione \"s\" se sim ou qualquer outra tecla se nao: ");
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
                printf("\nLivro devolvido!\n");
            break;
            default:
                 for(int i=0; i<nrequisicoes;i++){
                    if(strcmp(livro[n].ISBN, requisicao[i].ISBN) == 0){
                        strcpy(requisicao[i].Estado_entrega, "disponivel");
                        strcpy(livro[n].Estado,"disponivel");
                    }
                }
                printf("\nLivro devolvido!\n");
            }
        }else{
            printf("\nO livro nao foi requisitado!\n");
        }
    printf("\nPressione alguma tecla para continuar!\n\n");
    getch();
    exibir_menu();
}
void exibir_menu_listagens(){
/*  Descrição: Imprime o menu das listagens no monitor
    Entradas: Nao tem
    Saidas: Nao tem
*/
    int opcao=0;
    printf("\t-- Listagem --\n\n");
    printf("\t1 - Livro \n");
    printf("\t2 - Leitores \n");
    printf("\t3 - Livros Requisitados \n");
    printf("\t4 - As 10 ultimas requisicoes \n");
    printf("\t0 - Menu principal \n\n");

    do{
        fflush(stdin);
        printf("\t\tOPCAO: ");
        scanf("%d", &opcao);
        printf("\n");
        switch(opcao){
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
                exibir_menu_listagens();
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
                exibir_menu_listagens();
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
                exibir_menu_listagens();
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
    }while(opcao!=1 && opcao!=2 && opcao!=3 && opcao!=4 && opcao!=0);

}
void requisitar_ultimas_10(){
/*  Descrição: Imprime as 10 ultimas requisicoes de cada leitor
    Entradas: Nao tem
    Saidas: Nao tem
*/
    int n=0;
    int codigo=0;
    int verificar_leitor=0;
    int nrequisicoes_por_leitor = 0;
    int num_requisicoes;
    int incrementa=0;


    printf("Digite o codigo de leitor: ");
    fflush(stdin);
    scanf("%d", &codigo);


    for(int n=0; n<nrequisicoes;n++){//For para saber quantas requisicoes o leitor ja realizou
        if(codigo == requisicao[n].Codigo_leitor){
           nrequisicoes_por_leitor++;
           verificar_leitor=1;
        }
    }
    if(verificar_leitor !=1){
        printf("\nCodigo de Leitor invalido!\n");
        printf("\nPressione alguma tecla para continuar!\n\n");
        getch();
        exibir_menu_listagens();
    }

    num_requisicoes=nrequisicoes_por_leitor;//E necessario passar o valor das requisicoes para outra variavel porque depois quanto tiver a decrementar no ciclo for o valor tambem ira decrementar na condicao dentro do ciclo for o que nao e pretendido.
    printf("\nUltimas 10 Requisicoes:\n");
    printf("Codigo de leitor: %d\n\n", requisicao[n].Codigo_leitor);
    for(int n=0; n<(num_requisicoes+incrementa);n++){//e necessario somar a variavel incrementar para que as requisicoes que foram feitas por outros leitores nao contarem no for
        if(codigo == requisicao[n].Codigo_leitor){
            nrequisicoes_por_leitor--;
        }else{
            incrementa++;//Se a requisicao nao for feita pelo utilizador o valor de n nao pode ser incrementado
        }
        if(nrequisicoes_por_leitor<10){
            if(codigo == requisicao[n].Codigo_leitor){
                printf("ISBN: %s\n", requisicao[n].ISBN);
                for(int i=0; i<nlivro;i++){
                    if(strcmp(requisicao[n].ISBN,livro[i].ISBN)==0){
                        printf("Titulo: %s\n", livro[i].Titulo);
                    }
                }
                printf("Data de requisicao: %d/%d/%d\n", requisicao[n].Dia,requisicao[n].Mes,requisicao[n].Ano);
                printf("Estado da entrega: %s \n\n", requisicao[n].Estado_entrega);
            }
        }
    }
    printf("\nPressione uma tecla para continuar!\n\n");
    getch();
    exibir_menu_listagens();
}
int calcular_dias_atual(){
/*  Descrição: Calcula todos os dias desde que se passaram ate a data atual
    Entradas: Nao tem
    Saidas: total_dias_atual
*/
    //Codigo que fornece o tempo atual
    time_t tempo;
    struct tm *timeinfo;
    time(&tempo);
    timeinfo=localtime(&tempo);
    int dia_atual=timeinfo->tm_mday, mes_atual=timeinfo->tm_mon+1, ano_atual=timeinfo->tm_year+1900;

    int dias_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int total_dias_atual = 0;
    int incrementador =0;

    //Imprime no monitor o tempo real
    printf("Data atual:\t\t %d/%d/%d\n\n",dia_atual,mes_atual,ano_atual);
    ano_atual=ano_atual-1;
    if(ano_atual%4 ==0){//Verifica se o ano anterior e bissexto ou nao.
        //Esta conta apesar de ser (int) pode ter na conta "0.75" e "0.25", porque como o ano e bissexto a conta nunca vai conter virgulas, logo nao se vai perder informacao.
        total_dias_atual+=ano_atual*0.75*365+ano_atual*0.25*366; //Calcula todos os dias desde que se passaram ate ao dia 31/12 do ano anterior.
    }else{//Se nao for bissexto
        for(incrementador=0; ano_atual%4!=0; incrementador++){//Remove anos ate que esteja num ano bissexto
           ano_atual--;
        }
        total_dias_atual+=ano_atual*0.75*365+ano_atual*0.25*366+incrementador*365;//Calcula todos os dias ate ao dia 31/12 do ano anterior e depois soma os anos removidos e multiplica por 365 porque sao anos nao bissextos
    }
    ano_atual+=incrementador+1;//Soma ao ano os anos que foram removidos no ciclo for, mais 1 que foi removido no inicio. Para verificar se o ano atual e bissexto ou nao
    if (ano_atual % 4 == 0) {//Verifica se o ano atual e bissexto
        dias_mes[1] = 29; //Modifica o vetor de index 1 para 29 devido aos anos bisextos
    }
    for (int i = 0; i < mes_atual - 1; i++) {//Soma os dias dos meses.
        total_dias_atual += dias_mes[i];
    }
    total_dias_atual += dia_atual;//Soma o resto dos dias
    return total_dias_atual;

}
int calcular_dias_requisicao(int n){
/*  Descrição: Calcula todos os dias que se passaram ate a data atual
    Entradas: ‘n’ e o numero do indice da estrutura livro
    Saidas: ‘total_dias_requisitar’ é o número de dias que se passaram ate a data atual
*/
    printf("Data de requisicao:\t %d/%d/%d\n",livro[n].dia_requisitar,livro[n].mes_requisitar,livro[n].ano_requisitar);
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
void carregar_ficheiro(){
/*  Descrição: Carrega informacoes de um ficheiro para o programa
    Entradas: Nao tem
    Saidas: Nao tem
*/

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
        if(strcmp(livro[n].Estado, "requisitado") == 0){
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
/*  Descrição: Gruarda informacoes do programa para um ficheiro
    Entradas: Nao tem
    Saidas: Nao tem
*/

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
        if(strcmp(livro[n].Estado, "requisitado") == 0){
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
/*  Descrição: Encerra o programa
    Entradas: Nao tem
    Saidas: Nao tem
*/
    char opcao;
    fflush(stdin);
    printf("\nTem certeza que deseja sair?\n");
    printf("Pressione \"s\" para sair ou qualquer outra tecla para continuar!\n");
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







