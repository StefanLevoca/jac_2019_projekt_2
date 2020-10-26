#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "program.h"

// prototypy funkcii
void addSt();

void updateSt();

void deleteSt();

void openDB();

void saveDB();

void quit();

void error(int action);

void start_clean_up();

// Iba cast main.c ma dostavat data od pouzivatela, program.c ich ma spracuvat

/**
 * Táto časť má obsahovať konzolové prostredie pomocou, ktorého bude používateľ aktívne vykonávať operácie z program.h
 * @return 0 standardny koniec programu, 1 chybovy koniec programu
 */
int main() {
    printf("Vitajte v malej databazovej verzii evidencie studentov 1.9.7.3. \n");

    char action = 0;
    // cakame na akciu pouzivatela, kym neukonci aplikaciu cez akciu q
    while (TRUE) {
        // zistime akciu
        while (scanf("%c", &action) != EOF) {
            // a podla akcie spustame jednotlive funkcie
            switch (action) {
                case 'h':
                    print_help();
                    // ;
                    // char *output1 = sprint_help();

                    // int rows1 = 10, columns1 = 40;
                    // for (int i = 0; i < rows1; i++) {
                    // for (int j = 0; j < columns1; ++j) {
                    // printf("%c ", *(output1 + i * columns1 + j));
                    // }
                    // printf("\n");
                    // }

                    // free(output1);
                    break;
                case 'p':
                    print_table();
                    // ;
                    // char *output2 = sprint_table();

                    // int rows2 = (2 + get_database_size()), columns2 = 80;
                    // for (int i = 0; i < rows2; i++) {
                    // for (int j = 0; j < columns2; ++j) {
                    // printf("%c ", *(output2 + i * columns2 + j));
                    // }
                    // printf("\n");
                    // }

                    // free(output2);
                    break;
                case 'c':
                    printf("Velkost databazy je %d \n", get_database_size());
                    break;
                case 'a':
                    addSt();
                    break;
                case 'u':
                    updateSt();
                    break;
                case 'd':
                    deleteSt();
                    break;
                case 'o':
                    openDB();
                    break;
                case 's':
                    saveDB();
                    break;
                case 'q':
                    quit();
                    // standardny koniec programu
                    return 0;
                    // default:
                    // error(action);
            }
        }
        // nastala chyba, dostali sme EOF napriklad vstup do
        // programu nebol z konzoly, ale bol presmerovany zo suboru
        // cez ruru a precitali sme vsetko z tohto suboru, resp. nastala chyba pri citani
        return 1;
    }
}

/**
 * Pomocna metoda pre pridanie studenta
 */
void addSt() {
    Student *student = init_student();

    printf("Zadajte meno []: \n");
    char meno_new[20];
    if (scanf("%s", meno_new) == EOF) {
        fprintf(stderr, "Chyba nacitania mena \n");
        return;
    }

    printf("Zadajte priezvisko []: \n");
    char priezvisko_new[20];
    if (scanf("%s", priezvisko_new) == EOF) {
        fprintf(stderr, "Chyba nacitania priezviska \n");
        return;
    }

    printf("Zadajte studijnu skupinu []: \n");
    char studijna_skupina_new[8];
    if (scanf("%s", studijna_skupina_new) == EOF) {
        fprintf(stderr, "Chyba nacitania studijnej skupiny \n");
        return;
    }

    printf("Zadajte body[0]: \n");
    int pocet_bodov_new;
    if (scanf("%d", &pocet_bodov_new) == EOF) {
        fprintf(stderr, "Chyba nacitania poctu bodov \n");
        return;
    }

    // nastavenie hodnot pre noveho studenta
    // char *strcpy(char *dest, const char *src) copies the string pointed to, by src to dest
    strcpy(student->meno, meno_new);
    strcpy(student->priezvisko, priezvisko_new);
    strcpy(student->studijna_skupina, studijna_skupina_new);
    student->pocet_bodov = pocet_bodov_new;

    int accepted;
    accepted = add_student(student);
    if (accepted == 0) {
        printf("Pridanie studenta uspesne \n");
    } else {
        printf("Pridanie studenta neuspesne \n");
    }
}

/**
 * Pomocna metoda pre aktualizaciu studenta
 */
void updateSt() {
    printf("Zadajte ID studenta: \n");
    int identifier;
    if (scanf("%d", &identifier) == EOF) {
        fprintf(stderr, "Chyba nacitania ID studenta \n");
        return;
    }

    if (identifier > get_database_size()) {
        fprintf(stderr, "Student so zadanym ID %d neexistuje v databaze \n", identifier);
        return;

    } else {
        Student *student = get_student(identifier);

        int accepted;
        accepted = update_student(identifier, student);
        if (accepted == 0) {
            printf("Update studenta uspesny \n");
        } else {
            printf("Update studenta neuspesny \n");
        }
    }
}

/**
 * Pomocna metoda pre zmazanie studenta
 */
void deleteSt() {
    printf("Zadajte ID studenta: \n");
    int identifier;
    if (scanf("%d", &identifier) == EOF) {
        fprintf(stderr, "Chyba nacitania ID studenta \n");
        return;
    }
    int accepted;
    accepted = delete_student(identifier);

    if (accepted == 0) {
        printf("Zmazanie studenta uspesne \n");
    } else {
        printf("Zmazanie studenta neuspesne \n");
    }
}

/**
 * Pomocna metoda pre nacitanie dat z databazy
 */
void openDB() {
    open_from_file(FILE_DB);
}

/**
 * Pomocna metoda pre ulozenie dat do databazy
 */
void saveDB() {
    save_to_file(FILE_DB);
}

/**
 * Ukoncenie aplikacie
 */
void quit() {
    start_clean_up();
    printf("Dakujem za pouzivanie \n");
}

/**
 * Nedefinovana operacia
 *
 * @param action akcia pouzivatela
 */
void error(int action) {
    printf("Pozadovana akcia %c je nedefinovana !!!  \n", (char) action);
    print_help();
}