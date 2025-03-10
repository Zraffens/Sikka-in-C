#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "account.h"
#include "transaction.h"
#include "user.h"

#define ACCOUNTS_FILE "accounts.txt"

int createAccount(const char* username, double initialBalance) {
    FILE* file = fopen(ACCOUNTS_FILE, "a");
    if (file == NULL) {
        printf("Error opening accounts file!\n");
        return 0;
    }
    
    fprintf(file, "%s %.2f\n", username, initialBalance);
    fclose(file);
    return 1;
}

double getBalance(const char* username) {
    FILE* file = fopen(ACCOUNTS_FILE, "r");
    if (file == NULL) {
        printf("Error opening accounts file!\n");
        return -1;
    }
    
    char fileUsername[30];
    double balance;
    
    while (fscanf(file, "%s %lf", fileUsername, &balance) == 2) {
        if (strcmp(fileUsername, username) == 0) {
            fclose(file);
            return balance;
        }
    }
    
    fclose(file);
    return -1; // User not found
}

int updateBalance(const char* username, double newBalance) {
    FILE* file = fopen(ACCOUNTS_FILE, "r");
    if (file == NULL) {
        printf("Error opening accounts file!\n");
        return 0;
    }
    
    // Read all accounts
    Account accounts[100];
    int accountCount = 0;
    
    while (fscanf(file, "%s %lf", accounts[accountCount].username, 
                 &accounts[accountCount].balance) == 2 && accountCount < 100) {
        accountCount++;
    }
    fclose(file);
    
    // Find and update user's balance
    int found = 0;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            accounts[i].balance = newBalance;
            found = 1;
            break;
        }
    }
    
    if (!found) {
        return 0; // User not found
    }
    
    // Write all accounts back to file
    file = fopen(ACCOUNTS_FILE, "w");
    if (file == NULL) {
        printf("Error opening accounts file for writing!\n");
        return 0;
    }
    
    for (int i = 0; i < accountCount; i++) {
        fprintf(file, "%s %.2f\n", accounts[i].username, accounts[i].balance);
    }
    fclose(file);
    
    return 1;
}

void displayBalance(const char* username) {
    double balance = getBalance(username);
    
    printf("\n===== ACCOUNT BALANCE =====\n");
    if (balance >= 0) {
        printf("Account: %s\n", username);
        printf("Current Balance: $%.2f\n", balance);
    } else {
        printf("Error retrieving balance information.\n");
    }
}

void handleDeposit(const char* username) {
    double amount, currentBalance;
    
    printf("\n===== DEPOSIT MONEY =====\n");
    printf("Enter amount to deposit: $");
    if (scanf("%lf", &amount) != 1 || amount <= 0) {
        printf("Invalid amount. Please enter a positive number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    currentBalance = getBalance(username);
    if (currentBalance < 0) {
        printf("Error retrieving account information.\n");
        return;
    }
    
    double newBalance = currentBalance + amount;
    if (updateBalance(username, newBalance)) {
        // Record the transaction
        addTransaction(username, "DEPOSIT", "", amount);
        printf("Deposit successful! New balance: $%.2f\n", newBalance);
    } else {
        printf("Deposit failed. Please try again later.\n");
    }
}

void handleWithdrawal(const char* username) {
    double amount, currentBalance;
    
    printf("\n===== WITHDRAW MONEY =====\n");
    printf("Enter amount to withdraw: $");
    if (scanf("%lf", &amount) != 1 || amount <= 0) {
        printf("Invalid amount. Please enter a positive number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    currentBalance = getBalance(username);
    if (currentBalance < 0) {
        printf("Error retrieving account information.\n");
        return;
    }
    
    if (amount > currentBalance) {
        printf("Insufficient funds. Your current balance is $%.2f\n", currentBalance);
        return;
    }
    
    double newBalance = currentBalance - amount;
    if (updateBalance(username, newBalance)) {
        // Record the transaction
        addTransaction(username, "WITHDRAWAL", "", amount);
        printf("Withdrawal successful! New balance: $%.2f\n", newBalance);
    } else {
        printf("Withdrawal failed. Please try again later.\n");
    }
}
