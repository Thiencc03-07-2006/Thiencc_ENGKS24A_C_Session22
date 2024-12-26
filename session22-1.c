#include <stdio.h>
#include <string.h>

struct Student{
    int id;
    char name[50];
    int age;
};

struct Student students[100];

struct Student save;

int n=0;

void loadStudents();

void saveStudents();

void printStudents();

void addStudent();

void updateStudent();

void deleteStudent();

void searchStudent();

void sortStudents();

int main(){
    loadStudents();
    int type;
    do{
        printf("\nMENU\n");
        printf("1. In danh sach sinh vien\n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. Tim kiem sinh vien\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d",&type);
        fflush(stdin);
        switch(type){
            case 1:
                printStudents();
                break;
            case 2:
                addStudent();
                break;
            case 3:
                updateStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                searchStudent();
                break;
            case 6:
                sortStudents();
                break;
        }
    }while(type!=7);
    return 0;
}

void loadStudents(){
    FILE *fptr=fopen("students.bin","rb");
    if(fptr){
        fread(&n,sizeof(int),1,fptr);
        fread(students,sizeof students,n,fptr);
        fclose(fptr);
    }
}

void saveStudents(){
    FILE *fptr=fopen("students.bin","wb");
    fwrite(&n,sizeof(int),1,fptr);
    fwrite(students,sizeof students,n,fptr);
    fclose(fptr);
}

void printStudents(){
    int i=0;
    while(i<n){
        printf("id: %d/ten: %s/tuoi: %d\n",students[i].id,students[i].name,students[i].age);
        i++;
    }
}

void addStudent(){
    printf("Nhap id: ");
    scanf("%d",&save.id);
    fflush(stdin);
    printf("Nhap ten: ");
    fgets(save.name,50,stdin);
    save.name[strcspn(save.name,"\n")]='\0';
    printf("Nhap tuoi: ");
    scanf("%d",&save.age);
    students[n]=save;
    n++;
    saveStudents();
}

void updateStudent(){
    int id;
    printf("Nhap id sinh vien can sua: ");
    scanf("%d",&id);
    fflush(stdin);
    int i=0;
    while(i<n){
        if(students[i].id==id){
            printf("Nhap ten: ");
            fgets(students[i].name,50,stdin);
            students[i].name[strcspn(students[i].name,"\n")]='\0';
            printf("Nhap tuoi: ");
            scanf("%d",&students[i].age);
            saveStudents();
            return;
        }
        i++;
    }
}

void deleteStudent(){
    int id;
    printf("Nhap id sinh vien can xoa: ");
    scanf("%d",&id);
    fflush(stdin);
    int i=0;
    while(i<n){
        if(students[i].id==id){
        	int j=i;
            while(j<n-1){
                students[j]=students[j+1];
                j++;
            }
            n--;
            saveStudents();
            return;
        }
        i++;
    }
}

void searchStudent() {
    char name[50];
    printf("Nhap ten sinh vien can tim: ");
    fgets(name,50,stdin);
    name[strcspn(name,"\n")]='\0';
    int i = 0;
    while(i<n){
        if(strcmp(students[i].name,name)==0){
            printf("id: %d, ten: %s, tuoi: %d\n",students[i].id,students[i].name,students[i].age);
        }
        i++;
    }
}

void sortStudents(){
    int i=0,j;
    while(i<n-1){
        j=i+1;
        while(j<n){
            if(students[i].id>students[j].id){
                save=students[i];
                students[i]=students[j];
                students[j]=save;
            }
            j++;
        }
        i++;
    }
    saveStudents();
}
