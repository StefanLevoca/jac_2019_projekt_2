#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "program.h"

// spajany zoznam studentov - https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm
struct Node {
    Student *student;
    struct Node *next;
};

// ukazovatel na prvy prvok v spajanom zozname
struct Node *head = NULL;

/**
 * C substring function: It returns a pointer to the substring (https://www.programmingsimplified.com/c/source-code/c-substring)
 *
 * @param string retazec znakov
 * @param position pozicia zaciatku
 * @param length pozadovana dlzka podretazca
 * @return a pointer to the substring
 */
char *substring(char *string, int position, int length) {
    char *pointer;
    int c;

    pointer = malloc(length + 1);

    if (pointer == NULL) {
        printf("Unable to allocate memory.\n");
        exit(1);
    }

    for (c = 0; c < length; c++) {
        *(pointer + c) = *(string + position - 1);
        string++;
    }

    *(pointer + c) = '\0';

    return pointer;
}

/* Táto časť má obsahovať rozhranie popísané hlavičkovým súborom program.h */

/**
 * Metoda pre vypis moznosti akcii tejto aplikacie na konzolu
 */
void print_help() {
    printf("Zoznam povolenych akcii: \n"
           "- h - zobrazi tieto informacie \n"
           "- p - vypis z databazy na konzolu \n"
           "- c - vypis velkosti databazy \n"
           "- a - vytvorit a pridat studenta \n"
           "- u - upravit studenta \n"
           "- d - zmazat studenta \n"
           "- o - otvorit databazu zo suboru \n"
           "- s - ulozit databazu do suboru \n"
           "- q - ukoncit program \n");
}

/**
 * Metoda, ktora nevypisuje nič priamo na konzolu ale,
 * text vrátia ako návratovú hodnotu volania funkcie
 *
 * @return text vystupu
 */
char *sprint_help() {
    // 10 : pocet riadkov vo vypise, 35 * sizeof(char) : 33 - maximalny pocet znakov z riadkov vo vypise,
    // jeden /0 - koniec pola znakov a jeden \n

    // https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
    int rows = 10, columns = 40;
    char *buffer = (char *) malloc(rows * columns * sizeof(char));

    int i = -1;
    sprintf((buffer + ++i), "%33s\n", "Zoznam povolenych akcii:");
    sprintf((buffer + ++i), "%33s\n", "- h - zobrazi tieto informacie");
    sprintf((buffer + ++i), "%33s\n", "- p - vypis z databazy na konzolu");
    sprintf((buffer + ++i), "%33s\n", "- c - vypis velkosti databazy");
    sprintf((buffer + ++i), "%33s\n", "- a - vytvorit a pridat studenta");
    sprintf((buffer + ++i), "%33s\n", "- u - upravit studenta");
    sprintf((buffer + ++i), "%33s\n", "- d - zmazat studenta");
    sprintf((buffer + ++i), "%33s\n", "- o - otvorit databazu zo suboru");
    sprintf((buffer + ++i), "%33s\n", "- s - ulozit databazu do suboru");
    sprintf((buffer + ++i), "%33s\n", "- q - ukoncit program");

    return buffer;
}

/**
 * Vypis obsahu databazy na konzolu (display the list)
 */
void print_table() {
    printf("| %3s | %20s | %20s | %8s | %4s |\n", "ID", "Meno", "Priezvisko", "Skupina", "Body");
    printf("| %3s | %20s | %20s | %8s | %4s |\n", "---", "--------------------", "--------------------", "--------",
           "----");

    struct Node *ptr = (struct Node *) head;
    int ID = 0;

    //start from the beginning
    while (ptr != NULL) {
        printf("| %3d | %20s | %20s | %8s | %4d |\n", ++ID, ptr->student->meno, ptr->student->priezvisko,
               ptr->student->studijna_skupina,
               ptr->student->pocet_bodov);
        ptr = ptr->next;
    }
}

/**
 * Metoda, ktora nevypisuje nič priamo na konzolu ale,
 * text vrátia ako návratovú hodnotu volania funkcie
 *
 * @return text vystupu
 */
