//projeto

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <conio.h>
#include <windows.h>


#define NLIVROS 100
#define NLEITORES 100


void tempo();
void menu();
void registar_livro();
void registar_leitor();
void requisitar_livro();
void devolver_livro();
void listagens();
void carregar_ficheiro();
void guardar_ficheiro();
void sair();

typedef struct {
    long int ISBN;    /*ISBN tem que ser (long long int) mas esta a dar warning*/
    char Titulo[NLIVROS];
    char Autor[NLIVROS];
    char Editora[NLIVROS];
    char Estado[NLIVROS];
}livro_t;
livro_t livro[NLIVROS];

typedef struct {
    int Codigo_leitor;
    char Nome[NLEITORES];
    int Dia;
    int Mes;
    int Ano;
    char Localidade[NLEITORES];
    int Contacto;
}leitor_t;
leitor_t leitor[NLEITORES];

int nlivro=0;
int nleitor=0;

int main(){
    carregar_ficheiro();
    menu();

return 0;
}
void menu(){
    int num=0;

        system("cls");

        printf("\t-- Gestao de Requisicoes de uma Biblioteca --\n\n");
        printf("Total de Livros:%d \t\t\t Total de Leitores:%d \n",nlivro,nleitor);
        printf("Total de Requisicoes ativas: \n\n");
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

    scanf("%ld", &livro[nlivro].ISBN);
    printf("O ISBN e %ld \n\n", livro[nlivro].ISBN);

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
    int leitor_verificar;
    printf("Digite o seu codigo de leitor!\n");
    fflush(stdin);
    scanf("%d", &leitor_verificar);
    for(int n=0; n<nleitor;n++){
        if(leitor[n].Codigo_leitor == leitor_verificar){
            printf("Codigo de Leitor valido!\n");
            printf("Digite o Titulo do livro!\n");
            char titulo_livro[NLIVROS];
            fflush(stdin);
            gets(titulo_livro);
            for(int n=0; n<nlivro; n++){
                if(strcmp(titulo_livro, livro[n].Titulo) == 0){//Permite comparar alfabeticamente duas strings. Devolve 0 - se as duas strings forem alfabeticamente iguais
                    printf("Titulo existe!\n");
                    char estado_disponivel[NLIVROS]= "disponivel";
                    if(strcmp(livro[n].Estado, estado_disponivel) == 0){
                        printf("Esta disponivel\n");
                        printf("Insira a data da requisicao!\n");
                        fflush(stdin);
                        int dia_requisitar;
                        int mes_requisitar;
                        int ano_requisitar;

                        printf("Dia:\n");
                        scanf("%d", &dia_requisitar);
                        fflush(stdin);
                        printf("Mes:\n");
                        scanf("%d", &mes_requisitar);
                        fflush(stdin);
                        printf("Ano:\n");
                        scanf("%d", &ano_requisitar);
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
    long int isbn;
    printf("Insira o ISBN do livro!\n");
    scanf("%ld", &isbn);

    for(int n=0; n<nlivro;n++){
        if(isbn == livro[n].ISBN){
            printf("Livro devolvido!\n");
            strcpy(livro[n].Estado, "disponivel");
            menu();
        printf("Nao existe nenhum livro este ISBN!\n");
        menu();

        }
    }
 }
void listagens(){

    system("cls");

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
                system("cls");
                for (int n = 0; n < nlivro; n++) {
                    printf("\nLivro%d:\n\n", n + 1);
                    printf("ISBN:\t\t %ld\n", livro[n].ISBN);
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
                system("cls");
                for (int n = 0; n < nleitor; n++) {
                    printf("\nLeitor %d: \n\n", n + 1);
                    printf("Codigo_leitor:\t\t %d\n", leitor[n].Codigo_leitor);
                    printf("Nome:\t\t\t %s\n", leitor[n].Nome);
                    printf("Data de Nascimento:\t %d-%d-%d\n", leitor[n].Dia,leitor[n].Mes,leitor[n].Ano);
                    printf("Localidade:\t\t %s\n", leitor[n].Localidade);
                    printf("Contacto:\t\t %d\n\n", leitor[n].Contacto);
                }
                printf("\nPressione uma tecla para continuar!\n\n");
                getch();
                listagens();
            break;
            case 3:
                listagens();
            break;
            case 4:
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
        FILE *ficheiro;
        ficheiro = fopen("Biblioteca.txt", "r");
        fscanf(ficheiro, "\nNumero de Livros: %d\n",&nlivro);
        fscanf(ficheiro, "\nNumero de Leitores: %d\n\n", &nleitor);
    for (int n = 0; n < nlivro; n++) {
        int n1=n+1;
        fscanf(ficheiro, "\nLivro%d:\n\n", &n1);
        fscanf(ficheiro, "ISBN: %ld\n", &livro[n].ISBN);
        fscanf(ficheiro, "Titulo: %s\n", livro[n].Titulo);
        fscanf(ficheiro, "Autor: %s\n", livro[n].Autor);
        fscanf(ficheiro, "Editora: %s\n", livro[n].Editora);
        fscanf(ficheiro, "Estado: %s\n", livro[n].Estado);
    }
    for (int n = 0; n < nleitor; n++) {
        int n1=n+1;
        fscanf(ficheiro, "\nLeitor %d: ", &n1);
        fscanf(ficheiro, "Codigo_leitor: %d\n", &leitor[n].Codigo_leitor);
        fscanf(ficheiro, "Nome: %s\n", leitor[n].Nome);
        fscanf(ficheiro, "Data de Nascimento: %d-%d-%d\n", &leitor[n].Dia,&leitor[n].Mes,&leitor[n].Ano);
        fscanf(ficheiro, "Localidade: %s\n", leitor[n].Localidade);
        fscanf(ficheiro, "Contacto: %d\n", &leitor[n].Contacto);
    }
    fclose(ficheiro);
}
void guardar_ficheiro(){
            FILE *ficheiro;
            ficheiro = fopen("Biblioteca.txt", "w");
            fprintf(ficheiro, "\nNumero de Livros: %d\n",nlivro);
            fprintf(ficheiro, "\nNumero de Leitores: %d\n\n", nleitor);
        for (int n = 0; n < nlivro; n++) {
            fprintf(ficheiro, "\nLivro%d:\n\n", n + 1);
            fprintf(ficheiro, "ISBN: %ld\n", livro[n].ISBN);
            fprintf(ficheiro, "Titulo: %s\n", livro[n].Titulo);
            fprintf(ficheiro, "Autor: %s\n", livro[n].Autor);
            fprintf(ficheiro, "Editora: %s\n", livro[n].Editora);
            fprintf(ficheiro, "Estado: %s\n", livro[n].Estado);
        }
        for (int n = 0; n < nleitor; n++) {
            fprintf(ficheiro, "\nLeitor %d: \n\n", n + 1);
            fprintf(ficheiro, "Codigo_leitor: %d\n", leitor[n].Codigo_leitor);
            fprintf(ficheiro, "Nome: %s\n", leitor[n].Nome);
            fprintf(ficheiro, "Data de Nascimento: %d-%d-%d\n", leitor[n].Dia,leitor[n].Mes,leitor[n].Ano);
            fprintf(ficheiro, "Localidade: %s\n", leitor[n].Localidade);
            fprintf(ficheiro, "Contacto: %d\n", leitor[n].Contacto);
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
void tempo(){
    time_t tempo;
    struct tm *timeinfo;
    char c;
    system("cls");

    while(1){
        time(&tempo);
        timeinfo = localtime(&tempo);
        system("cls");

        printf("Data %02d/%02d/%02d \nHoras: %02d:%02d:%02d \n", timeinfo->tm_mday, timeinfo->tm_mon+1, timeinfo->tm_year+1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
        if(kbhit()){
            c=getch();
            if(c==27){
                printf("\nTecla Escape priomida --> Fim de programa\n");
                menu();
            }else{
                printf("\nTecla primida, mas sem efeito %c \n\n", c);
                Sleep(1000);
            }
        }
    }
}
void afixa_time(){
    time_t tempo;
    struct tm *timeinfo;
    time(&tempo);
    timeinfo=localtime(&tempo);
    printf("Data %02d/%02d/%02d \nHoras: %02d/%02d/%02d", timeinfo->tm_mday, timeinfo->tm_mon+1, timeinfo->tm_year+1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}

