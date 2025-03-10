# Comprehensive Documentation of Sikka Payment Service

## Overall Architecture

The application is structured into several key modules:

- User Management (user.h, user.c)
- Account Management (account.h, account.c)
- Transaction Processing (transaction.h, transaction.c)
- User Interface (ui.h, ui.c)
- Main Program Flow (main.c)

## Data Storage

The system uses three text files for data persistence:

1. users.txt: Stores user account information in format:
   `username password name email phone address`
2. accounts.txt: Stores account balances in format:
   `username balance`
3. transactions.txt: Stores transaction records in format:
   `sender_username transaction_type receiver_username amount datetime`

## Detailed Component Breakdown

### 1. User Management (user.h, user.c)

#### Data Structures

- `User struct`: Holds user information with fixed-size fields
  - username (30 chars)
  - password (30 chars)
  - name (50 chars)
  - email (50 chars)
  - phone (15 chars)
  - address (100 chars)

#### Key Functions

- `clearInputBuffer()`: Cleans input buffer by consuming remaining characters
- `secureInput()`: Safely reads input with newline handling
- `userExists()`: Checks if username exists in users.txt
- `validateUser()`: Verifies login credentials
- `registerUser()`: Creates new user account
  1. Collects user information
  2. Validates username availability
  3. Writes to users.txt
  4. Creates corresponding account with 0 balance
- `loginUser()`: Handles user authentication
- `updateUserProfile()`: Modifies user information
  1. Loads all users into memory
  2. Updates specific user
  3. Writes all data back to file

### 2. Account Management (account.h, account.c)

#### Data Structures

- `Account struct`: Links username to balance
  - username (30 chars)
  - balance (double)

#### Key Functions

- `createAccount()`: Initializes new account with balance
- `getBalance()`: Retrieves current balance
- `updateBalance()`: Modifies account balance
  1. Reads all accounts
  2. Updates specific account
  3. Writes all back to file
- `displayBalance()`: Shows formatted balance info
- `handleDeposit()`: Processes deposits
  1. Validates amount
  2. Updates balance
  3. Records transaction
- `handleWithdrawal()`: Processes withdrawals
  1. Checks sufficient funds
  2. Updates balance
  3. Records transaction

### 3. Transaction Processing (transaction.h, transaction.c)

#### Data Structures

- `Transaction struct`: Records financial operations
  - senderUsername (30 chars)
  - transactionType (20 chars)
  - receiverUsername (30 chars)
  - amount (double)
  - date (30 chars)

#### Key Functions

- `addTransaction()`: Records new transaction

  1. Gets current timestamp
  2. Formats transaction data
  3. Appends to transactions.txt
  4. Forces immediate write with fflush()

- `displayTransactionHistory()`: Shows user's transactions

  1. Reads transaction file line by line
  2. Parses different transaction formats
  3. Handles special cases (deposits, bills)
  4. Displays formatted output

- `handleTransfer()`: Processes money transfers

  1. Validates recipient
  2. Checks sufficient funds
  3. Updates both accounts
  4. Records transaction

- `handleBillPayment()`: Manages bill payments
  1. Shows bill types menu
  2. Validates amount
  3. Updates balance
  4. Records as BILL\_{TYPE} transaction

### 4. User Interface (ui.h, ui.c)

#### Functions

- `displayWelcomeBanner()`: Shows ASCII art welcome screen
- `displayAuthMenu()`: Shows login/register options
- `displayMainMenu()`: Shows main functionality menu

### 5. Main Program Flow (main.c)

#### Core Loop

1. Displays welcome banner
2. Authentication loop:
   - Login
   - Register
   - Exit
3. Main operation loop:
   - Check Balance
   - Deposit
   - Withdraw
   - Transfer
   - Bill Payment
   - Transaction History
   - Profile Update
   - Logout
   - Exit

### Error Handling

1. File Operations:

   - Checks for NULL on file open
   - Proper file closing in all paths
   - Error messages for file operations

2. Input Validation:

   - Buffer overflow prevention
   - Numeric input validation
   - Balance sufficiency checks

3. Data Consistency:
   - Atomic file writes
   - Complete transaction logging
   - Buffer flushing for immediate updates

### Security Measures

1. User Authentication:

   - Password verification
   - Session management
   - Input sanitization

2. Data Protection:
   - File-based persistence
   - Transaction logging
   - Profile update verification

### Transaction Types

1. Direct Transfers:

   - User-to-user transfers
   - Balance checks
   - Double-entry updates

2. System Transactions:

   - Deposits
   - Withdrawals
   - Bill payments

3. Bill Categories:
   - Electricity
   - Water
   - Internet
   - Mobile
   - Cable TV

### Memory Management

1. Static Allocation:

   - Fixed-size arrays
   - Predefined buffer sizes
   - Stack-based structures

2. File Handling:
   - Sequential file access
   - Complete file rewrites
   - Immediate buffer flushing

### User Experience Flow

1. Registration:

   - Username uniqueness check
   - Profile information collection
   - Account initialization

2. Authentication:

   - Credential verification
   - Session establishment
   - Menu access

3. Transaction Processing:

   - Amount validation
   - Balance verification
   - Confirmation prompts
   - Success/failure notifications

4. Profile Management:
   - Field-specific updates
   - Data persistence
   - Validation checks

This documentation covers every aspect of the system's functionality, from high-level architecture to low-level implementation details.
