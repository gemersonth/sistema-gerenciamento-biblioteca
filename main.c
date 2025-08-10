#include <stdio.h>
#include <string.h>

#define PASSWORD_ADMIN "admin123"
#define PASSWORD_BUFFER 100
#define MAX_BOOKS 10


typedef struct {
    char title[50];
    char landlord[50];
    int remaining_days;
    int leased;
    float fine;
} Book;


void clear_buffer(void);
void add_book(Book *bookVector, int *bookCount);
void remove_book(Book *bookVector, int *bookCount);
void list_book(Book *bookVector, int *bookCount);
void allocate_book(Book *bookVector, int *bookCount);
void return_book(Book *bookVector, int *bookCount);
void increase_term(Book *bookVector, int *bookCount);
void pay(Book *bookVector, int *bookCount);
int question(void);

int main() {

    int exit = 0;
    int option;

    Book Books[MAX_BOOKS];
    int bookCount = 0;

    do {
    
        printf("\n---------------MENU---------------\n");
        printf("1. ADICIONAR LIVRO\n");
        printf("2. REMOVER LIVRO\n");
        printf("3. LISTAR LIVROS\n");
        printf("4. ALOCAR LIVRO\n");
        printf("5. DEVOLVER LIVRO\n");
        printf("6. AUMENTAR PRAZO\n");
        printf("7. PAGAR\n");
        printf("8. SAIR\n");
        printf("----------------------------------\n");
        scanf("%d", &option);
        clear_buffer();

        if ( option == 8 ) {
            printf("\n SAINDO... \n");
            exit = 1;
        } 
        
        else {

            switch ( option ) {

                case 1:
                    add_book(Books, &bookCount);
                    break;
                
                case 2:
                    remove_book(Books, &bookCount);
                    break;
                
                case 3:
                    list_book(Books, &bookCount);
                    break;
                
                case 4:
                    allocate_book(Books, &bookCount);
                    break;

                case 5:
                    return_book(Books, &bookCount);
                    break;
                case 6:
                    increase_term(Books, &bookCount);
                    break;
                case 7:
                    pay(Books, &bookCount);
                    break;
                
                default:
                    printf("\n OPÇÃO INVÁLIDA \n");

            }

        }

    } while( exit == 0 );

    return 0;
}

void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void add_book(Book *bookVector, int *bookCount) {
    printf("\nDIGITE A SENHA ADMIN: ");
    char inputPassword[PASSWORD_BUFFER];
    fgets(inputPassword, PASSWORD_BUFFER, stdin);

    for ( int i = 0; inputPassword[i] != '\0'; i++ ) {
        if ( inputPassword[i] == '\n' ) {
            inputPassword[i] = '\0';
        }
    }

    if ( strcmp(inputPassword, PASSWORD_ADMIN) == 0 ) {
        printf("ACESSO LIBERADO!\n");
        if ( *bookCount < MAX_BOOKS ) {

            printf("DIGITE O TÍTULO DO LIVRO: ");
            int bufferBookTitle = sizeof(bookVector[*bookCount].title);
            char bookTitle[bufferBookTitle];
            fgets(bookTitle, bufferBookTitle, stdin);
            
            for ( int i = 0; i < sizeof(bookTitle); i++ ) {
                if ( bookTitle[i] == '\n' ) {
                    bookTitle[i] = '\0';
                    break;
                }
            }

            if ( question() == 0 ) {
                return;
            }

            strcpy(bookVector[*bookCount].title, bookTitle);
            (*bookCount) ++;
        } 
        
        else {
            printf("BIBLIOTECA ESTÁ CHEIA!");
            return;
        }
    
    } 

    else {
        printf("ACESSO NEGADO!");
    }
    
}

void remove_book(Book *bookVector, int *bookCount) {
    if ( *bookCount == 0 ) {
        printf("NENHUM LIVRO FOI ADICIONADO A BIBLIOTECA!\n");
        return;
    }

    printf("\nDIGITE A SENHA ADMIN: ");
    char inputPassword[PASSWORD_BUFFER];
    fgets(inputPassword, PASSWORD_BUFFER, stdin);

    for ( int i = 0; inputPassword[i] != '\0'; i++ ) {
        if ( inputPassword[i] == '\n' ) {
            inputPassword[i] = '\0';
        }
    }

    if ( strcmp(inputPassword, PASSWORD_ADMIN) == 0 ) {
        printf("ACESSO LIBERADO!\n");

        list_book(bookVector, bookCount);

        printf("DIGITE O NÚMERO REFERENTE AO LIVRO: ");
        int inputRefBook;
        scanf("%d", &inputRefBook);
        if ( inputRefBook <= 0 || inputRefBook > *bookCount ) {
            printf("ERRO, DIGITE UM VALOR REFERENTE AO LIVRO!\n");
            return;
        }

        int indexToRemove = inputRefBook - 1;

        printf("REMOVENDO O LIVRO '%s'...\n", bookVector[indexToRemove].title);
        for (int i = indexToRemove; i < *bookCount - 1; i++) {
            bookVector[i] = bookVector[i + 1];
        }
        
        (*bookCount)--;

        printf("LIVRO REMOVIDO COM SUCESSO!\n");

    }

    else {
        printf("ACESSO NEGADO!\n");
    }

}

void list_book(Book *bookVector, int *bookCount) {
    printf("\n============================== LIVROS ==============================\n");
    for ( int i = 0; i < *bookCount; i++ ) {
        printf("%d. %s  %s\n", i + 1, bookVector[i].title, bookVector[i].leased == 1 ? "(LOCADO)" : "(NÃO LOCADO)");
    }
    printf("\n====================================================================\n");
}

