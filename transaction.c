#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "transaction.h"
#include "account.h"
#include "user.h"

#define TRANSACTIONS_FILE "transactions.txt"

int addTransaction(const char* senderUsername, const char* transactionType, 
                  const char* receiverUsername, double amount) {
    FILE* file = fopen(TRANSACTIONS_FILE, "a");
    if (file == NULL) {
        printf("Error opening transactions file!\n");
        return 0;
    }
    
    // Get current date and time
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char date[30];
    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", t);
    
    fprintf(file, "%s %s %s %.2f %s\n", 
            senderUsername, transactionType, receiverUsername, amount, date);
    fflush(file);  // Force write to disk
    fclose(file);
    return 1;
}

void displayTransactionHistory(const char* username) {
    FILE* file = fopen(TRANSACTIONS_FILE, "r");
    if (file == NULL) {
        printf("No transaction history found.\n");
        return;
    }
    
    // Ensure we're reading from the start of file
    rewind(file);
    
    printf("\n===== TRANSACTION HISTORY =====\n");
    printf("%-20s %-15s %-20s %-10s %-20s\n", 
           "Sender", "Type", "Receiver", "Amount", "Date");
    printf("------------------------------------------------------------------------------------\n");
    
    char senderUsername[30], transactionType[20], receiverUsername[30], date[30];
    double amount;
    int found = 0;
    
    char line[200];  // Buffer for reading entire line
    
    while (fgets(line, sizeof(line), file) != NULL) {
        // Reset receiverUsername to empty for each line
        receiverUsername[0] = '\0';
        
        // Parse the line carefully
        int items = sscanf(line, "%s %s %s %lf %[^\n]", 
                          senderUsername, transactionType, receiverUsername, &amount, date);
        
        // If we only got 4 items, the format might be "sender type - amount date"
        // This means there's no receiver (e.g., for DEPOSIT, WITHDRAWAL, BILL payments)
        if (items == 4) {
            // Move data: what we thought was receiverUsername is actually amount
            // and what we thought was amount is actually date
            strcpy(date, receiverUsername);  // Save what we read as receiverUsername to date
            sscanf(date, "%lf", &amount);    // Parse amount from what we saved
            
            // Get the date (it's now the 4th parameter)
            sscanf(line, "%s %s %s %s", senderUsername, transactionType, receiverUsername, date);
            
            // Clear receiverUsername as it's not a real recipient
            receiverUsername[0] = '-';
            receiverUsername[1] = '\0';
        }
        
        // Check if user is sender or receiver (only check receiver if it's not empty)
        if (strcmp(senderUsername, username) == 0 || 
            (receiverUsername[0] != '-' && strcmp(receiverUsername, username) == 0)) {
            
            printf("%-20s %-15s %-20s $%-10.2f %-20s\n", 
                   senderUsername, transactionType, 
                   (receiverUsername[0] == '-') ? "-" : receiverUsername, 
                   amount, date);
            found = 1;
        }
    }
    
    fclose(file);
    
    if (!found) {
        printf("No transactions found for your account.\n");
    }
}

void handleTransfer(const char* senderUsername) {
    char receiverUsername[30];
    double amount, senderBalance, receiverBalance;
    
    printf("\n===== TRANSFER MONEY =====\n");
    printf("Enter recipient's username: ");
    scanf("%s", receiverUsername);
    clearInputBuffer();
    
    if (strcmp(senderUsername, receiverUsername) == 0) {
        printf("You cannot transfer money to yourself.\n");
        return;
    }
    
    if (!userExists(receiverUsername)) {
        printf("Recipient account not found.\n");
        return;
    }
    
    printf("Enter amount to transfer: $");
    if (scanf("%lf", &amount) != 1 || amount <= 0) {
        printf("Invalid amount. Please enter a positive number.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    senderBalance = getBalance(senderUsername);
    if (senderBalance < 0) {
        printf("Error retrieving your account information.\n");
        return;
    }
    
    if (amount > senderBalance) {
        printf("Insufficient funds. Your current balance is $%.2f\n", senderBalance);
        return;
    }
    
    receiverBalance = getBalance(receiverUsername);
    if (receiverBalance < 0) {
        printf("Error retrieving recipient's account information.\n");
        return;
    }
    
    // Confirm transfer
    char confirm;
    printf("Transfer $%.2f to %s? (y/n): ", amount, receiverUsername);
    scanf(" %c", &confirm);
    clearInputBuffer();
    
    if (confirm != 'y' && confirm != 'Y') {
        printf("Transfer cancelled.\n");
        return;
    }
    
    // Update both balances
    if (updateBalance(senderUsername, senderBalance - amount) && 
        updateBalance(receiverUsername, receiverBalance + amount)) {
        
        // Record the transaction
        addTransaction(senderUsername, "TRANSFER", receiverUsername, amount);
        printf("Transfer successful! New balance: $%.2f\n", senderBalance - amount);
    } else {
        printf("Transfer failed. Please try again later.\n");
    }
}

void handleBillPayment(const char* username) {
    int billChoice;
    double amount, currentBalance;
    char billType[50];
    
    printf("\n===== PAY BILLS =====\n");
    printf("1. Electricity Bill\n");
    printf("2. Water Bill\n");
    printf("3. Internet Bill\n");
    printf("4. Mobile Recharge\n");
    printf("5. Cable TV\n");
    printf("Enter your choice: ");
    
    if (scanf("%d", &billChoice) != 1 || billChoice < 1 || billChoice > 5) {
        printf("Invalid choice.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    
    switch (billChoice) {
        case 1: strcpy(billType, "ELECTRICITY"); break;
        case 2: strcpy(billType, "WATER"); break;
        case 3: strcpy(billType, "INTERNET"); break;
        case 4: strcpy(billType, "MOBILE"); break;
        case 5: strcpy(billType, "CABLE_TV"); break;
    }
    
    printf("Enter bill amount: $");
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
    
    // Confirm bill payment
    char confirm;
    printf("Pay %s bill of $%.2f? (y/n): ", billType, amount);
    scanf(" %c", &confirm);
    clearInputBuffer();
    
    if (confirm != 'y' && confirm != 'Y') {
        printf("Bill payment cancelled.\n");
        return;
    }
    
    double newBalance = currentBalance - amount;
    if (updateBalance(username, newBalance)) {
        // Record the transaction
        char transactionType[30] = "BILL_";
        strcat(transactionType, billType);
        addTransaction(username, transactionType, "", amount);
        printf("%s bill payment successful! New balance: $%.2f\n", billType, newBalance);
    } else {
        printf("Bill payment failed. Please try again later.\n");
    }
}
