#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFOSIZE 1000

int G_index=0;
int found_name=-1;
int phone_exit_validation=-1;
int found_contact=-1;
void check_duplicate_phone(char phone_no[30]);

void add_contact();
void search_contact();
void delete_contact();
void display_all_contacts();
void assign_to_db(char db_name[100],char name[100] );
int char_counter(char my_char[100]);
void recording_to_file();
void loading_file();
void compare_two_name(char search_name[100],char db_name[100]);

struct info{
    char name[100];
    char phone_no[30];
};
struct info db[INFOSIZE];

int main() {
    int choice=0;
    loading_file();
    while(1){
        printf("Contact Management System \n");
        printf("1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Delete Contact\n");
        printf("4. Display All Contacts\n");
        printf("5. Exit\n");
        printf("Enter Your Choice:");
        scanf("%d",&choice);

        switch (choice) {
            case 1:
                add_contact();
                break;
            case 2:
                search_contact();
                break;
            case 3:
                delete_contact();
                break;
            case 4:
                display_all_contacts();
                break;
            case 5:
                printf("Exiting program...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
void add_contact(){
    char name[100];
    char phone_no[30];
    getchar();
    printf("Enter Name:");
    fgets(name,sizeof (name),stdin);
    name[strcspn(name, "\n")] = '\0';
    printf("Enter Phone Number:");
    fgets(phone_no,sizeof (phone_no),stdin);
    phone_no[strcspn(phone_no, "\n")] = '\0';
    phone_exit_validation=-1;
    check_duplicate_phone(phone_no);
    if(phone_exit_validation!=-1){
        assign_to_db(db[G_index].name,name);
        assign_to_db(db[G_index].phone_no,phone_no);
        G_index++;
        recording_to_file();
        printf("Contact Added Successfully! \n\n");
    }else{
        printf("This contact is already exist.\n\n");
    }
}
void search_contact(){
    char search_name[100];
    int found=0;
    if(G_index==0){
        printf("There is no data to search!\n\n");
    }else{
        getchar();
        found_name=-1;
        printf("Enter Name to search :");
        fgets(search_name, sizeof(search_name), stdin);
        search_name[strcspn(search_name, "\n")] = '\0';
        for(int i=0;i<G_index;i++){
            compare_two_name(search_name,db[i].name);
            if(found_name==1){
                printf("Contact Found:\n");
                printf("Name : %s \n",db[i].name);
                printf("Phone : %s \n\n",db[i].phone_no);
                found=1;
                break;
            }
        }
        if(found==0){
            printf("Contact is not found.\n\n");
        }
    }
}
void delete_contact(){
    char delete_name[100];
    int found=0;
    if(G_index==0){
        printf("There is no data to delete.\n\n");
    }else{
        getchar();
        found_name=-1;
        printf("Enter name to delete :");
        fgets(delete_name, sizeof(delete_name), stdin);
        delete_name[strcspn(delete_name, "\n")] = '\0';
        for(int i=0;i<G_index;i++){
            compare_two_name(delete_name,db[i].name);
            if(found_name==1){
                for(int d=i;d<G_index-1;d++){
                    assign_to_db(db[d].name,db[d+1].name);
                    assign_to_db(db[d].phone_no,db[d+1].phone_no);
                }
                G_index--;
                found=1;
                printf("Contact deleted successfully! \n\n");
            }
        }
        if(found==0){
            printf("Error:Contact not found.! \n\n");
        }else{
            recording_to_file();
        }
    }

}
void display_all_contacts(){
    if(G_index==0){
        printf("There is not data to show. \n\n");
    }else{
            printf("Contact List\n");
            printf("--------------------------------\n");
            for(int contact=0;contact<G_index;contact++){
                printf("Name :%s \n",db[contact].name);
                printf("Phone :%s \n",db[contact].phone_no);
            }
            printf("--------------------------------\n\n");
    }
}
void check_duplicate_phone(char phone_no[30]){
    int phone_count=char_counter(phone_no);
    int found=0;
    for(int i=0;i<G_index;i++){
        int same_count=0;
        int db_phone_count= char_counter(db[i].phone_no);
        if(db_phone_count==phone_count){
            for(int n=0;n<phone_count;n++){
                if(phone_no[n]!=db[i].phone_no[n]){
                    break;
                }
                same_count++;
            }
        }
        if(phone_count==same_count){
            phone_exit_validation=-1;
            found=1;
            break;
        }
    }
    if(found==0){
        phone_exit_validation = 1;
    }
}
void assign_to_db(char db_name[100],char assign[100]){
    // strcpy(db_name, assign);
    int i = 0;
    while(assign[i] != '\0'){
        db_name[i] = assign[i];
        i++;
    }
    db_name[i] = '\0';
}
int char_counter(char my_char[100]){
    int count=0;
    for(int i=0;i<100;i++){
        if(my_char[i]=='\0'){
            break;
        }
        count++;
    }
    return count;
}
void recording_to_file(){
   FILE *fptr=fopen("Contact_List.txt","w");
   if(fptr==NULL){
       printf("File cannot open!\n");
   }else{
       for(int i=0;i<G_index;i++){
           if(strlen(db[i].name) > 0 && strlen(db[i].phone_no) > 0){
               fprintf(fptr, "%s,%s\n", db[i].name, db[i].phone_no);
          }
       }
   }
    fclose(fptr);
}
void loading_file(){
    FILE *fptr=fopen("Contact_List.txt","r");
    if(fptr==NULL){
        printf("File cannot open!\n");
    }else{
        int count = 0;
        char line[256];
        while (fgets(line, sizeof(line), fptr) != NULL) {
            count++;
        }
        rewind(fptr);
        G_index = 0;
        for(int i=0;i<count;i++){
            fscanf(fptr, " %99[^,],%s\n", db[i].name, &db[i].phone_no);
            G_index++;
        }
    }
    fclose(fptr);
}
void compare_two_name(char search_name[100],char db_name[100]){
    int search_counter= char_counter(search_name);
    int db_counter= char_counter(db_name);
    int same_counter=0;
    if(search_counter==db_counter){
        for(int i=0;i<search_counter;i++){
            if(search_name[i]!=db_name[i]){
                break;
            }else{
                same_counter++;
            }
        }
        if(same_counter==search_counter){
            found_name=1;
        }

    }else{
        found_name=-1;
    }
}
