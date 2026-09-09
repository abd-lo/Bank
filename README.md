# Bank Management System (C++ Console Application)

A console-based banking system written in **C++**, using file-based persistence and a class hierarchy inherited from a shared `clsPerson` base. It manages client accounts, core banking transactions, a currency exchange module, and a permission-based user login system.

## Overview

The application simulates the back-office side of a bank branch: tellers/staff log in with individual accounts, and — depending on their assigned permissions — can manage client accounts, process deposits/withdrawals/transfers, and look up exchange rates. Every meaningful action (transfers, logins) is written to an append-only log file, giving the system a basic audit trail.

## Features

### Client Accounts
- Add, update, delete (soft-delete via a "marked for delete" flag), and list bank clients.
- Each client has a first/last name, email, phone, a unique **account number**, a **PIN code**, and an account balance.
- Find a client by account number, or by account number + PIN (used to authorize transactions).

### Banking Operations
- **Deposit** — increases a client's balance and persists it immediately.
- **Withdraw** — decreases a client's balance, but only if sufficient funds are available; insufficient-funds withdrawals are rejected.
- **Transfer** — moves funds between two client accounts (deposits into the destination, then withdraws from the source) and, on success, writes a record to a transfer log with the amount, both account numbers, resulting balances, and the staff username who performed it.
- **Total balances** — reports the sum of every client's balance across the bank.

### Currency Exchange
- Maintains a list of currencies, each with a country, currency code, name, and exchange rate.
- Add, update, and look up currencies by code.
- Convert amounts between currencies using **USD as the base/intermediary currency** (an amount is first converted to USD, then from USD to the target currency).
- A calculator screen lets staff convert an arbitrary amount between any two listed currencies.

### Users & Permission-Based Access
- Staff log in with a username and password (passwords are stored with a simple reversible character-shift cipher, not a cryptographic hash).
- Each user is assigned a **permissions bitmask** (`enPermissions`), with individual bits for listing clients, adding/deleting/updating clients, finding a client, performing transactions, managing users, and viewing the login registry — plus a special "all permissions" value.
- `CheckAccessPermission()` gates every sensitive menu option against the logged-in user's bitmask, so a user without the `pManageUsers` bit, for example, can't reach the user-management screen.
- Every successful login is timestamped and appended to a login registry, viewable by users with the relevant permission.

## Architecture

This is a single console application, structured as header-only C++ classes rather than a layered/multi-project solution:

| File / Folder | Responsibility |
|---|---|
| `clsPerson.h` | Base class for shared identity fields (name, email, phone) |
| `clsBankClientTest.h` | `clsBankClient` — accounts, balances, deposit/withdraw/transfer, transfer logging |
| `clsUser.h` | Staff accounts, authentication, permission bitmask, login registry |
| `CurrencyExchange/clsCurrency.h` | Currency records and USD-based conversion logic |
| `Libraries/` | Shared helpers — string splitting, input validation, date formatting, encryption utility |
| `Screens/` | One class per menu screen (list/add/delete/update/find clients, transactions, manage users, currency exchange, etc.), each gated by the current user's permissions |
| `Global.h` | Holds the currently logged-in user for the session |
| `Main.cpp` | Entry point — loops on the login screen, then hands off to the main menu |

### Data Persistence
No database is used — all data is stored in plain-text, delimiter-separated (`#//#`) files in the project root:

| File | Contents |
|---|---|
| `Clients.txt` | Client records (name, contact info, account number, PIN, balance) |
| `Users.txt` | Staff user records (name, contact info, username, encrypted password, permissions) |
| `Currencies.txt` | Currency records (country, code, name, exchange rate) |
| `TransfersLog.txt` | Append-only log of every successful transfer |
| `Login.txt` | Append-only log of every successful login (timestamp, username, permissions) |

## Tech Stack

- **Language:** C++
- **I/O:** Standard file streams (`fstream`) for persistence — no external database
- **Interface:** Console (text-based menus)

## Getting Started

### Prerequisites
- A C++ compiler (g++, MSVC, or Clang)

### Build & Run
```bash
g++ Main.cpp -o Bank
./Bank
```
On first run, `Clients.txt`, `Users.txt`, `Currencies.txt`, `Login.txt`, and `TransfersLog.txt` are read from (and written to) the working directory — make sure the executable is run from the project root so these files can be found/created.

## Project Structure

```
Bank/
├── Main.cpp                     # Entry point
├── Global.h                     # Session-wide current user
├── clsUser.h                    # Staff accounts, auth, permissions
├── clsBankClientTest.h          # Client accounts & transactions
├── CurrencyExchange/
│   ├── Main.cpp
│   └── clsCurrency.h            # Currency records & conversion
├── Libraries/
│   ├── clsPerson.h              # Shared base class
│   ├── clsString.h              # String helpers (split, etc.)
│   ├── clsInputValidate.h       # Console input validation
│   ├── clsDate.h                # Date/time formatting
│   └── clsUtil.h                # Password cipher, misc utilities
├── Screens/                     # One class per menu screen
├── Clients.txt / Users.txt / Currencies.txt
├── TransfersLog.txt / Login.txt # Data files (generated at runtime)
```

## License

This project is available for educational and personal use.
