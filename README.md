# Caesar Cipher Encryption Tool


This is a C implementation of the Caesar Cipher encryption and decryption technique. It supports both text-based and file-based encryption/decryption.


## 🚀 Features


- Encrypt or decrypt text input
- Encrypt or decrypt entire files
- Works with both uppercase and lowercase letters
- Handles non-alphabetic characters by preserving them


## 🛠️ Build Instructions


### Requirements


- GCC or another C compiler
- Make (optional, for easier compilation)


### Build using Make


```bash
make


Run


make run


Or manually:


gcc -o cesar_cipher main.c
./cesar_cipher


🧪 Usage


   Choose an option from the menu:


       1: Encrypt text


       2: Decrypt text


       3: Encrypt a file


       4: Decrypt a file


       5: Exit


   Provide the required input and key.


Example:


   Encrypting text:


   Please enter a text (max 100 chars): hello world
   The key: 3
   The encrypted text is: khoor zruog


   File paths must be absolute or relative to your current working directory.


📁 File Structure


.
├── main.c         # Source code
├── Makefile       # Build script
└── README.md      # Project documentation
