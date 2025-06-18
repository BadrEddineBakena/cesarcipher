#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char* createShiftedAlphabet(int key) {
   char* shiftedAlphabet = malloc(27 * sizeof(char));
   if (shiftedAlphabet == NULL) return NULL;


   char alphabets[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   for (int i = 0; i < 26; i++) {
       shiftedAlphabet[i] = alphabets[(i + key) % 26];
   }
   shiftedAlphabet[26] = '\0';
   return shiftedAlphabet;
}


char *encryptText(char *text, int key) {
   char alphabets[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
   char *shiftedAlphabet = createShiftedAlphabet(key);
   char *ptr = alphabets;
   char *result = malloc(strlen(text) + 1);
   char *resStart = result;


   if (!result || !shiftedAlphabet) return NULL;


   while (*text) {
       char *pos = NULL;


       if (islower(*text)) {
           pos = strchr(ptr, toupper(*text));
           *result = pos ? shiftedAlphabet[pos - ptr] + ('a' - 'A') : *text;
       } else {
           pos = strchr(ptr, *text);
           *result = pos ? shiftedAlphabet[pos - ptr] : *text;
       }


       text++;
       result++;
   }


   *result = '\0';
   free(shiftedAlphabet);
   return resStart;
}


char *decryptText(char *text, int key) {
   return encryptText(text, 26 - key);
}


void readText(char *buffer, size_t size, const char *prompt) {
   printf("%s", prompt);
   if (fgets(buffer, size, stdin)) {
       size_t len = strlen(buffer);
       if (len > 0 && buffer[len - 1] == '\n') {
           buffer[len - 1] = '\0';
       }
   } else {
       buffer[0] = '\0';
   }
}


int readKey(const char *prompt) {
   int key;
   printf("%s", prompt);
   scanf("%d", &key);


   int c;
   while ((c = getchar()) != '\n' && c != EOF);


   return key % 26;
}


void encryptFile(const char *inputPath, const char *outputPath, int key) {
   if (!inputPath || !outputPath) return;


   FILE *file = fopen(inputPath, "r");
   if (!file) {
       perror("Error opening input file");
       return;
   }


   FILE *output = fopen(outputPath, "w");
   if (!output) {
       perror("Error opening output file");
       fclose(file);
       return;
   }


   char line[1024];
   while (fgets(line, sizeof(line), file)) {
       char *encryptedLine = encryptText(line, key);
       if (encryptedLine) {
           fprintf(output, "%s", encryptedLine);
           free(encryptedLine);
       }
   }


   fclose(file);
   fclose(output);
   printf("Successfully encrypted file: %s -> %s\n", inputPath, outputPath);
}


void decryptFile(const char *inputPath, const char *outputPath, int key) {
   if (!inputPath || !outputPath) return;


   FILE *file = fopen(inputPath, "r");
   if (!file) {
       perror("Error opening input file");
       return;
   }


   FILE *output = fopen(outputPath, "w");
   if (!output) {
       perror("Error opening output file");
       fclose(file);
       return;
   }


   char line[1024];
   while (fgets(line, sizeof(line), file)) {
       char *decryptedLine = decryptText(line, key);
       if (decryptedLine) {
           fprintf(output, "%s", decryptedLine);
           free(decryptedLine);
       }
   }


   fclose(file);
   fclose(output);
   printf("Successfully decrypted file: %s -> %s\n", inputPath, outputPath);
}




void displayMsg() {
   printf("\n Pick a number : ");
}




int main(void) {
   printf("=================================\n |\t\t CesarCipher\t\t\t | \n ===============================\n");
   printf("Welcome to CesarCipher encryption tool , choose what you want:\n");
   printf("1: encrypt a text\n");
   printf("2: decrypt a text\n");
   printf("3: encrypt a file\n");
   printf("4: decrypt a file\n");
   printf("5: exit\n");
   displayMsg();
   char buffer[10];
   int choice = 0;


   while (choice != 5) {
       fgets(buffer, sizeof(buffer), stdin);
       sscanf(buffer, "%d", &choice);


       switch (choice) {
           case 1: {
               char text[101];
               readText(text, sizeof(text), "Please enter a text (max 100 chars): ");
               int key = readKey("The key: ");
               char *encrypted = encryptText(text, key);
               if (encrypted) {
                   printf("The encrypted text is: %s\n", encrypted);
                   free(encrypted);
               } else {
                   printf("Encryption failed due to memory error.\n");
               }
               break;
           }


           case 2: {
               char text[101];
               readText(text, sizeof(text), "Please enter an encrypted text (max 100 chars): ");
               int key = readKey("The key: ");
               char *decrypted = decryptText(text, key);
               if (decrypted) {
                   printf("The decrypted text is: %s\n", decrypted);
                   free(decrypted);
               } else {
                   printf("Decryption failed due to memory error.\n");
               }
               break;
           }


           case 3: {
               char path[101], path2[101];
               readText(path, sizeof(path), "Please enter the path of the file to encrypt (full path): ");
               readText(path2, sizeof(path2), "Please enter the path of the file to store encrypted content: ");
               int key = readKey("The key: ");
               encryptFile(path, path2, key);
               break;
           }


           case 4: {
               char path[101], path2[101];
               readText(path, sizeof(path), "Please enter the path of the file to decrypt (full path): ");
               readText(path2, sizeof(path2), "Please enter the path of the file to store decrypted content: ");
               int key = readKey("The key: ");
               decryptFile(path, path2, key);
               break;
           }


           case 5: {
               printf("Goodbye\n");
               return 0;
           }


           default: {
               printf("Invalid choice, try again.\n");
               break;
           }
       }
       displayMsg();
   }


   return 0;
}


