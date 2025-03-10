# Sikka Payment Service Application

A console-based payment service application written in C that simulates features of popular payment platforms.

## Features

- User registration and login
- Account management (balance checking, profile updates)
- Money transfers between users
- Bill payments for utilities and services
- Transaction history and statements
- Secure data storage in text files

## How to Compile

Using GCC:

```
gcc -o cpay main.c user.c account.c transaction.c ui.c
```

Or use the included Makefile:

```
ming32-make
```

## How to Use

1. Run the compiled executable:

```
./cpay
```

2. Register a new account or login with existing credentials
3. Navigate through the menu options to use the payment services

## Data Storage

The application stores all data in the following text files:

- users.txt: User account information
- accounts.txt: Account balances
- transactions.txt: Transaction history

## Notes

- When entering names or addresses with spaces, use underscores instead (e.g., John_Doe)
- All monetary values are stored in simple decimal format
