#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char username[50];
    char password[50];
} Account;

Account accounts[100];
int accountCount = 0;

void loadAccounts() {
    FILE *file = fopen("accounts.dat", "rb");
    if (file != NULL) {
        fread(&accountCount, sizeof(int), 1, file);
        fread(accounts, sizeof(Account), accountCount, file);
        fclose(file);
    }
}

void saveAccounts() {
    FILE *file = fopen("accounts.dat", "wb");
    if (file != NULL) {
        fwrite(&accountCount, sizeof(int), 1, file);
        fwrite(accounts, sizeof(Account), accountCount, file);
        fclose(file);
    }
}

int isUsernameTaken(const char *username) {
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0) {
            return 1; 
        }
    }
    return 0;
}

void registerAccount() {
    char username[50], password[50], confirmPassword[50];

    printf("\ndang ki tai khoan\n");
    printf("Nhap ten tai khoan: ");
    scanf("%s", username);

    if (isUsernameTaken(username)) {
        printf("Ten tai khoan da ton tai. Vui long thu lai.\n");
        return;
    }

    printf("Nhap mat khau: ");
    scanf("%s", password);
    printf("Xac nhan mat khau: ");
    scanf("%s", confirmPassword);

    if (strcmp(password, confirmPassword) != 0) {
        printf("Mat khau xac nhan khong khop. Vui long thu lai.\n");
        return;
    }

    if (accountCount < 100) {
        strcpy(accounts[accountCount].username, username);
        strcpy(accounts[accountCount].password, password);
        accountCount++;
        saveAccounts();
        printf("Dang ky tai khoan thanh cong!\n");
    } else {
        printf("So luong tai khoan da dat gioi han.\n");
    }
}

void login() {
    char username[50], password[50];

    printf("\nDANG NHAP\n");
    printf("Nhap ten tai khoan: ");
    scanf("%s", username);
    printf("Nhap mat khau: ");
    scanf("%s", password);

    for (int i = 0; i < accountCount; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0) {
            printf("Dang nhap thanh cong\n");
            return;
        }
    }
    printf("Dang nhap that bai. Vui long kiem tra lai thong tin.\n");
}

void menu() {
    int choice;
    do {
        printf("\nMENU\n");
        printf("1. Dang nhap\n");
        printf("2. Dang ky\n");
        printf("3. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                registerAccount();
                break;
            case 3:
                printf("Thoat chuong trinh\n");
                break;
            default:
                printf("Lua chon khong hop le\n");
        }
    } while (choice != 3);
}

int main() {
    loadAccounts();
    menu();
    return 0;
}


