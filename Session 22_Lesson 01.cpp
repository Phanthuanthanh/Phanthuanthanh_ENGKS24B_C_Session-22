#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    int age;
} Student;

const int MAX_STUDENTS = 100;
const char FILE_NAME[] = "students.dat";

Student students[MAX_STUDENTS];
int student_count = 0;

void load_students_from_file() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file != NULL) {
        student_count = fread(students, sizeof(Student), MAX_STUDENTS, file);
        fclose(file);
    }
}

void save_students_to_file() {
    FILE *file = fopen(FILE_NAME, "wb");
    if (file != NULL) {
        fwrite(students, sizeof(Student), student_count, file);
        fclose(file);
    }
}

void display_students() {
    if (student_count == 0) {
        printf("Danh sach sinh vien trong.\n");
        return;
    }
    printf("\nDanh sach sinh vien:\n");
    printf("%-5s %-20s %-5s\n", "ID", "Ten", "Tuoi");
    for (int i = 0; i < student_count; i++) {
        printf("%-5d %-20s %-5d\n", students[i].id, students[i].name, students[i].age);
    }
}

void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("Khong the them sinh vien. Danh sach da du.\n");
        return;
    }
    Student new_student;
    printf("Nhap ID: ");
    scanf("%d", &new_student.id);
    printf("Nhap ten: ");
    getchar(); 
    fgets(new_student.name, sizeof(new_student.name), stdin);
    new_student.name[strcspn(new_student.name, "\n")] = '\0'; 
    printf("Nhap tuoi: ");
    scanf("%d", &new_student.age);
    students[student_count++] = new_student;
    save_students_to_file();
    printf("Them sinh vien thanh cong.\n");
}

void edit_student() {
    int id;
    printf("Nhap ID sinh vien can sua: ");
    scanf("%d", &id);
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            printf("Nhap ten moi: ");
            getchar(); 
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0';
            printf("Nhap tuoi moi: ");
            scanf("%d", &students[i].age);
            save_students_to_file();
            printf("Cap nhat thong tin sinh vien thanh cong.\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien \n", id);
}

void delete_student() {
    int id;
    printf("Nhap ID sinh vien can xoa: ");
    scanf("%d", &id);
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            for (int j = i; j < student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            student_count--;
            save_students_to_file();
            printf("Xoa sinh vien thanh cong.\n");
            return;
        }
    }
    printf("Khong tim thay sinh vien \n", id);
}

void search_student() {
    int id;
    printf("Nhap ID sinh vien can tim: ");
    scanf("%d", &id);
    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id) {
            printf("\nSinh vien tim thay:\n");
            printf("ID: %d\n", students[i].id);
            printf("Ten: %s\n", students[i].name);
            printf("Tuoi: %d\n", students[i].age);
            return;
        }
    }
    printf("Khong tim thay sinh vien\n", id);
}

void sort_students() {
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = i + 1; j < student_count; j++) {
            if (students[i].id > students[j].id) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    save_students_to_file();
    printf("Sap xep danh sach sinh vien thanh cong.\n");
}

int main() {
    load_students_from_file();
    int choice;
    do {
        printf("\nMENU\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                display_students();
                break;
            case 2:
                add_student();
                break;
            case 3:
                edit_student();
                break;
            case 4:
                delete_student();
                break;
            case 5:
                search_student();
                break;
            case 6:
                sort_students();
                break;
            case 7:
                printf("Thoat chuong trinh\n");
                break;
            default:
                printf("Lua chon khong hop le\n");
        }
    } while (choice != 7);

    return 0;
}


