#include <stdio.h>
#include <string.h>
void encrypt_file(char text[200],int shift);
void decrypt_file(char text[200],int shift);

int main() {
    int option=0;
    char input_name[200];
    char output_name[200];
    char text[256];
    int shift_key;
    printf("Simple File Encryption/Decryption Program.\n");
    printf("1. Encrypt a file.\n");
    printf("2. Decrypt a file.\n");
    printf("Enter your choice:");
    scanf("%d",&option);

    printf("Enter the input file name:");
    scanf("%s",input_name);
    printf("Enter the output file name:");
    scanf("%s",output_name);
    printf("Enter the key (integer):");
    scanf("%d",&shift_key);

    FILE *input_fptr = fopen(input_name, "r");
    FILE *output_fptr = fopen(output_name, "w");
    if (input_fptr == NULL || output_fptr==NULL) {
        printf("Error: Could not open file .\n");
        return 1;
    }else{
        while (fgets(text, sizeof(text), input_fptr) != NULL) {
            text[strcspn(text, "\n")] = '\0';
            if(option==1){
                encrypt_file(text, shift_key);
            }else if(option==2){
                decrypt_file(text, shift_key);
            }
            int written = fprintf(output_fptr, "%s\n", text);
            if (written < 0) {
                printf("Error: Failed to write to file!\n");
            } else {
                if(option==1){
                    printf("Encryption completed: Output saved to %s",output_name);
                }else if(option==2){
                    printf("Decryption completed: Output saved to %s",output_name);
                }
            }
        }

    }
    fclose(input_fptr);
    fclose(output_fptr);
    return 0;
}
void encrypt_file(char text[200],int shift){
    for(int i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        if(c >= 'A' && c <= 'Z')
            text[i] = ((c - 'A' + shift) % 26) + 'A';
        else if(c >= 'a' && c <= 'z')
            text[i] = ((c - 'a' + shift) % 26) + 'a';
    }
}
void decrypt_file(char text[200],int shift){
    for(int i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        if(c >= 'A' && c <= 'Z')
            text[i] = ((c - 'A' - shift+26) % 26) + 'A';
        else if(c >= 'a' && c <= 'z')
            text[i] = ((c - 'a' - shift+26) % 26) + 'a';
    }
}