char *sprint_table() {
    // 2 + get_database_size() : hlavicka tabulky a zaznamy v tabulke, 73 * sizeof(char) :
    // 71 pocet znakov vo vypise jedneho riadku, jeden /0 - koniec pola znakov a jeden \n

    // https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
    int rows = (2 + get_database_size()), columns = 80;
    char *buffer = (char *) malloc(rows * columns * sizeof(char));

    int i = -1;
    sprintf((buffer + ++i), "| %3s | %20s | %20s | %8s | %4s |\n", "ID", "Meno", "Priezvisko", "Skupina", "Body");
    sprintf((buffer + ++i), "| %3s | %20s | %20s | %8s | %4s |\n", "---", "--------------------",
            "--------------------",
            "--------",
            "----");

    struct Node *ptr = (struct Node *) head;
    int ID = 0;

    //start from the beginning
    while (ptr != NULL) {
        sprintf((buffer + ++i), "| %3d | %20s | %20s | %8s | %4d |\n", ++ID, ptr->student->meno,
                ptr->student->priezvisko,
                ptr->student->studijna_skupina,
                ptr->student->pocet_bodov);
        ptr = ptr->next;
    }

    return buffer;
}

/**
 * Metoda pre ziskanie noveho prazdneho studenta, v ramke
 *
 * @return referencia na strukturu Student
 */
Student *init_student() {
    Student *student;
    student = (Student *) malloc(sizeof(Student));

    if (student == NULL) {
        printf("Memory not allocated.\n");
        exit(EXIT_FAILURE);
    }
    // printf("Memory successfully allocated using calloc.\n");
    return student;
}

/**
 * Metoda pre pridanie studenta na prvu poziciu (insert link at the first location)
 *
 * @param student referencia na studenta
 * @return 0 - podarilo sa pridanie studenta do databazy; 1 nepodarilo sa pridanie studenta do databazy
 */
int add_student(Student *student) {

    // create a link
    struct Node *link = (struct Node *) malloc(sizeof(struct Node));

    if (link == NULL) {
        printf("Memory not allocated.\n");
        exit(EXIT_FAILURE);
    }
    //  printf("Memory successfully allocated using calloc.\n");

    strcpy(link->student->meno, student->meno);
    strcpy(link->student->priezvisko, student->priezvisko);
    strcpy(link->student->studijna_skupina, student->studijna_skupina);
    link->student->pocet_bodov = student->pocet_bodov;

    //point it to old first Node
    link->next = head;

    //point first to new first Node
    head = link;

    return 0;
}

/**
 * Metoda na ziskanie studenta z databazy (find a link with given key)
 *
 * @param identifier ID studenta
 * @return referencia na studenta
 */
Student *get_student(int identifier) {

    //start from the first link
    struct Node *current = head;

    //if list is empty
    if (head == NULL) {
        return current->student = NULL;
    }

    //navigate through list
    int key = 1;
    while (key != identifier) {

        //if it is last Node
        if (current->next == NULL) {
            return current->student = NULL;

        } else {
            //go to next link
            current = current->next;
            ++key;
        }
    }

    //if data found, return the current Link
    return current->student;
}

/**
 * Metoda pre aktualizaciu studenta
 *
 * @param identifier ID studenta
 * @param student referencia na studenta
 * @return 0 - podaril sa update studenta v databaze; 1 nepodaril sa update studenta v databaze
 */
int update_student(int identifier, Student *student) {

    printf("Zadajte meno []: \n");
    char meno_update[20];
    if (scanf("%s", meno_update) == EOF) {
        fprintf(stderr, "Chyba nacitania mena \n");
        return 1;
    }

    printf("Zadajte priezvisko []: \n");
    char priezvisko_update[20];
    if (scanf("%s", priezvisko_update) == EOF) {
        fprintf(stderr, "Chyba nacitania priezviska \n");
        return 1;
    }

    printf("Zadajte studijnu skupinu []: \n");
    char studijna_skupina_update[8];
    if (scanf("%s", studijna_skupina_update) == EOF) {
        fprintf(stderr, "Chyba nacitania studijnej skupiny \n");
        return 1;
    }

    printf("Zadajte body[0]: \n");
    int pocet_bodov_update;
    if (scanf("%d", &pocet_bodov_update) == EOF) {
        fprintf(stderr, "Chyba nacitania poctu bodov \n");
        return 1;
    }

    // update hodnot pre daneho studenta
    strcpy(student->meno, meno_update);
    strcpy(student->priezvisko, priezvisko_update);
    strcpy(student->studijna_skupina, studijna_skupina_update);
    student->pocet_bodov = pocet_bodov_update;

    // studenta zmazeme zo zoznamu
    delete_student(identifier);

    // a pridame aktualizovaneho studenta do zoznamu
    add_student(student);

    return 0;
}

/**
 * Metoda pre vymazanie studenta z databazy (delete a link with given key)
 * @param identifier Id studenta
 * @return 0 - podaril sa vymaz studenta z databazy; 1 nepodaril sa vymaz studenta z databazy
 */
