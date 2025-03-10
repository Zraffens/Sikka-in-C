#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <time.h>

typedef struct {
    char senderUsername[30];
    char transactionType[20]; // TRANSFER, DEPOSIT, WITHDRAWAL, BILL_PAYMENT
    char receiverUsername[30];
    double amount;
    char date[30];
} Transaction;

int addTransaction(const char* senderUsername, const char* transactionType, 
                  const char* receiverUsername, double amount);
void displayTransactionHistory(const char* username);
void handleTransfer(const char* senderUsername);
void handleBillPayment(const char* username);

#endif /* TRANSACTION_H */
