#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFOSIZE 1000

int G_index=0;
int found_name=-1;

void add_word();
void display_word();
void search_word();
void delete_word();
void update_definition();
void assign_to_db(char db_name[100],char name[100] );
int char_counter(char my_char[100]);
void recording_to_file();
void loading_file();
void compare_two_name(char search_name[100],char db_name[100]);

struct word{
    char word[100];
    char definition[500];
};
struct word db[INFOSIZE];

int main() {
    loading_file();
    int choice=0;
    while (1){
        printf("Dictionary Application!\n");
        printf("1. Add Word\n");
        printf("2.Display Words\n");
        printf("3.Search Word\n");
        printf("4.Delete Word\n");
        printf("5.Update Definition\n");
        printf("6. Exit\n");
        printf("Enter Your Choice:");
        scanf("%d",&choice);

        switch (choice) {
            case 1:
                add_word();
                break;
            case 2:
                display_word();
                break;
            case 3:
                search_word();
                break;
            case 4:
                delete_word();
                break;
            case 5:
                update_definition();
                break;
            case 6:
                printf("Exiting program...\n");
                exit(0);
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
void add_word(){
    char word[100];
    char definition[500];
    getchar();
    printf("Enter Word:");
    fgets(word,sizeof (word),stdin);
    word[strcspn(word, "\n")] = '\0';
    printf("Enter Definition:");
    fgets(definition,sizeof (definition),stdin);
    definition[strcspn(definition, "\n")] = '\0';

    assign_to_db(db[G_index].word,word);
    assign_to_db(db[G_index].definition,definition);

    G_index++;
    recording_to_file();
    printf("Word Added Successfully! \n\n");
}
void search_word(){
    char search_word[100];
    int found=0;
    if(G_index==0){
        printf("There is no data to search!\n\n");
    }else{
        getchar();
        printf("Enter word to search :");
        fgets(search_word, sizeof(search_word), stdin);
        search_word[strcspn(search_word, "\n")] = '\0';
        for(int i=0;i<G_index;i++){
            compare_two_name(search_word,db[i].word);
            if(found_name==1){
                printf("Definition of %s :%s \n\n",db[i].word,db[i].definition);
                found=1;
                break;
            }
        }
        if(found==0){
            printf("%s is not found.\n\n",search_word);
        }
    }
}
void delete_word(){
    char delete_word[100];
    int found=0;
    if(G_index==0){
        printf("There is no data to delete.\n\n");
    }else{
        getchar();
        found_name=-1;
        printf("Enter name to delete :");
        fgets(delete_word, sizeof(delete_word), stdin);
        delete_word[strcspn(delete_word, "\n")] = '\0';
        for(int i=0;i<G_index;i++){
            compare_two_name(delete_word,db[i].word);
            if(found_name==1){
                for(int d=i;d<G_index-1;d++){
                    assign_to_db(db[d].word,db[d+1].word);
                    assign_to_db(db[d].definition,db[d+1].definition);
                }
                G_index--;
                found=1;
                printf("Word '%s' deleted successfully! \n\n",delete_word);
            }
        }
        if(found==0){
            printf("Error:'%s' not found.! \n\n",delete_word);
        }else{
            recording_to_file();
        }
    }

}
void display_word(){
    if(G_index==0){
        printf("There is not data to show. \n\n");
    }else{
        FILE *fptr=fopen("Dictionary_Data.txt","r");
        if(fptr==NULL){
            printf("File Can't Open!\n\n");
        }else{
            printf("%-20s %-40s\n", "Word", "Definition");
            printf("------------------------------------------------------------\n");
            for(int contact=0;contact<G_index;contact++){
                printf("%-20s %-40s\n", db[contact].word, db[contact].definition);
            }
            printf("------------------------------------------------------------\n\n");
        }
    }
}
void update_definition(){
    char update_word[100];
    char update_def[500];
    int found=0;
    getchar();
    printf("Enter Word:");
    fgets(update_word,sizeof (update_word),stdin);
    update_word[strcspn(update_word, "\n")] = '\0';
    printf("Enter Definition:");
    fgets(update_def,sizeof (update_def),stdin);
    update_def[strcspn(update_def, "\n")] = '\0';

    update_word[strcspn(update_word, "\n")] = '\0';
    for(int i=0;i<G_index;i++){
        compare_two_name(update_word,db[i].word);
        if(found_name==1){
                assign_to_db(db[i].definition,update_def);
            found=1;
            printf("Word '%s' update successfully! \n\n",update_word);
        }
    }
    if(found==0){
        printf("Error:'%s' not found.!\n \n",update_word);
    }else {
        recording_to_file();
    }
}
void assign_to_db(char db_word[500],char assign[500]){
    int i = 0;
    while(assign[i] != '\0'){
        db_word[i] = assign[i];
        i++;
    }
    db_word[i] = '\0';
}
int char_counter(char my_char[500]){
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
    FILE *fptr=fopen("Dictionary_Data.txt","w");
    if(fptr==NULL){
        printf("File cannot open!");
    }else{
        for(int i=0;i<G_index;i++){
            printf("This is check %s|%s", db[i].word, db[i].definition);
            fprintf(fptr, "%s|%s\n", db[i].word, db[i].definition);
        }
    }
    fclose(fptr);
}
void loading_file(){
    FILE *fptr=fopen("Dictionary_Data.txt","r");
    if(fptr==NULL){
        printf("File cannot open!\n\n");
    }else{
        int count = 0;
        char line[256];
        while (fgets(line, sizeof(line), fptr) != NULL) {
            count++;
        }
        rewind(fptr);

        G_index = 0;
        for(int i=0;i<count;i++){
            fscanf(fptr, " %99[^|]|%199[^\n]\n", db[i].word, &db[i].definition);
            G_index++;
        }
    }
    fclose(fptr);
}
void compare_two_name(char search_word[100],char db_word[100]){
    int search_counter= char_counter(search_word);
    int db_counter= char_counter(db_word);
    int same_counter=0;
    if(search_counter==db_counter){
        for(int i=0;i<search_counter;i++){
            if(search_word[i]!=db_word[i]){
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

