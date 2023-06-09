/*
PROJETO DE PROGRAMA��O DE COMPUTADORES I
REALIZADO POR:

NOME:               Diogo Filipe Vieira Cravo
N� DE ESTUDANTE:    2222030
EMAIL:              2222030@my.ipleiria.pt

NOME:               Daniel Francisco Carreira de Jesus
N� DE ESTUDANTE:    2221378
EMAIL:              2221378@my.ipleiria.pt
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
//As Bibliotecas <time.h> e <conio.h> utilizadas para obter o dia, o mes e o ano atual
#include <time.h>
#include <conio.h>
#include <ctype.h> //Biblioteca utilizada para as funcoes isalpha() e isdigit()

#define MAXLIVROS 50 //Numero maximo de livros
#define MAXLEITORES 50 //Numero maximo de leitores
#define MAXREQUISICOES MAXLEITORES*10 //O numero maximo de requisicoes e = MAXLEITORES*10
#define TEXTO 50 //Numero maximo de indice dos vetores: Titulo, Autor, Editora, Nome e Localidade

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


typedef struct {//Estrutura de vetores para guardar livros com as suas respetivas informacoes
    //ISBN de um livro e um numero unico que indentifica um livro
    //Pode armazenar ate 13 digitos incluindo '\0', (tem que ter ser char para poder guardar zeros a esquerda)
    char ISBN[14];
    char Titulo[TEXTO];//Titulo do livro. Informacao intruduzida pelo utilizador
    char Autor[TEXTO];//Autor do livro. Informacao intruduzida pelo utilizador
    char Editora[TEXTO];//Editora do livro. Informacao intruduzida pelo utilizador
    char Estado[13];//Pode armazenar as palavras, dispon�vel, requisitado ou inutilizavel, incluindo '\0'
    int dia_requisitar;//Dia em que o livro foi requisitado
    int mes_requisitar;//Mes em que o livro foi requisitado
    int ano_requisitar;//Ano em que o livro foi requisitado
} livro_t;
livro_t livro[MAXLIVROS];//Numero maximo de livros

typedef struct {//Estrutura de vetores para guardar leitores com as suas respetivas informacoes
    int Codigo_leitor;//Codigo de leitor unico para cada leitor
    char Nome[TEXTO];//Nome do leitor inserido pelo utilizador
    //As variaveis Dia, Mes e Ano sao referentes a data de Nascimento do leitor
    int Dia;//Dia em que o livro foi requisitado
    int Mes;//Mes em que o livro foi requisitado
    int Ano;//Ano em que o livro foi requisitado
    char Localidade[TEXTO];//
    char Contacto[10];////Pode armazenar ate 9 digitos incluindo '\0', e char para fazer protecao de dados mais facilmente
} leitor_t;
leitor_t leitor[MAXLEITORES];//Numero maximo de leitores


typedef struct {//Estrutura de vetores para guardar leitores com as suas respetivas informacoes
    int Codigo_leitor;//Codigo de leitor unico para cada leitor
    char ISBN[14];//Pode armazenar ate 13 digitos incluindo '\0', (tem que ter ser char para poder guardar zeros a esquerda)
    int Dia;//Dia em que o livro foi requisitado
    int Mes;//Mes em que o livro foi requisitado
    int Ano;//Ano em que o livro foi requisitado
    char Estado_entrega[13];//Pode armazenar as palavras, devolvido, requisitado ou inutilizavel + incluindo '\0'
} requisicoes_t;
requisicoes_t requisicao[MAXREQUISICOES];//Numero maximo de requesicoes


int nlivro=0;//Numero de livros
int nleitor=0;//Numero de leitores
int requisicoes_ativas=0;//Numero de livros que estao por devolver.
int nrequisicoes=0;//Numero de todas as requisicoes realizadas. Todos os livros devolvidos e por devolver.


int main() {
    /*  Descri��o: Chama a funcao 'carregar_ficheiro()' que carrega informacoes de um ficheiro
    para o programa e de seguida chama a funcao 'exibir_menu()' que imprime o menu no monitor.
        Entradas: Nao tem
        Saidas: Nao tem
    */

    carregar_ficheiro();
    exibir_menu();
    return 0;
}
void exibir_menu() {
    /*  Descri��o: Imprime o menu no monitor
        Entradas: Nao tem
        Saidas: Nao tem
    */
    char estado_requisitado[12]= "requisitado";//Vetor utilizado para verificar quantos livros estao requisitados
    int num=0;//Armazena um numero fornecido pelo utilizador com o intuito de escolher uma opcao do menu
    requisicoes_ativas=0;
    //Calcula o numero de requisicoes ativas
    for(int i=0; i<nlivro; i++) {
        if(strcmp(livro[i].Estado, estado_requisitado) == 0) {
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

    do {
        fflush(stdin);
        printf("\t\tOPCAO: ");
        scanf("%d", &num);
        printf("\n");
        switch(num) {
        case 1:
            system("cls");//Limpa a tela
            registar_livro();
            break;
        case 2:
            system("cls");//Limpa a tela
            registar_leitor();
            break;
        case 3:
            system("cls");//Limpa a tela
            requisitar_livro();
            break;
        case 4:
            system("cls");//Limpa a tela
            devolver_livro();
            break;
        case 5:
            system("cls");//Limpa a tela
            exibir_menu_listagens();
            break;
        case 0:
            system("cls");//Limpa a tela
            desligar_programa();
            break;
        default:
            printf("Escolha uma op��o v�lida do menu!\n\n");
        }
    } while(num!=1 && num!=2 && num!=3 && num!=4 && num!=5 && num!=0);

}
void registar_livro() {
    /*  Descri��o: Permite registar informa��o referente a um livro
        Entradas: Nao tem
        Saidas: Nao tem
    */
    int string_comprimento=0;//Verifica se o ISBN introduzido tem 13 caracteres
    int procurar_letras=0;//Verifica se o ISBN introduzido apenas tem digitos
    char isbn_verificar[14];//Vetor onde e guardado o ISBN
    int verificar_caracteres=0;//Verifica se o Autor introduzido apenas tem letras ou " "
    char opcao1;//Armazena dados fornecidos pelo utilizador com o intuito de escolher se o utilizador pertende confirmar o registo do livro
    char opcao2;//Armazena dados fornecidos pelo utilizador com o intuito de escolher se o utilizador pertende fazer outro registro

    if(nlivro<MAXLIVROS) {
        do { //Codigo Verifica se o ISBN tem 13 digitos

            string_comprimento = 0;
            do {
                procurar_letras=0;
                printf("Insira o ISBN: ");
                fflush(stdin);
                gets(isbn_verificar);
                for(int i =0; isbn_verificar[i] != '\0'; i++) { //Verifica o vetor isbn_verificar[i] ate ao final '\0'
                    if (isdigit(isbn_verificar[i]) == 0) {//isdigit devolve 0 se nao for numero (letras ou simbolos)
                        procurar_letras=1;//Verifica todo o vetor "isbn" caracter a caracter e se encontrar alguma coisa diferente de um numero passa a variavel procurar_letras para 1
                    }
                }
                if(procurar_letras ==1) {
                    printf("\nO ISBN e constituido apenas de numeros!\n\n");
                    printf("\nPressione uma tecla para continuar!\n");
                    getch();
                    system("cls");//Limpa a tela
                }
            } while(procurar_letras==1);//So sai do (do while) quando o utilizador digitar apenas numeros
            while(isbn_verificar[string_comprimento] != '\0') {
                string_comprimento++;
            }

            if(string_comprimento != 13) {
                printf("\nISBN necessita de conter 13 digitos!\n\n");
                printf("\nPressione uma tecla para continuar!\n");
                getch();
                system("cls");//Limpa a tela
            }
        } while(string_comprimento != 13);//So sai do (do while) quando o utilizador digitar 13 numeros

        //Verifica se o ISBN ja esta registado no sistema!
        for(int i=0; i<nlivro; i++) {
            if(strcmp(livro[i].ISBN,isbn_verificar)==0) {
                printf("\nO ISBN insirido ja existe! \n\n");
                printf("\nPressione alguma tecla para continuar!\n\n");
                getch();
                system("cls");//Limpa a tela
                exibir_menu();
            }
        }
        strcpy(livro[nlivro].ISBN,isbn_verificar);//Permite copiar strOrigem para strDestino.
        system("cls");//Limpa a tela

        fflush(stdin);
        printf("Digite o Titulo: ");
        gets(livro[nlivro].Titulo);
        system("cls");//Limpa a tela

        do {
            fflush(stdin);
            printf("Digite o Autor: ");
            gets(livro[nlivro].Autor);
            verificar_caracteres=0;
            for(int i =0; livro[nlivro].Autor[i] != '\0'; i++) { //Verifica o vetor Autor[i] ate ao final '\0'
                if ((isalpha(livro[nlivro].Autor[i]) == 0) && (livro[nlivro].Autor[i] != ' ')) {//isalpha devolve um numero 0 se nao for letra
                    verificar_caracteres=1;//Verifica todo o vetor nome caracter a caracter e se encontrar alguma coisa diferente de uma letra ou diferente de um "space" passa a variavel verificar_caracteres para 1
                }
            }
            if(verificar_caracteres == 1) {
                printf("\nO Nome apenas pode conter letras!\n\n");
                printf("\nPressione alguma tecla para continuar!\n\n");
                getch();
                system("cls");//Limpa a tela
            }
        } while(verificar_caracteres == 1);//So regista o autor se conter apenas letras
        printf("\n\tAutor: %s\n\n", livro[nlivro].Autor);
        system("cls");//Limpa a tela

        fflush(stdin);
        printf("Digite a Editora: ");
        gets(livro[nlivro].Editora);
        system("cls");//Limpa a tela

        strcpy(livro[nlivro].Estado, "disponivel");//Permite copiar strOrigem para strDestino.

        do {
            printf("Deseja confirmar o registo do livro? \n");
            printf("\nDigite \"s\" se sim ou \"n\" se nao: ");
            printf("\n\n\tISBN:\t\t%s", livro[nlivro].ISBN);
            printf("\n\tTitulo:\t\t%s", livro[nlivro].Titulo);
            printf("\n\tAutor:\t\t%s", livro[nlivro].Autor);
            printf("\n\tEditora:\t%s \n\n", livro[nlivro].Editora);
            printf("\t\tOPCAO: ");

            fflush(stdin);
            scanf("%c", &opcao1);
            switch(opcao1) { //Utilizado para saber se o utilizador pertende confirmar o registo do livro
            case 's':
            case 'S':
                system("cls");//Limpa a tela
                nlivro++;//Se o utilizador pretender guardar o registo o indice de n livro avanca 1 valor
                printf("Digite \"s\" para registar outro livro ou qualquer outra tecla para voltar ao menu:\n");
                printf("\n\t\tOPCAO: ");
                fflush(stdin);
                scanf("%c", &opcao2);
                printf("\n");
                switch(opcao2) { //Utilizado para saber se o utilizador pertende fazer outro registro
                case 's':
                case 'S':
                    system("cls");//Limpa a tela
                    registar_livro();
                    break;
                default:
                    system("cls");//Limpa a tela
                    exibir_menu();
                }
                break;
            case 'n':
            case 'N':
                system("cls");//Limpa a tela
                printf("Digite \"s\" para registar outro livro ou qualquer outra tecla para voltar ao menu: ");
                printf("\n\n\t\tOPCAO: ");
                fflush(stdin);
                scanf("%c", &opcao2);
                printf("\n");
                switch(opcao2) { //Utilizado para saber se o utilizador pertende fazer outro registro
                case 's':
                case 'S':
                    system("cls");//Limpa a tela
                    registar_livro();
                    break;
                default:
                    system("cls");//Limpa a tela
                    exibir_menu();
                }
                break;
            default:
                printf("\nNecessita de introduzir \"s\" ou \"n\"!\n\n");
            }
        } while(opcao1 != ('s' || 'S' || 'n' || 'N'));
    } else {
        printf("O numero maximo de registros de livros foi atingido!\n\n");
        printf("\nPressione uma tecla para continuar!\n");
        getch();
        system("cls");//Limpa a tela
        exibir_menu();
    }

}
void registar_leitor() {
    /*  Descri��o: Permite registar informa��o referente a um leitor
        Entradas: Nao tem
        Saidas: Nao tem
    */
    int verificar_leitor=0;//Variavel que pede ao utilizador o codigo de leitor
    int estado = 0;//Variavel que verifica se o codigo de leitor ja esta registado
    int verificar_caracteres=0;//Variavel que verifica se o nome intruduzido pelo utilizador contem caracteres
    int verificar_data=0;//Variavel que verifica se a data e valida
    int contacto_registado =0;//Variavel que verifica se o telemovel ja foi registado
    int incrementador=0;//Variavel que incrementa ate que o vetor leitor[nleitor].Contacto[n] seja  diferente de'\0' com o intuito de analisar se o contacto tem 9 numeros
    int verificar_contacto = 0;//Variavel que verifica se o contacto tem 9 digitos
    char opcao1;//Armazena dados fornecidos pelo utilizador com o intuito de escolher se o utilizador pertende confirmar o registo do leitor
    char opcao2;//Armazena dados fornecido pelo utilizador com o intuito de escolher se o utilizador pertende fazer outro registro


    if(nleitor<MAXLEITORES) {
        //Codigo necessario para saber o ano atual
        time_t tempo;
        struct tm *timeinfo;
        time(&tempo);
        timeinfo=localtime(&tempo);
        int ano_atual=timeinfo->tm_year+1900;//O ano atual e utilizado para definir como limete na data de nascimento

        printf("Insira o Codigo de leitor: ");
        fflush(stdin);
        scanf("%d", &verificar_leitor);
        for(int i=0; i<nleitor; i++) {
            if(leitor[i].Codigo_leitor == verificar_leitor) { //Verifica se o codigo leitor ja existe
                if(estado == 0) {
                    system("cls");//Limpa a tela
                    printf("O Codigo de leitor %d ja existe! \n\n",leitor[i].Codigo_leitor);
                    estado = 1;
                    printf("\nPressione alguma tecla para continuar!\n\n");
                    getch();
                    system("cls");//Limpa a tela
                    exibir_menu();
                }
            }
        }
        leitor[nleitor].Codigo_leitor= verificar_leitor;
        system("cls");//Limpa a tela

        do {
            fflush(stdin);
            printf("Insira o Nome: ");
            gets(leitor[nleitor].Nome);
            verificar_caracteres=0;
            for(int i =0; leitor[nleitor].Nome[i] != '\0'; i++) { //Verifica o vetor Nome[i] ate ao final '\0'
                if ((isalpha(leitor[nleitor].Nome[i]) == 0)&&(leitor[nleitor].Nome[i] != ' ')) {//isalpha devolve um numero 0 se nao for letra
                    verificar_caracteres=1;//Verifica todo o vetor nome caracter a caracter e se encontrar alguma coisa diferente de uma letra passa a variavel verificar_caracteres para 1
                }
            }

            if(verificar_caracteres==1) {
                printf("\nO Nome apenas pode conter letras!\n\n");
                printf("\nPressione alguma tecla para continuar!\n\n");
                getch();
                system("cls");//Limpa a tela
            }
        } while(verificar_caracteres == 1);//So regista o nome se conter apenas letras
        system("cls");//Limpa a tela
        do {
            if(verificar_data == 1) {
                printf("\nData de Nascimento invalida!\n\n");
                printf("\nPressione alguma tecla para continuar!\n\n");
                getch();
                system("cls");//Limpa a tela
            }
            verificar_data=0;
            printf("Insira a data de Nascimento:\n");

            do {
                printf("Insira o Dia: ");
                fflush(stdin);
                scanf("%d", &leitor[nleitor].Dia);
            } while(leitor[nleitor].Dia > 31 || leitor[nleitor].Dia < 1);//Pede ao utilizador um dia entre o intervalo de 1 a 31

            do {
                fflush(stdin);
                printf("Insira o Mes: ");
                scanf("%d", &leitor[nleitor].Mes);
            } while(leitor[nleitor].Mes > 12 || leitor[nleitor].Mes < 1); //Pede ao utilizador um mes entre o intervalo de 1 a 12


            do {
                fflush(stdin);
                printf("Insira o Ano: ");
                scanf("%d", &leitor[nleitor].Ano);
            } while(leitor[nleitor].Ano < 1850 || leitor[nleitor].Ano > ano_atual); //Pede ao utilizador um ano entre o intervalo 1850 e o ano atual


            //Verifica se no mes de fevereiro foi introduzido mais de 29 dias em anos bissextos
            if(leitor[nleitor].Ano %4 == 0) {//Resto da divisao inteira do ano bisexto e 0
                if(leitor[nleitor].Mes == 2) {
                    if(leitor[nleitor].Dia > 29) {
                        verificar_data = 1;
                    }
                }
            }
            //Verifica se no mes de fevereiro foi introduzido mais de 28 dias em anos nao bissextos
            if(leitor[nleitor].Ano %4 == 1 || leitor[nleitor].Ano %4 == 2 || leitor[nleitor].Ano %4 == 3) {//Resto da divisao inteira do ano bisexto e 1,2 ou 3
                if(leitor[nleitor].Mes == 2) {
                    if(leitor[nleitor].Dia> 28) {
                        verificar_data = 1;
                    }
                }
            }
            //Verifica se em abril, junho, setembro ou novembro tem mais de 30 dias
            if(leitor[nleitor].Mes == 4 || leitor[nleitor].Mes == 6 || leitor[nleitor].Mes == 9 || leitor[nleitor].Mes == 11) {
                if(leitor[nleitor].Dia> 30) {
                    verificar_data=1;
                }
            }
        } while(verificar_data==1);
        system("cls");//Limpa a tela


        fflush(stdin);
        printf("Insira a Localidade: ");
        gets(leitor[nleitor].Localidade);
        system("cls");//Limpa a tela

        do { //Pede um contacto ate o contacto ter 9 digitos
            incrementador=0;
            verificar_contacto=0;
            printf("Insira o Contacto: ");
            fflush(stdin);
            gets(leitor[nleitor].Contacto);
            contacto_registado=0;
            for(int i=0; i<nleitor; i++) {
                if(strcmp(leitor[nleitor].Contacto,leitor[i].Contacto)==0) {
                    contacto_registado=1;
                }
            }
            for (int n = 0; leitor[nleitor].Contacto[n] != '\0'; n++) {
                incrementador++;
            }
            for(int i =0; leitor[nleitor].Contacto[i] != '\0'; i++) { //Verifica o vetor Nome[i] ate ao final '\0'
                if(isdigit(leitor[nleitor].Contacto[i])==0) {
                    verificar_contacto=1;
                }
            }

            if(contacto_registado==1 || incrementador!=9 || verificar_contacto==1) {
                if(contacto_registado==1) {
                    printf("\nO contacto inserido ja se encontra resgistado!\n");
                }
                if(incrementador!=9) {
                    printf("\nO contacto inserido necessita de ter 9 digitos!\n");
                }

                if(verificar_contacto==1) {
                    printf("\nO contacto so pode conter numeros!\n\n");
                }
                printf("\n\nPressione uma tecla para continuar!\n");
                getch();
                system("cls");//Limpa a tela
            }


        } while(contacto_registado==1 || incrementador!=9 || verificar_contacto==1);
        do {
            system("cls");//Limpa a tela
            printf("Deseja confirmar o registo do leitor? \n");
            printf("\nDigite \"s\" se sim ou \"n\" se nao!\n");
            printf("\nCodigo de leitor:\t%d ", leitor[nleitor].Codigo_leitor);
            printf("\nNome:\t\t\t%s ", leitor[nleitor].Nome);
            printf("\nData de Nascimento:\t%d/%d/%d ", leitor[nleitor].Dia, leitor[nleitor].Mes, leitor[nleitor].Ano);
            printf("\nLocalidade:\t\t%s ", leitor[nleitor].Localidade);
            printf("\nContacto:\t\t%s ", leitor[nleitor].Contacto);
            printf("\n\n\t\tOPCAO: ");

            fflush(stdin);
            scanf("%c", &opcao1);
            switch(opcao1) {
            case 's':
            case 'S':
                system("cls");//Limpa a tela
                nleitor++;
                printf("Deseja registar outro Leitor?\n");
                printf("Digite \"s\" para registar outro leitor ou qualquer outra tecla para voltar ao menu: ");
                fflush(stdin);
                scanf("%c", &opcao2);
                switch(opcao2) {
                case 's':
                case 'S':
                    printf("\n");
                    system("cls");//Limpa a tela
                    registar_leitor();
                    break;
                default:
                    printf("\n");
                    system("cls");//Limpa a tela
                    exibir_menu();
                }
                break;
            case 'n':
            case 'N':
                system("cls");//Limpa a tela
                printf("Deseja registar outro Leitor?\n");
                printf("Digite \"s\" para registar outro leitor ou qualquer outra tecla para voltar ao menu: ");
                fflush(stdin);
                scanf("%c", &opcao2);
                switch(opcao2) {
                case 's':
                case 'S':
                    printf("\n");
                    system("cls");//Limpa a tela
                    registar_leitor();
                    break;
                default:
                    printf("\n");
                    system("cls");//Limpa a tela
                    exibir_menu();
                }
            default:
                printf("\nPor favor digite uma das opcoes disponiveis!\n");
            }
        } while(opcao1 != ('s' || 'S' || 'n' || 'N'));
    } else {
        printf("O numero maximo de registros de leitores foi atingido!\n\n");
        printf("\nPressione uma tecla para continuar!\n");
        getch();
        system("cls");//Limpa a tela
        exibir_menu();
    }
}
void requisitar_livro() {
    /*  Descri��o: Permite requisitar um livro
        Entradas: Nao tem
        Saidas: Nao tem
    */
    int verificar_leitor = 0;//Armazena o codigo de leitor intoduzido pelo leitor e compara com todos os codigos de leitores para verificar se o leitor ja existe
    char isbn[14];//Armazena o  ISBN intoduzido pelo leitor e compara com todos os ISBN para verificar se o livro esta registado
    int verificar_data = 0;//Verifica se a data introduzida pelo utilizador e valida
    time_t tempo;
    struct tm *timeinfo;
    time(&tempo);
    timeinfo=localtime(&tempo);
    int ano_atual=timeinfo->tm_year+1900;//O ano atual e utilizado para definir como limete na data de requisicao

    if(nrequisicoes<MAXREQUISICOES) {
        printf("Digite o seu codigo de leitor: ");
        fflush(stdin);
        scanf("%d", &verificar_leitor);
        for(int i=0; i<nleitor; i++) {
            if(leitor[i].Codigo_leitor == verificar_leitor) {
                system("cls");//Limpa a tela
                printf("Digite o ISBN do livro: ");
                fflush(stdin);
                gets(isbn);
                for(int n=0; n<nlivro; n++) {
                    if(strcmp(isbn, livro[n].ISBN) == 0) { //Verifica se o livro esta registado
                        if(strcmp(livro[n].Estado, "disponivel") == 0 && strcmp(livro[n].Estado, "inutilizavel") != 0 ) { //Verifica a disponibilidade do livro
                            system("cls");//Limpa a tela
                            printf("Insira a data da requisicao!\n");

                            do { //Realiza o pedido da data de requisicao ate que a data seja valida!
                                if(verificar_data == 1) {
                                    printf("\nData Invalida!\n");
                                    printf("\nPressione alguma tecla para continuar!\n\n");
                                    getch();
                                    system("cls");//Limpa a tela
                                    printf("Insira a data da requisicao!\n");
                                }
                                verificar_data=0;
                                do { //Pede um numero do dia da requisicao ate estar entre 1 e 31
                                    printf("\nDia: ");
                                    scanf("%d", &livro[n].dia_requisitar);
                                } while(livro[n].dia_requisitar <1 || livro[n].dia_requisitar >31);

                                do { //Pede um numero do mes da requisicao ate estar entre 1 e 12
                                    printf("Mes: ");
                                    scanf("%d", &livro[n].mes_requisitar);
                                } while(livro[n].mes_requisitar <1 || livro[n].mes_requisitar >12);

                                do { //Pede um numero do ano de requisicao ate ser maior que 2000
                                    printf("Ano: ");
                                    scanf("%d", &livro[n].ano_requisitar);
                                } while(livro[n].ano_requisitar<2000 || livro[n].ano_requisitar>ano_atual);

                                //Verifica se no mes de fevereiro foi introduzido mais de 29 dias em anos bissextos
                                if(livro[n].ano_requisitar %4 == 0) {
                                    if(livro[n].mes_requisitar == 2) {
                                        if(livro[n].dia_requisitar > 29) {
                                            verificar_data = 1;
                                        }
                                    }
                                }
                                //Verifica se no mes de fevereiro foi introduzido mais de 28 dias em anos nao bissextos
                                if(livro[n].ano_requisitar %4 == 1 || livro[n].ano_requisitar %4 == 2 ||livro[n].ano_requisitar %4 == 3) {
                                    if(livro[n].mes_requisitar == 2) {
                                        if(livro[n].dia_requisitar> 28) {
                                            verificar_data = 1;
                                        }
                                    }
                                }
                                //Verifica se em abril, junho, setembro ou novembro tem mais de 30 dias
                                if(livro[n].mes_requisitar == 4 || livro[n].mes_requisitar == 6 || livro[n].mes_requisitar == 9 || livro[n].mes_requisitar == 11) {
                                    if(livro[n].dia_requisitar> 30) {
                                        verificar_data = 1;
                                    }
                                }
                            } while(verificar_data==1);
                            verificar_data = 0;
                            system("cls");//Limpa a tela

                            printf("Data de requisicao: %d/%d/%d\n",livro[n].dia_requisitar, livro[n].mes_requisitar, livro[n].ano_requisitar);
                            printf("\nRequisicao realizada com sucesso!\n\n");

                            requisicao[nrequisicoes].Codigo_leitor = leitor[i].Codigo_leitor;
                            strcpy(requisicao[nrequisicoes].ISBN,livro[n].ISBN);
                            requisicao[nrequisicoes].Dia = livro[n].dia_requisitar;
                            requisicao[nrequisicoes].Mes = livro[n].mes_requisitar;
                            requisicao[nrequisicoes].Ano = livro[n].ano_requisitar;
                            strcpy(requisicao[nrequisicoes].Estado_entrega,"requisitado");
                            nrequisicoes++;
                            strcpy(livro[n].Estado, "requisitado");//Permite copiar strOrigem para strDestino.
                            printf("Pressione alguma tecla para continuar!\n\n");
                            getch();
                            system("cls");//Limpa a tela
                            exibir_menu();
                        } else {
                            system("cls");//Limpa a tela
                            printf("O livro nao esta disponivel!\n\n");
                            printf("Pressione alguma tecla para continuar!\n\n");
                            getch();
                            system("cls");//Limpa a tela
                            exibir_menu();
                        }
                    }
                }
                printf("\nISBN invalido!\n");
                printf("Faca o registo do livro antes de o requisitar!\n\n");
                printf("Pressione alguma tecla para continuar!\n\n");
                getch();
                system("cls");//Limpa a tela
                exibir_menu();
            }
        }
        printf("\nCodigo de Leitor invalido!\n");
        printf("Faca o registo do leitor antes de requisitar um livro!\n\n");
        printf("Pressione alguma tecla para continuar!\n\n");
        getch();
        system("cls");//Limpa a tela
        exibir_menu();
    } else {
        printf("O maximo de requisicoes foi atingido!\n\n");
        printf("\nPressione alguma tecla para continuar!\n\n");
        getch();
        system("cls");//Limpa a tela
        exibir_menu();
    }

}
void devolver_livro() {
    /*  Descri��o: Permite devolver um livro
        Entradas: Nao tem
        Saidas: Nao tem
    */
    char isbn[14];//Pede o ISBN ao utilizador
    int verificar_isbn=0;//Verifica se o ISBN ja existe
    int n=0;//Define o Indice do vetor
    char opcao;//Variavel utilizada para saber se o livro esta inutilizavel ou nao.

    printf("Insira o ISBN do livro: ");
    fflush(stdin);
    gets(isbn);
    for(int i=0; i<nlivro; i++) {
        if(strcmp(isbn, livro[i].ISBN) == 0) {
            n=i;
            verificar_isbn=1;
        } else {
            if(verificar_isbn !=1) {
                verificar_isbn=0;
            }
        }
    }
    if(verificar_isbn==0) {
        printf("\nISBN invalido!\n");
        printf("\nPressione alguma tecla para continuar!\n\n");
        getch();
        system("cls");//Limpa a tela
        exibir_menu();
    }
    system("cls");//Limpa a tela
    if(strcmp(livro[n].Estado, "requisitado") == 0) {

        printf("Livro devolvido!\n\n");
        strcpy(livro[n].Estado, "disponivel");
        int tempo_requisitar=calcular_dias_requisicao(n);//A variavel tempo_requisitar armazena o valor retornado da funcao "calcular_dias_requisicao"
        int tempo_atual=calcular_dias_atual();//A variavel tempo_atual armazena o valor retornado da funcao "calcular_dias_atual"
        printf("O livro foi requisitado durante %d dias!\n\n",tempo_atual-tempo_requisitar);//Imprime no monitor o numero de dias que o livro esteve requisitado
        printf("O livro esta inutilizavel?\n");
        printf("Pressione \"s\" se sim ou qualquer outra tecla se nao: ");
        fflush(stdin);
        scanf("%c", &opcao);
        switch(opcao) {
        case 's':
        case 'S':
            strcpy(livro[n].Estado,"inutilizavel");
            for(int i=MAXREQUISICOES; i>=0; i--) { //Verifica a estrutura requisicao de tras para a frente para encontrar a ultima requisicao feita
                if(strcmp(isbn, requisicao[i].ISBN) == 0) {
                    printf("%d",i);
                    strcpy(requisicao[i].Estado_entrega, "inutilizavel");
                    printf("\nO livro esta inutilizavel!\n");
                    printf("\nPressione alguma tecla para continuar!\n\n");
                    getch();
                    system("cls");//Limpa a tela

                    exibir_menu();
                }
            }

            break;
        default:
            for(int i=0; i<nrequisicoes; i++) {
                if(strcmp(livro[n].ISBN, requisicao[i].ISBN) == 0) {
                    strcpy(requisicao[i].Estado_entrega, "devolvido");
                    strcpy(livro[n].Estado,"disponivel");
                }
            }
            printf("\nO livro nao esta inutilizavel!\n");
        }
    } else {
        printf("O livro nao ainda nao foi requisitado!\n");
    }
    printf("\nPressione alguma tecla para continuar!\n\n");
    getch();
    system("cls");//Limpa a tela
    exibir_menu();
}
void exibir_menu_listagens() {
    /*  Descri��o: Imprime o menu das listagens no monitor
        Entradas: Nao tem
        Saidas: Nao tem
    */
    int opcao=0;//Armazena um numero fornecido pelo utilizador com o intuito de escolher uma opcao do menu listagens

    do {
        printf("\t-- Listagens --\n\n");
        printf("\t1 - Livro \n");
        printf("\t2 - Leitores \n");
        printf("\t3 - Livros Requisitados \n");
        printf("\t4 - As 10 ultimas requisicoes \n");
        printf("\t0 - Menu principal \n\n");
        fflush(stdin);
        printf("\t\tOPCAO: ");
        scanf("%d", &opcao);
        printf("\n");
        switch(opcao) {
        case 1:
            system("cls");//Limpa a tela
            printf("\t-- Livros --\n");
            for (int n = 0; n < nlivro; n++) {
                printf("\nLivro %d:\n\n", n + 1);
                printf("ISBN:\t\t %s\n", livro[n].ISBN);
                printf("Titulo:\t\t %s\n", livro[n].Titulo);
                printf("Autor:\t\t %s\n", livro[n].Autor);
                printf("Editora:\t %s\n", livro[n].Editora);
                printf("Estado:\t\t %s\n", livro[n].Estado);
            }
            printf("\nPressione uma tecla para continuar!\n\n");
            getch();
            system("cls");//Limpa a tela
            exibir_menu_listagens();//Volta ao menu listagens
            break;
        case 2:
            system("cls");//Limpa a tela
            printf("\t-- Leitores --\n");
            for (int n = 0; n < nleitor; n++) {
                printf("\nLeitor %d: \n\n", n + 1);
                printf("Codigo_leitor:\t\t %d\n", leitor[n].Codigo_leitor);
                printf("Nome:\t\t\t %s\n", leitor[n].Nome);
                printf("Data de Nascimento:\t %d/%d/%d\n", leitor[n].Dia,leitor[n].Mes,leitor[n].Ano);
                printf("Localidade:\t\t %s\n", leitor[n].Localidade);
                printf("Contacto:\t\t %s\n\n", leitor[n].Contacto);
            }
            printf("\nPressione uma tecla para continuar!\n\n");
            getch();
            system("cls");//Limpa a tela
            exibir_menu_listagens();//Volta ao menu listagens
            break;
        case 3:
            system("cls");//Limpa a tela
            printf("\t-- Requisicoes --\n");
            for(int n=0; n<nrequisicoes; n++) {
                printf("\nRequisicao %d: \n\n", n+1);
                printf("Codigo de leitor:\t%d\n", requisicao[n].Codigo_leitor);
                printf("ISBN:\t\t\t%s\n", requisicao[n].ISBN);
                printf("Data de requisicao:\t%d/%d/%d\n", requisicao[n].Dia,requisicao[n].Mes,requisicao[n].Ano);
                printf("Estado da entrega:\t%s \n", requisicao[n].Estado_entrega);
            }
            printf("\n\n\tTotal de Requisicoes: %d \n\n", nrequisicoes);
            printf("\nPressione uma tecla para continuar!\n\n");
            getch();
            system("cls");//Limpa a tela
            exibir_menu_listagens();//Volta ao menu listagens
            break;
        case 4:
            system("cls");//Limpa a tela
            requisitar_ultimas_10();
            break;
        case 0:
            system("cls");//Limpa a tela
            exibir_menu();//Volta ao menu
            break;
        default:
            system("cls");//Limpa a tela
            printf("Opcao invalida. Escolha uma do menu!\n\n");
            printf("\nPressione alguma tecla para continuar!\n\n");
            getch();
            system("cls");//Limpa a tela
        }
    } while(opcao!=1 && opcao!=2 && opcao!=3 && opcao!=4 && opcao!=0);

}
void requisitar_ultimas_10() {
    /*  Descri��o: Imprime as 10 ultimas requisicoes de cada leitor
        Entradas: Nao tem
        Saidas: Nao tem
    */
    int leitor_codigo=0;//Pede o o codigo de leitor ao utilizador
    int verificar_leitor=0;//Verifica se o codigo de leitor e valido
    int nrequisicoes_por_leitor = 0;//Verifica quantas requisicoes foram feitas pelo leitor
    int num_requisicoes;//Passa o valor da variavel nrequisicoes_por_leitor
    //Porque depois quanto tiver a decrementar no ciclo for o valor tambem ira decrementar na condicao dentro do ciclo for o que nao e pretendido.
    int incrementa=0;//Variavel incrementa para que as requisicoes que foram feitas por outros leitores nao contarem no for


    printf("Digite o codigo de leitor: ");
    fflush(stdin);
    scanf("%d", &leitor_codigo);
    system("cls");//Limpa a tela


    for(int n=0; n<nrequisicoes; n++) { //For para saber quantas requisicoes o leitor ja realizou
        if(leitor_codigo == leitor[n].Codigo_leitor) {
            verificar_leitor=1;
        }
    }
    if(verificar_leitor !=1) {
        printf("\nCodigo de Leitor invalido!\n");
        printf("\nPressione alguma tecla para continuar!\n\n");
        getch();
        system("cls");//Limpa a tela
        exibir_menu_listagens();
    }

    for(int n=0; n<nrequisicoes; n++) { //For para saber quantas requisicoes o leitor ja realizou
        if(leitor_codigo == requisicao[n].Codigo_leitor) {
            nrequisicoes_por_leitor++;
        }
    }

    printf("\t-- Ultimas 10 Requisicoes do leitor %d --\n\n", leitor_codigo);
    if(nrequisicoes_por_leitor==0) {
        printf("O leitor ainda nao requisitou nenhum livro!\n");

    } else {
        num_requisicoes=nrequisicoes_por_leitor;//E necessario passar o valor das requisicoes para outra variavel porque depois quanto tiver a decrementar no ciclo for o valor tambem ira decrementar na condicao dentro do ciclo for o que nao e pretendido.
        for(int n=0; n<(num_requisicoes+incrementa); n++) { //e necessario somar a variavel incrementar para que as requisicoes que foram feitas por outros leitores nao contarem no for
            if(leitor_codigo == requisicao[n].Codigo_leitor) {
                nrequisicoes_por_leitor--;
            } else {
                incrementa++;//Se a requisicao nao for feita pelo utilizador o valor de n nao pode ser incrementado
            }
            if(nrequisicoes_por_leitor<10) {
                if(leitor_codigo == requisicao[n].Codigo_leitor) {
                    printf("ISBN: %s\n", requisicao[n].ISBN);
                    for(int i=0; i<nlivro; i++) {
                        if(strcmp(requisicao[n].ISBN,livro[i].ISBN)==0) {
                            printf("Titulo: %s\n", livro[i].Titulo);
                        }
                    }
                    printf("Data de requisicao: %d/%d/%d\n", requisicao[n].Dia,requisicao[n].Mes,requisicao[n].Ano);
                    printf("Estado da entrega: %s \n\n", requisicao[n].Estado_entrega);
                }
            }
        }
    }

    printf("\nPressione uma tecla para continuar!\n\n");
    getch();
    system("cls");//Limpa a tela
    exibir_menu_listagens();
}
int calcular_dias_atual() {
    /*  Descri��o: Calcula todos os dias desde que se passaram ate a data atual
        Entradas: Nao tem
        Saidas: total_dias_atual
    */
    //Codigo que fornece o tempo atual
    time_t tempo;
    struct tm *timeinfo;
    time(&tempo);
    timeinfo=localtime(&tempo);
    int dia_atual=timeinfo->tm_mday, mes_atual=timeinfo->tm_mon+1, ano_atual=timeinfo->tm_year+1900;

    int total_dias_atual = 0;//Variavel que guarda a soma de todos os dias
    int incrementador =0;//Variavel que incrementa ate um ano bissexto
    int dias_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//numero de dias em todos os meses num ano nao bissexto

    //Imprime no monitor o tempo real
    printf("Data atual:\t\t %d/%d/%d\n\n",dia_atual,mes_atual,ano_atual);
    ano_atual=ano_atual-1;//Subtrai 1 ano porque o pretendido e calcular o numero de dias ate ao dia 31/12 do ano anterior ira ser calculado o resto dos dias no ano presente mais a frente no codigo
    if(ano_atual%4 ==0) { //Verifica se o ano anterior e bissexto ou nao.
        //Esta conta apesar de ser (int) pode ter na conta "0.75" e "0.25", porque como o ano e bissexto a conta nunca vai conter virgulas, logo nao se vai perder informacao.
        total_dias_atual+=ano_atual*0.75*365+ano_atual*0.25*366; //Calcula todos os dias desde que se passaram ate ao dia 31/12 do ano anterior.
    } else { //Se nao for bissexto
        for(incrementador=0; ano_atual%4!=0; incrementador++) { //Remove anos ate que esteja num ano bissexto
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
int calcular_dias_requisicao(int n) {
    /*  Descri��o: Calcula todos os dias que se passaram ate a data atual
        Entradas: �n� e o numero do indice da estrutura livro
        Saidas: �total_dias_requisitar� � o n�mero de dias que se passaram ate a data atual
    */
    printf("Data de requisicao:\t %d/%d/%d\n",livro[n].dia_requisitar,livro[n].mes_requisitar,livro[n].ano_requisitar);
    int ano = livro[n].ano_requisitar;//Passa o valor de livro[n].ano_requisitar para variavel ano
    int mes = livro[n].mes_requisitar;//Passa o valor de livro[n].mes_requisitar para variavel mes
    int total_dias_requisitar = 0;//Variavel que guarda a soma de todos os dias
    int i=0;//Variavel que incrementa ate que o ano seja bissexto
    int dias_mes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//numero de dias em todos os meses num ano nao bissexto

    ano=ano-1;//Subtrai 1 ano porque o pretendido e calcular o numero de dias ate ao dia 31/12 do ano anterior ira ser calculado o resto dos dias no ano presente mais a frente no codigo
    if(ano%4 ==0) { //Verifica se o ano anterior e bissexto ou nao.
        total_dias_requisitar+=ano*0.75*365+ano*0.25*366; //Esta conta apesar de ser (int) pode ter na conta "0.75" e "0.25", porque como o ano e bissexto a conta nunca vai conter virgulas, logo nao se vai perder informacao.
    } else {
        for(i=0; ano%4!=0; ano--) {
            i++;
        }
        total_dias_requisitar+=ano*0.75*365+ano*0.25*366+i*365;//Calcula todos os dias desde que se passaram ate ao dia 31/12 do ano anterior.
    }
    ano+=i+1;//Soma ao ano os anos que foram removidos no ciclo for, mais 1 que foi removido no inicio. Para verificar se o ano atual e bissexto ou nao
    if (ano % 4 == 0) {//Verifica se o ano atual e bissexto
        dias_mes[1] = 29;//Modifica o vetor de index 1 para 29 devido aos anos bisextos
    }
    for (i = 0; i < mes - 1; i++) {//Soma os dias dos meses.
        total_dias_requisitar += dias_mes[i];
    }
    total_dias_requisitar += livro[n].dia_requisitar;//Soma o resto dos dias
    return total_dias_requisitar;
}
void carregar_ficheiro() {
    /*  Descri��o: Carrega informacoes de um ficheiro para o programa
        Entradas: Nao tem
        Saidas: Nao tem
    */
    FILE *ficheiro;//Ponteiro para ficheiro
    ficheiro = fopen("Biblioteca.dat", "rb");
    if(ficheiro == NULL) { //Testar se �funcionou�
        printf("Criacao do ficheiro!\n\n");
    }
    fread(&nlivro,sizeof(nlivro),1,ficheiro);
    fread(&nleitor,sizeof(nleitor),1,ficheiro);
    fread(&nrequisicoes,sizeof(nrequisicoes),1,ficheiro);

    for (int n = 0; n < nlivro; n++) {
        fread(livro[n].ISBN,sizeof(livro[n].ISBN),1,ficheiro);
        fread(livro[n].Titulo,sizeof(livro[n].Titulo),1,ficheiro);
        fread(livro[n].Autor,sizeof(livro[n].Autor),1,ficheiro);
        fread(livro[n].Editora,sizeof(livro[n].Editora),1,ficheiro);
        fread(livro[n].Estado,sizeof(livro[n].Estado),1,ficheiro);
        if(strcmp(livro[n].Estado, "requisitado") == 0) {
            fread(&livro[n].dia_requisitar,sizeof(livro[n].dia_requisitar),1,ficheiro);
            fread(&livro[n].mes_requisitar,sizeof(livro[n].mes_requisitar),1,ficheiro);
            fread(&livro[n].ano_requisitar,sizeof(livro[n].ano_requisitar),1,ficheiro);
        }
    }
    for (int n = 0; n < nleitor; n++) {
        fread(&leitor[n].Codigo_leitor,sizeof(leitor[n].Codigo_leitor),1,ficheiro);
        fread(leitor[n].Nome,sizeof(leitor[n].Nome),1,ficheiro);
        fread(&leitor[n].Dia,sizeof(leitor[n].Dia),1,ficheiro);
        fread(&leitor[n].Mes,sizeof(leitor[n].Mes),1,ficheiro);
        fread(&leitor[n].Ano,sizeof(leitor[n].Ano),1,ficheiro);
        fread(leitor[n].Localidade,sizeof(leitor[n].Localidade),1,ficheiro);
        fread(&leitor[n].Contacto,sizeof(leitor[n].Contacto),1,ficheiro);
    }
    for(int n=0; n<nrequisicoes; n++) {
        fread(&requisicao[n].Codigo_leitor,sizeof(requisicao[n].Codigo_leitor),1,ficheiro);
        fread(requisicao[n].ISBN,sizeof(requisicao[n].ISBN),1,ficheiro);
        fread(&requisicao[n].Dia,sizeof(requisicao[n].Dia),1,ficheiro);
        fread(&requisicao[n].Mes,sizeof(requisicao[n].Mes),1,ficheiro);
        fread(&requisicao[n].Ano,sizeof(requisicao[n].Ano),1,ficheiro);
        fread(requisicao[n].Estado_entrega,sizeof(requisicao[n].Estado_entrega),1,ficheiro);
    }
    fclose(ficheiro);
}
void guardar_ficheiro() {
    /*  Descri��o: Gruarda informacoes do programa para um ficheiro
        Entradas: Nao tem
        Saidas: Nao tem
    */
    FILE *ficheiro;//ponteiro para ficheiro
    ficheiro = fopen("Biblioteca.dat", "wb");
    fwrite(&nlivro,sizeof(nlivro),1,ficheiro);
    fwrite(&nleitor,sizeof(nleitor),1,ficheiro);
    fwrite(&nrequisicoes,sizeof(nrequisicoes),1,ficheiro);

    for (int n = 0; n < nlivro; n++) {
        fwrite(livro[n].ISBN,sizeof(livro[n].ISBN),1,ficheiro);
        fwrite(livro[n].Titulo,sizeof(livro[n].Titulo),1,ficheiro);
        fwrite(livro[n].Autor,sizeof(livro[n].Autor),1,ficheiro);
        fwrite(livro[n].Editora,sizeof(livro[n].Editora),1,ficheiro);
        fwrite(livro[n].Estado,sizeof(livro[n].Estado),1,ficheiro);
        if(strcmp(livro[n].Estado, "requisitado") == 0) {
            fwrite(&livro[n].dia_requisitar,sizeof(livro[n].dia_requisitar),1,ficheiro);
            fwrite(&livro[n].mes_requisitar,sizeof(livro[n].mes_requisitar),1,ficheiro);
            fwrite(&livro[n].ano_requisitar,sizeof(livro[n].ano_requisitar),1,ficheiro);
        }
    }
    for (int n = 0; n < nleitor; n++) {
        fwrite(&leitor[n].Codigo_leitor,sizeof(leitor[n].Codigo_leitor),1,ficheiro);
        fwrite(leitor[n].Nome,sizeof(leitor[n].Nome),1,ficheiro);
        fwrite(&leitor[n].Dia,sizeof(leitor[n].Dia),1,ficheiro);
        fwrite(&leitor[n].Mes,sizeof(leitor[n].Mes),1,ficheiro);
        fwrite(&leitor[n].Ano,sizeof(leitor[n].Ano),1,ficheiro);
        fwrite(&leitor[n].Localidade,sizeof(leitor[n].Localidade),1,ficheiro);
        fwrite(leitor[n].Contacto,sizeof(leitor[n].Contacto),1,ficheiro);
    }
    for(int n=0; n<nrequisicoes; n++) {
        fwrite(&requisicao[n].Codigo_leitor,sizeof(requisicao[n].Codigo_leitor),1,ficheiro);
        fwrite(requisicao[n].ISBN,sizeof(requisicao[n].ISBN),1,ficheiro);
        fwrite(&requisicao[n].Dia,sizeof(requisicao[n].Dia),1,ficheiro);
        fwrite(&requisicao[n].Mes,sizeof(requisicao[n].Mes),1,ficheiro);
        fwrite(&requisicao[n].Ano,sizeof(requisicao[n].Ano),1,ficheiro);
        fwrite(requisicao[n].Estado_entrega,sizeof(requisicao[n].Estado_entrega),1,ficheiro);
    }
    fclose(ficheiro);
}
void desligar_programa() {
    /*  Descri��o: Encerra o programa
        Entradas: Nao tem
        Saidas: Nao tem
    */
    char opcao;//Variavel utilizada para obeter a confirmacao se o utilizador deseja encerrar o programa ou nao
    fflush(stdin);
    printf("Tem certeza que deseja sair?\n");
    printf("Digite \"s\" para sair ou qualquer outra tecla para voltar ao menu: ");
    scanf("%c", &opcao);
    switch(opcao) {
    case 's':
    case 'S':
        guardar_ficheiro();
        printf("\nO programa foi encerrado!\n");
        exit(0);//comando que encerra o programa
        break;
    default:
        system("cls");//Limpa a tela
        exibir_menu();
    }
}







