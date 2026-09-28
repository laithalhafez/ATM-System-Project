# ATM System (C++)

A console-based ATM application built in C++ featuring client login, quick and normal withdrawal modes, deposits, balance inquiry, and PIN code updates with automatic file synchronization.

## 🎮 Features
- **Client Authentication:** Secure client login using Account Number and PIN Code.
- **ATM Main Menu:**
  - ⚡ **Quick Withdraw:** Preset withdrawal amounts ($20, $50, $100, up to $1000).
  - 💵 **Normal Withdraw:** Custom withdrawal amounts restricted to multiples of 5 with balance verification.
  - 💰 **Deposit:** Direct deposit processing with real-time balance updates.
  - 📊 **Check Balance:** View current account balance.
  - 🔑 **Change PIN Code:** Update account PIN after old PIN confirmation.
- **Persistent Data Storage:** Real-time synchronization of account data with the `AllClientsData.txt` file.

## 🔑 Demo Credentials
You can test the system using the following account details from `AllClientsData.txt`:

| Account Number | PIN Code | Account Holder | Phone Number | Initial Balance |
| :--- | :--- | :--- | :--- | :--- |
| `A5343` | `4444` | Mohammad Laith Alhafez | 0994774811 | $49,000.00 |
| `R3322` | `55555` | Ali | 09234378623 | $3,000.00 |
| `W233` | `77777` | Omar | 0932489234 | $6,400.00 |
| `G553` | `8888` | HaDy | 0923424253 | $8,000.00 |
| `N4234` | `7777` | Mahmoud Alajamy | 0942235 | $60,000.00 |

## 🛠️ Code & Concepts
- **Clean Code & SRP:** Functions structured with single responsibilities for readability and maintenance.
- **Structs & State Management:** Utilizes `stClientInfo` to manage session state (`CurrentClient`).
- **File I/O & Parsing:** Reads and writes delimited lines (`#//#`) using `vSplitFunction` and file streams (`fstream`).
- **Input Validation:** Enforces valid withdrawal increments (`IsAmountValid`) and prevents overdrawing funds.

## 🚀 How to Run

1. Create a file named `AllClientsData.txt` in the project directory and paste the demo credentials above.
2. Open the project in **Visual Studio** or any C++ IDE.
3. Compile and run the `ATM System.cpp` file.
4. Log in using any of the credentials provided above!