int delete_student(int identifier) {
    if (identifier > get_database_size()) {
        fprintf(stderr, "Student s danym ID %d neexistuje v databaze", identifier);
        return 1;

    } else {
        //start from the first link
        struct Node *current = head;
        struct Node *previous = NULL;

        // tu ulozim to co budem chciet na konci uvolnit z pamate, cize alokovanu pamat na nepotrebneho studenta
        struct Node *to_free = NULL;

        //if list is empty
        if (head == NULL) {
            return 1;
        }

        //navigate through list
        int key = 1;
        while (key != identifier) {

            //if it is last Node
            if (current->next == NULL) {
                return 1;

            } else {
                //store reference to current link
                previous = current;

                //move to next link
                current = current->next;
                ++key;
            }
        }

        // found a match, update the link
        if (current == head) {

            // na uvolnenie z pamate
            to_free = current;

            // change first to point to next link
            head = head->next;

            // uvolnenie pamate z RAM
            free(to_free);

        } else {

            // na uvolnenie z pamate
            to_free = current;

            //bypass the current link
            previous->next = current->next;

            // uvolnenie pamate z RAM
            free(to_free);
        }
    }

    return 0;
}

/**
 * Metoda oznamujuca doplnkove informacie o databaze
 *
 * @return pocet zaznamov v databaze
 */
int get_database_size() {
    int length = 0;
    struct Node *current;

    for (current = head; current != NULL; current = current->next) {
        length++;
    }

    return length;
}

/**
 * Metoda sluziaca na ulozenie databazy na disk
 *
 * @param file_name meno suboru kde sa ulozi databaza zaznamov
 * @return 0 - podarilo sa ulozenie databazy do suboru; 1 nepodarilo sa ulozenie databazy do suboru
 */
int save_to_file(char *file_name) {
    FILE *file_resource;

    if ((file_resource = fopen(file_name, "w")) == NULL) {
        fprintf(stderr, "Chyba pri otvarani suboru");
        exit(EXIT_FAILURE);

    } else {
        fprintf(file_resource, "| %3s | %20s | %20s | %8s | %4s |\n", "ID", "Meno", "Priezvisko", "Skupina",
                "Body");
        fprintf(file_resource, "| %3s | %20s | %20s | %8s | %4s |\n", "---", "--------------------",
                "--------------------", "--------",
                "----");

        struct Node *ptr = (struct Node *) head;
        int ID = 0;

        //start from the beginning
        while (ptr != NULL) {
            fprintf(file_resource, "| %3d | %20s | %20s | %8s | %4d |\n", ++ID, ptr->student->meno,
                    ptr->student->priezvisko,
                    ptr->student->studijna_skupina,
                    ptr->student->pocet_bodov);

            ptr = ptr->next;
        }

        printf("Ulozene \n");
        fclose(file_resource);
    }
    return 0;
}

/**
 * Metoda na zistenie poctu zaznamov v subore kvoli alokacii pola (https://www.tutorialspoint.com/c-program-to-count-the-number-of-lines-in-a-file)
 *
 * @return -1 ak nastala chyba, inak pocet zaznamov v subore
 */
int count_file_lines(char *file_name) {
    FILE *fp;
    char ch;
    int lines_count = 0;

    //open file in read more
    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("File \"%s\" does not exist!!! \n", file_name);
        return -1;
    }

    //read character by character and check for new line
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            ++lines_count;
        }
    }

    //close the file
    fclose(fp);

    //print number of lines
    printf("Total number of lines are: %d \n", lines_count);
    return lines_count;
}

/**
 * Metoda sluziaca na nacitanie databazy z disku
 *
 * @param file_name meno suboru, z ktoreho sa databaza zaznamov nacita
 * @return 0 - podarilo sa nacitanie databazy zo suboru; 1 nepodarilo sa nacitanie databazy zo suboru
 */
