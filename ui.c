#include <stdio.h>
#include <stdlib.h>
#include "ui.h"

void displayWelcomeBanner() {
    printf("\n");
    printf("*******************************************************\n");
    printf("*                                                     *\n");
    printf("*             WELCOME TO Sikka SERVICE                *\n");
    printf("*                                                     *\n");
    printf("*              Your Secure Payment App                *\n");
    printf("*                                                     *\n");
    printf("*******************************************************\n");
}

void displayAuthMenu() {
    printf("\n===== AUTHENTICATION MENU =====\n");
    printf("1. Login\n");
    printf("2. Register\n");
    printf("3. Exit\n");
    printf("Choose an option: ");
}

void displayMainMenu(const char* username) {
    printf("\n===== MAIN MENU =====\n");
    printf("Welcome, %s!\n\n", username);
    printf("1. Check Balance\n");
    printf("2. Deposit Money\n");
    printf("3. Withdraw Money\n");
    printf("4. Transfer Money\n");
    printf("5. Pay Bills\n");
    printf("6. Transaction History\n");
    printf("7. Update Profile\n");
    printf("8. Logout\n");
    printf("9. Exit\n");
    printf("Choose an option: ");
}
