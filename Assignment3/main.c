#include <stdio.h>
#include <stdlib.h>
#define BOOKSIZE 2000

void add_book();
void data_assign_to_db(char receiver[200],char assign[200]);
int char_counter(char my_char[200]);
void display_all_book();
void check_book_already(char book_name[200]);
void delete_book();
void search_book();
void compare_two_title_name(char search_title[200],char db_title[200]);

int G_index=0;
int found_title=-1;
int book_exit_validation=-1;

struct book{
    int book_id;
    char book_title[200];
    char author_name[200];
};
struct book db[BOOKSIZE];

int main() {
    int choice=0;
    while (1) {
        printf("Book Management System\n");
        printf("1. Add Book\n");
        printf("2. Delete Book\n");
        printf("3. Search Book\n");
        printf("4. Display All Book\n");
        printf("5. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                add_book();
                break;
            case 2:
                delete_book();
                break;
            case 3:
                search_book();
                break;
            case 4:
                display_all_book();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
void add_book(){
    int book_id=0;
    char book_title[200];
    char author_name[200];

    printf("Enter Book ID :");
    scanf("%d",&book_id);
    getchar();
    printf("Enter Book Title :");
    fgets(book_title, sizeof(book_title), stdin);
    printf("Enter Author Name :");
    fgets(author_name, sizeof(author_name), stdin);

    book_exit_validation=-1;
    check_book_already(book_title);
    if(book_exit_validation!=-1){
        db[G_index].book_id=book_id;
        data_assign_to_db(db[G_index].book_title,book_title);
        data_assign_to_db(db[G_index].author_name,author_name);
        G_index++;
        printf("Book added successfully! \n");
    }else{
        printf("This Book is already exist! \n");
    }
}
void delete_book(){
   int delete_id=0;
   int found=0;
   if(G_index==0){
       printf("No book in the system.\n");
   }else{
       printf("Enter Book ID to delete :");
       scanf("%d",&delete_id);
       for(int i=0;i<G_index;i++){
           if(delete_id==db[i].book_id){
               for(int d=i;d<G_index-1;d++){
                   db[d].book_id=db[d+1].book_id;
                   data_assign_to_db(db[d].book_title,db[d+1].book_title);
                   data_assign_to_db(db[d].author_name,db[d+1].author_name);
               }
               G_index--;
               found=1;
               printf("Book with ID:%d deleted successfully! \n",delete_id);
           }
       }
       if(found==0){
           printf("Error:Book with ID:%d not found.! \n",delete_id);
       }
   }
}
void search_book(){
    char search_name[200];
    int found=0;
    if(G_index==0){
        printf("No book in the system!\n");
    }else{
        getchar();
        printf("Enter Book Title to search :");
        fgets(search_name, sizeof(search_name), stdin);
        for(int i=0;i<G_index;i++){
            compare_two_title_name(search_name,db[i].book_title);
            if(found_title==1){
                printf("Book Found:\n");
                printf("ID : %d \n",db[i].book_id);
                printf("Title : %s \n",db[i].book_title);
                printf("Author : %s \n",db[i].author_name);
                found=1;
                break;
            }
        }
        if(found==0){
            printf("Error:Book with Title %s is not found.\n",search_name);
        }
    }
}
void data_assign_to_db(char receiver[200],char assign[200]){
    int i = 0;
    while(assign[i] != '\0'){
        receiver[i] = assign[i];
        i++;
    }
    receiver[i] = '\0';
}
int char_counter(char my_char[200]){
    int count=0;
    for(int i=0;i<200;i++){
        if(my_char[i]=='\0'){
            break;
        }
        count++;
    }
    return count;
}
void display_all_book(){
    if(G_index==0){
        printf("No book in the system. \n");
    }else{
        for(int book=0;book<G_index;book++){
            printf("ID : %d ,Title : %s, Author : %s ", db[book].book_id,
                   db[book].book_title,
                   db[book].author_name);
            printf("\n");
        }
    }
}
void check_book_already(char book_name[200]){
    int book_char_count=char_counter(book_name);
     int same_count=0;
     int found=0;
    for(int i=0;i<G_index;i++){
        int db_name_count= char_counter(db[i].book_title);
        if(db_name_count==book_char_count){
            for(int n;n<book_char_count;n++){
                if(book_name[n]!=db[i].book_title[n]){
                    break;
                }
                same_count++;
            }
        }
        if(book_char_count==same_count){
            book_exit_validation=-1;
            found=1;
            break;
        }
    }
    if(found==0){
        book_exit_validation = 1;
    }
}
void compare_two_title_name(char search_title[200],char db_title[200]){
    int search_counter= char_counter(search_title);
    int db_counter= char_counter(db_title);
    int same_counter=0;
    if(search_counter==db_counter){
        for(int i=0;i<search_counter;i++){
            if(search_title[i]!=db_title[i]){
                break;
            }else{
                same_counter++;
            }
        }
        if(same_counter==search_counter){
         found_title=1;
        }

    }else{
        found_title=-1;
    }
}