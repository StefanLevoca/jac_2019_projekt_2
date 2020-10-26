// Tento súbor neupravujte, len ho importujte

#define TRUE 1
#define FALSE 0

#define FILE_DB "database.txt"

typedef struct StudentStruct {
    char meno[20];
    char priezvisko[20];
    char studijna_skupina[8];
    int pocet_bodov;
} Student;

/* Vypis informacii na konzolu. Iba tieto dve metody maju povolene vykonavat printf. */
void print_help();

void print_table();

/*
 Bonus: Vytvorte metody sprint_help a sprint_table tak aby nevypisovali nič priamo na konzolu ale,
 * text vrátia ako návratovú hodnotu volania funkcie.
*/
char *sprint_help();

char *sprint_table();

/* Pomocna metoda pre ziskanie noveho prazdenho studenta, v ramke */
Student *init_student();

/* CRUD operacie s databazou */
int add_student(Student *student);

Student *get_student(int identifier);

int update_student(int identifier, Student *student);

int delete_student(int identifier);

/* Doplnkove informacie o databaze */
int get_database_size();

/* Ulozenie databazy na disk */
int save_to_file(char *file_name);

/* Nacitanie databazy z disku*/
int open_from_file(char *file_name);