void allocate_book(Book *bookVector, int *bookCount) {

    if ( *bookCount == 0 ) {
        printf("NENHUM LIVRO FOI ADICIONADO A BIBLIOTECA\n");
        return;
    }
    
    list_book(bookVector, bookCount);

    printf("DIGITE O NÚMERO CORRESPONDENTE AO LIVRO: ");
    int inputNumRefBook;
    scanf("%d", &inputNumRefBook);

    if ( inputNumRefBook <= 0 || inputNumRefBook > *bookCount ) {
            printf("ERRO, DIGITE O VALOR REFERENTE AO LIVRO!\n");
            return;    
    }

    int index = inputNumRefBook - 1;

    if ( bookVector[index].leased == 1 ) {
        printf("\nLIVRO INDISPONÍVEL!\n");
        return;
    } 
    
    printf("LIVRO SELECIONADO: %s\n\n", bookVector[index].title);

    printf("DIGITE SEU NOME: ");
    clear_buffer();
    char inputName[sizeof(bookVector[index].landlord)];
    fgets(inputName, sizeof(inputName), stdin);

    for ( int i = 0; i < *bookCount; i++ ) {
        if ( strcmp(bookVector[i].landlord, inputName) == 0 ) {
            printf("VOCÊ JÁ TEM 1 LIVRO LOCADO EM SEU NOME!");
            return;
        }
    }

    printf("DIGITE O NÚMERO DE DIAS PARA DEVOLUÇÃO: ");
    int inputNumDays;
    scanf("%d", &inputNumDays);
    clear_buffer();

    if ( question() == 0 ) {
        return;
    }

    strcpy(bookVector[index].landlord, inputName);
    bookVector[index].remaining_days = inputNumDays;
    bookVector[index].leased = 1;
    bookVector[index].fine = 0;

    printf("LIVRO LOCADO COM SUCESSO!\n");

}

void return_book(Book *bookVector, int *bookCount) {

    if ( *bookCount == 0 ) {
        printf("NÃO EXISTE LIVROS NA BIBLIOTECA!\n");
        return;
    }

    else {

        printf("DIGITE SEU NOME: ");
        char inputName[sizeof(bookVector[0].landlord)];
        fgets(inputName, sizeof(inputName), stdin);

        for ( int i = 0; i <= *bookCount; i++ ) {
            if ( strcmp(bookVector[i].landlord, inputName) == 0 ) {

                printf("DIAS QUE FICOU COM O LIVRO: ");
                int inputAmountDays;
                scanf("%d", &inputAmountDays);

                if ( inputAmountDays > bookVector[i].remaining_days ) {
                    const float fineRate = 0.5;
                    bookVector[i].fine += (inputAmountDays - bookVector[i].remaining_days) * fineRate;
                    printf("NÃO FOI POSSÍVEL DEVOLVER O LIVRO, VOCÊ ULTRAPASSOU O PRAZO DE %d DIASj\n", bookVector[i].remaining_days);
                    printf("VOCÊ TEM UMA MULTA DE R$%.2f A PAGAR!\n", bookVector[i].fine);
                    return;
                }

                else {
                    strcpy(bookVector[i].landlord, "");
                    bookVector[i].remaining_days = 0;
                    bookVector[i].leased = 0;
                    printf("LIVRO DEVOLVIDO COM SUCESSO!");
                    return;
                }

            }
        }

        printf("NENHUM LIVRO FOI ENCONTRADO EM SEU NOME!\n");

    }

}

void increase_term(Book *bookVector, int *bookCount) {
    if ( *bookCount <= 0 ) {
        printf("NENHUM LIVRO FOI ADICIONADO A BIBLIOTECA!");
        return;
    } 

    printf("DIGITE SEU NOME: ");
    char inputName[sizeof(bookVector[0].landlord)];
    fgets(inputName, sizeof(inputName), stdin);

    for ( int i = 0; i < *bookCount; i++ ) {
        if ( strcmp(bookVector[i].landlord, inputName) == 0 ) {

            if ( bookVector[i].fine > 0 ) {
                printf("NÃO FOI POSSÍVEL AUMENTAR O PRAZO, VOCÊ TEM UMA MULTA DE R$%.2f A PAGAR!\n", bookVector[i].fine);
                return;
            }

            printf("DIGITE A QUANTIDADE DE DIAS QUE DESEJA INCREMENTAR: ");
            int inputDays;
            scanf("%d", &inputDays);

            bookVector[i].remaining_days += inputDays;
            printf("DIAS RESTANTES: %d\n", bookVector[i].remaining_days);
            return;
        }

    printf("NENHUM LIVRO FOI ENCONTRADO EM SEU NOME!\n");

    }
}

void pay(Book *bookVector, int *bookCount) {
    if ( *bookCount == 0 ) {
        printf("NENHUM LIVRO FOI ADICIONADO A BIBLIOTECA!\n");
        return;
    }

    printf("DIGITE SEU NOME: ");
    char inputName[sizeof(bookVector[0].landlord)];
    fgets(inputName, sizeof(inputName), stdin);

    for ( int i = 0; i <= *bookCount; i++ ) {
        if ( strcmp(bookVector[i].landlord, inputName) == 0 ) {
            if ( bookVector[i].fine > 0 ) {
                bookVector[i].fine += 0;
                printf("SUA MULTA DE %.2f FOI PAGO!\n", bookVector[i].fine);
                return;
            }
            else {
                printf("VOCÊ NÃO TEM MULTAS!");
                return;
            }
        }
    }
    printf("NÃO TEM LIVROS LOCADOS EM SEU NOME!\n");
}

int question() {
    while (1) {
        printf("DESEJA CONTINUAR? S/N ");
        char response;
        scanf("%c", &response);

        if ( response == 's' || response == 'S' || response == '\n' ) {
            return 1;
        } else {
            return 0;
        }
    }
}
