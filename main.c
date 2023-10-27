/*
 * TODO: 
 * Bestand von Getränke anlegen
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* macros */
#define MOD(A, B) (A % B)
#define REST(A, B) (A / B)
#define PFAND 0.25
#define ADD 'a'
#define SUB 's'
#define CASHBOX "cashbox.dat"
#define STOCK "stock.dat"

/* enums */
enum Money { CENT1, CENT2, CENT5, CENT10, CENT20, CENT50, EURO1, EURO2, EURO5, EURO10, EURO20 };

/* structs */
struct Beverage {
    char name[32];
    float price;
    bool pfand;
};

struct Beverage beverages[] = {
    {"Wasser",       0.50, true},
    {"Limo",         1.00, true},
    {"Cola",         1.50, true},
    {"Saft",         2.00, false},
    {"Jägermeister", 2.10, false},
    {"Bier",         2.50, true},
};

float money[] = {
    0.01,
    0.02,
    0.05,
    0.10,
    0.20,
    0.50,
    1.00,
    2.00,
    5.00,
    10.00,
    20.00,
};

/* function prototypes */
float beverage_price(int choice);
void buy(int amount);
void cashbox(float price, char mode);
float coin_input();
bool check_coin(float input);
bool check_pfand(int choice);
void pfand(int amount);
void print_change(float change);
void stock(int amount)
int user_choice();

/* function implementation */
float beverage_price(int choice)
{
    switch (choice) {
    case 1:
        return beverages[choice-1].price;
        break;
    case 2:
        return beverages[choice-1].price;
        break;
    case 3:
        return beverages[choice-1].price;
        break;
    case 4:
        return beverages[choice-1].price;
        break;
    case 5:
        return beverages[choice-1].price;
        break;
    default:
        printf("Getränk nicht gefunden\n");
        exit(0);
    }
}

void buy(int amount)
{
    float change, input, price, tmp;
    int choice;
   
    price = 0;
    for (int i = 0; i < amount; i++) {
        choice = user_choice();
        price += beverage_price(choice);
        if (check_pfand(choice))
            price += PFAND;
    }

    printf("Der Preis für Ihre Auswahl beträgt %.2f\n", price);
    input = coin_input();
    while (input < price) {
        printf("Bitte werfen Sie noch eine Münze ein!\n");
        tmp = coin_input();
        input += tmp;
    }
    cashbox(price, ADD);

    if (input > price) {
        change = input - price;
        print_change(change);
    } else {
        change = 0;
    }
    cashbox(change, SUB);
    printf("Vielen Dank für Ihren Einkauf, bitte entnehmen Sie Ihre Flaschen und das Restgeld von %.2f\n", change);
}

void cashbox(float price, char mode)
{
    FILE *fp = fopen(CASHBOX, "r+");
    if (fp == NULL) {
        fprintf(stderr, "Can't open %s\n", CASHBOX);
        exit(1);
    }
    float cash;
    fscanf(fp, "%f", &cash);
    if (price > cash) {
        printf("Kein Wechselgeld vorhanden. Bitte rufen Sie einen Mitarbeiter\n");
        exit(0);
    }
    if (mode == 'a') {
        cash += price;
        fseek(fp, 0, SEEK_SET);
        fprintf(fp, "%.2f", cash);
    } else if (mode == 's') {
        cash = cash - price;
        fseek(fp, 0, SEEK_SET);
        fprintf(fp, "%.2f", cash);
    }
    fclose(fp);
}

float coin_input()
{
    float input;
    do {
        printf("Einwurf: ");
        scanf("%f", &input);
    } while (!check_coin(input));
    return input;
}

bool check_coin(float input)
{
    for (enum Money i = CENT1; i <= EURO20; i++) {
        if (input == money[i])
            return true;
    }
    printf("So eine Münze gibt es nicht!\n");
    return false;
}

bool check_pfand(int choice)
{
    if (beverages[choice - 1].pfand)
        return true;
    return false;
}

void pfand(int amount)
{
    float pfand = 0;
    for (int i = 0; i < amount; i++) {
        int choice = user_choice();
        if (check_pfand(choice)) {
            cashbox(PFAND, SUB);
            pfand += PFAND;
        } else {
            printf("Dieses Getränk hat keinen Pfand!\n");
        }
    }
    printf("Vielen Dank! Bitte entnehmen Sie Ihr Pfandgeld von %.2f.\n", pfand);
}

void print_change(float change)
{
    int cents = change * 100;

    printf("\n2 EUR:   %d\n", REST(cents, 200));
    cents = MOD(cents, 200);
    printf("1 EUR:   %d\n", REST(cents, 100));
    cents = MOD(cents, 100);
    printf("50 Cent: %d\n", REST(cents, 50));
    cents = MOD(cents, 50);
    printf("20 Cent: %d\n", REST(cents, 20));
    cents = MOD(cents, 20);
    printf("10 Cent: %d\n", REST(cents, 10));
    cents = MOD(cents, 10);
    printf("5 Cent:  %d\n", REST(cents, 5));
    cents = MOD(cents, 5);
    printf("2 Cent:  %d\n", REST(cents, 2));
    cents = MOD(cents, 2);
    printf("1 Cent:  %d\n\n", REST(cents, 1));
}

void stock(int amount)
{
    FILE *fp = fopen(STOCK, "r+");
    if (fp == NULL) {
        fprintf(stderr, "Can't open %s\n", STOCK);
        exit(1);
    }

    
}

int user_choice()
{
    int choice;
    int size = sizeof(beverages) / sizeof(beverages[0]);
    printf("Wählen Sie Ihre Getränk aus:\n");
    for (int i = 0; i < size; i++) {
        printf("%d) %s\n", i+1, beverages[i].name);
    }
    printf("> ");
    scanf("%d", &choice);
    return choice;
}

int main(int argc, char *argv[])
{
    int mode, amount;

    printf("GETRÄNKEAUTOMAT:\n");
    printf("----------------\n");

    printf("Was möchten Sie tun?\n");
    printf("1) Getränk kaufen\n");
    printf("2) Pfand zurückgeben\n> ");
    scanf("%d", &mode);

    switch (mode) {
    case 1:
        printf("Wie viele Getränke möchten Sie kaufen?\n> ");
        scanf("%d", &amount);
        buy(amount);
        break;
    case 2:
        printf("Wie viele Flaschen möchten Sie zurückgeben?\n> ");
        scanf("%d", &amount);
        pfand(amount);
        break;
    default:
        printf("Modus der Nummer %d wurde nicht gefunden\n", mode);
        break;
    }
    return 0;
}
