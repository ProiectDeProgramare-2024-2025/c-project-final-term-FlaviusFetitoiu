#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TABLES 50
#define MAX_RESERVATIONS 100

typedef struct {
    int id;
    int capacity;
    int available;
} Table;

typedef struct {
    int tableId;
    char date[15];
    char time[10];
} Reservation;

Table tables[MAX_TABLES];
Reservation reservations[MAX_RESERVATIONS];
int tableCount = 0, reservationCount = 0;

void apasaenter() {
    printf("\nApasa enter pentru a te intoarce la meniul principal.");
    while (getchar() != '\n');
    getchar();
}

void saveData() {
    FILE *file = fopen("tables.txt", "w");
    if (file) {
        fprintf(file, "%d\n", tableCount);
        for (int i = 0; i < tableCount; i++) {
            fprintf(file, "%d %d %d\n", tables[i].id, tables[i].capacity, tables[i].available);
        }
        fclose(file);
    }

    file = fopen("reservations.txt", "w");
    if (file) {
        fprintf(file, "%d\n", reservationCount);
        for (int i = 0; i < reservationCount; i++) {
            fprintf(file, "%d %s %s\n", reservations[i].tableId, reservations[i].date, reservations[i].time);
        }
        fclose(file);
    }
}

void loadData() {
    FILE *file = fopen("tables.txt", "r");
    if (file) {
        fscanf(file, "%d", &tableCount);
        for (int i = 0; i < tableCount; i++) {
            fscanf(file, "%d %d %d", &tables[i].id, &tables[i].capacity, &tables[i].available);
        }
        fclose(file);
    }

    file = fopen("reservations.txt", "r");
    if (file) {
        fscanf(file, "%d", &reservationCount);
        for (int i = 0; i < reservationCount; i++) {
            fscanf(file, "%d %s %s", &reservations[i].tableId, reservations[i].date, reservations[i].time);
        }
        fclose(file);
    }
}

void addTable(int capacity) {
    if (tableCount < MAX_TABLES) {
        tables[tableCount].id = tableCount + 1;
        tables[tableCount].capacity = capacity;
        tables[tableCount].available = 1;
        tableCount++;
        saveData();
        printf("Masa adaugata cu succes!\n");
        apasaenter();
    } else {
        printf("Nu se mai pot adauga mese!\n");
        apasaenter();
    }
}

void removeTable(int id) {
    for (int i = 0; i < tableCount; i++) {
        if (tables[i].id == id) {
            for (int j = i; j < tableCount - 1; j++) {
                tables[j] = tables[j + 1];
            }
            tableCount--;
            saveData();
            printf("Masa eliminata cu succes!\n");
            apasaenter();
            return;
        }
    }
    printf("Masa nu a fost gasita!\n");
    apasaenter();
}

void listTables() {
    printf("Mese disponibile:\n");
    for (int i = 0; i < tableCount; i++) {
        printf("ID: %d, Capacitate: %d, Disponibil: %s\n", tables[i].id, tables[i].capacity, tables[i].available ? "\033[1;32mDa\033[0m\n ": "\033[1;31mNu\033[0m\n");
    }
    apasaenter();
}
void listReservations() {
    printf("Rezervari:\n");
    for (int i = 0; i < reservationCount; i++) {
        printf("Masa ID: %d, Data: %s, Ora: %s\n", reservations[i].tableId, reservations[i].date, reservations[i].time);
    }
    apasaenter();
}

void searchTable(int capacity) {
    for (int i = 0; i < tableCount; i++) {
        if (tables[i].capacity >= capacity && tables[i].available) {
            printf("Masa gasita - ID: %d, Capacitate: %d\n", tables[i].id, tables[i].capacity);
            apasaenter();
            return;
        }
    }
    printf("Nu s-a gasit nicio masa disponibila pentru aceasta capacitate.\n");
    apasaenter();
}

void makeReservation(int id, char *date, char *time) {
    for (int i = 0; i < tableCount; i++) {
        if (tables[i].id == id && tables[i].available) {
            reservations[reservationCount].tableId = id;
            strcpy(reservations[reservationCount].date, date);
            strcpy(reservations[reservationCount].time, time);
            reservationCount++;
            tables[i].available = 0;
            saveData();
            printf("Rezervare efectuata cu succes!\n");
            apasaenter();
            return;
        }
    }
    printf("Masa nu este disponibila!\n");
    apasaenter();
}

void cancelReservation(int id) {
    for (int i = 0; i < reservationCount; i++) {
        if (reservations[i].tableId == id) {
            for (int j = i; j < reservationCount - 1; j++) {
                reservations[j] = reservations[j + 1];
            }
            reservationCount--;
            for (int k = 0; k < tableCount; k++) {
                if (tables[k].id == id) {
                    tables[k].available = 1;
                    break;
                }
            }
            saveData();
            printf("Rezervare anulata cu succes!\n");
            apasaenter();
            return;
        }
    }
    printf("Rezervarea nu a fost gasita!\n");
    apasaenter();
}
void clearscreen() {
    system("cls || clear");
}
int main() {
    loadData();
    int choice, capacity, id;
    char date[15], time[10];

    while (1){
        clearscreen();
        printf("===Meniu principal===\n");
        printf("\n1. Adauga masa\n2. Sterge masa\n3. Afiseaza mese\n4. Cauta masa\n5. Fa rezervare\n6. Anuleaza rezervare\n7. Afiseaza rezervari\n8. Iesire\n");
        printf("Alegeti o optiune: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                clearscreen();
                printf("===Adauga masa===\n");
                printf("Introduceti capacitatea mesei: ");
                scanf("%d", &capacity);
                addTable(capacity);
                break;
            case 2:
                clearscreen();
                printf("===Sterge masa===\n");
                printf("Introduceti ID-ul mesei: ");
                scanf("%d", &id);
                removeTable(id);
                break;
            case 3:
                clearscreen();
                printf("===Afiseaza mese===\n");
                listTables();
                break;
            case 4:
                clearscreen();
                printf("===Cauta mese===\n");
                printf("Introduceti capacitatea dorita: ");
                scanf("%d", &capacity);
                searchTable(capacity);
                break;
            case 5:
                clearscreen();
                printf("===Rezervare===\n");
                printf("Introduceti ID-ul mesei: ");
                scanf("%d", &id);
                printf("Introduceti data (dd/mm/yyyy): ");
                scanf("%s", date);
                printf("Introduceti ora (hh:mm): ");
                scanf("%s", time);
                makeReservation(id, date, time);
                break;
            case 6:
                clearscreen();
                printf("===Anuleaza rezervare===\n");
                printf("Introduceti ID-ul mesei: ");
                scanf("%d", &id);
                cancelReservation(id);
                break;
            case 7:
                clearscreen();
                printf("===Lista revervari===\n");
                listReservations();
                break;
            case 8:
                clearscreen();
                saveData();
                exit(0);
            default:
                clearscreen();
                printf("Optiune invalida!\n");
        }
    }
    return 0;
}