int open_from_file(char *file_name) {
    int records;

    if ((records = count_file_lines(file_name)) == -1) {
        return 1;
    }

    FILE *file_resource;

    int ID = 0;
    int rows = records, columns = 80;
    char *lines = (char *) malloc(rows * columns * sizeof(char));

    // prve 2 riadky v subore budu hlavicka tabulky
    int startReading = 0;

    if ((file_resource = fopen(file_name, "r")) == NULL) {
        fprintf(stderr, "Chyba pri otvarani suboru \n");
        exit(EXIT_FAILURE);
    }

    // 75 : 71 pocet znakov vo vypise jedneho riadku,
    // jeden /0 - koniec pola znakov a jeden \n, dalsi jeden /0 pridava funkcia
    // fgets(char* riadok, int maxriadok, FILE* fu) a cita prave
    // maxriadok - 1 znakov zo suboru, na ktory ukazuje fu

    // kym mame zaznamy v subore
    for (int i = 0; i < rows; ++i) {

        // char *fgets(char *str, int n, FILE *stream) reads a line from the specified stream
        // and stores it into the string pointed to by str. It stops when either (n-1) characters
        // are read, the newline character is read, or the end-of-file is reached, whichever comes first.
        while (fgets((lines + startReading), 75, file_resource) != NULL) {

            // uz mame zaznamy o studentoch
            if (startReading >= 2) {

                char readed_meno[20];
                char readed_priezvisko[20];
                char readed_studijna_skupina[8];
                int readed_pocet_bodov;

                // https://www.codingame.com/playgrounds/14213/how-to-play-with-strings-in-c/string-split
                // https://www.educative.io/edpresso/splitting-a-string-using-strtok-in-c
                char delimiter[] = "|";

                // dostavame ID, to ale nepotrebujeme pri vypisovani tabulky sa ID generuje podla poctu zaznamov
                char *ptr = strtok((lines + startReading), delimiter);

                // strtok() returns NULL when there is no more tokens, i.e., the whole string is split.
                if (ptr != NULL) {

                    // In the next call to strtok(), the first parameter needs to be NULL so that strtok() starts
                    // splitting the string from the next token's starting position it remembers.

                    // MENO
                    ptr = strtok(NULL, delimiter);

                    // retazec znakov musime orezat, potrebujeme orezat prvu a poslednu " " pre kazdy zaznam
                    // |  ID |                 Meno |           Priezvisko |  Skupina | Body |
                    // | --- | -------------------- | -------------------- | -------- | ---- |

                    char *output = substring(ptr, 1, sizeof(readed_meno) / sizeof(readed_meno[0]));
                    strcpy(readed_meno, output);
                    free(output);

                    // PRIEZVISKO
                    ptr = strtok(NULL, delimiter);
                } else {
                    fprintf(stderr, "Chyba poctu zaznamov v riadku otvoreneho suboru");
                    exit(EXIT_FAILURE);
                }

                if (ptr != NULL) {

                    char *output = substring(ptr, 1, sizeof(readed_priezvisko) / sizeof(readed_priezvisko[0]));
                    strcpy(readed_priezvisko,
                           output);
                    free(output);

                    // STUDIJNA_SKUPINA
                    ptr = strtok(NULL, delimiter);
                } else {
                    fprintf(stderr, "Chyba poctu zaznamov v riadku otvoreneho suboru");
                    exit(EXIT_FAILURE);
                }

                if (ptr != NULL) {

                    char *output = substring(ptr, 1, sizeof(readed_studijna_skupina) /
                                                     sizeof(readed_studijna_skupina[0]));
                    strcpy(readed_studijna_skupina, output);
                    free(output);

                    // POCET_BODOV
                    ptr = strtok(NULL, delimiter);
                } else {
                    fprintf(stderr, "Chyba poctu zaznamov v riadku otvoreneho suboru");
                    exit(EXIT_FAILURE);
                }

                if (ptr != NULL) {
                    char *pocet_bodov_string = substring(ptr, 1, 4);

                    // potrebujeme zo znakoveho pola ziskat int cislo
                    // https://stackoverflow.com/questions/7021725/how-to-convert-a-string-to-integer-in-c
                    readed_pocet_bodov = (int) strtol(pocet_bodov_string, (char **) NULL, 10);
                    free(pocet_bodov_string);

                } else {
                    fprintf(stderr, "Chyba poctu zaznamov v riadku otvoreneho suboru");
                    exit(EXIT_FAILURE);
                }

                Student *student = init_student();
                strcpy(student->meno, readed_meno);
                strcpy(student->priezvisko, readed_priezvisko);
                strcpy(student->studijna_skupina, readed_studijna_skupina);
                student->pocet_bodov = readed_pocet_bodov;

                if (add_student(student) == 1) {
                    fprintf(stderr, "Chyba pri pridavani zaznamov zo suboru");
                    fclose(file_resource);
                    exit(EXIT_FAILURE);

                } else {
                    printf("Zaznam cislo %d pridany \n", ++ID);
                }
            }

            // posun citacieho ramca
            ++startReading;
        }
    }

    // zatvarame subor a uvolnujeme alokovanu pamat
    printf("Hotovo nacitanych %d studentov \n", ID);
    fclose(file_resource);
    free(lines);

    return 0;
}

/**
 * Metoda na uvolnenie prostriedkov programu pred ukoncenim aplikacie
 */
void start_clean_up() {
    struct Node *current;

    // pomocna premenna
    struct Node *temp = NULL;

    for (current = head; current != NULL; current = temp) {
        temp = current->next;
        free(current);
    }
}