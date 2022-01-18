//NAME : DOHA MUTAZ HMEID
//ID :1190120
//SECTION :2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define S 100

struct node{
   char statement[S];
   struct node* link;
};

struct node *top = NULL;
//i made another stack it holds same elements in the original stack but
//in the reverse order and i used it to print the original stack from
//bottom to top as required
struct node *top2 = NULL;

void push(char s[S]);
void pop();
//this second push function to add elements to the second stack
void push2(struct node*);
void printStack();
void writeInFile();

int main()
{
    int count =0 ;
    char stat[S]; //to hold statements entered by the user
    char s[S]; //to hold the last undo statement

    while(1){

        printf("\nenter a statement: ");
          gets(stat);

        if(strcmp(stat , "undo") == 0){
                strcpy(s,top->statement);
                pop();
                count++;
        }

        else if(strcmp(stat , "redo") == 0){
                if(count == 0)
                    printf("YOU DID NOT REMOVE ANY STATEMENT YET");
                else
                    push(s);
        }

        else if(strcmp(stat , "print") == 0){
                printStack();
        }

        else if(strcmp(stat , "save") == 0){
                writeInFile();
        }

        else if(strcmp(stat , "quit") == 0){
                printf("Good Bye!");
                exit(0);
        }

        else{
               push(stat);
        }
    }
    return 0;
}

void push(char s[S]){

struct node* temp;
temp = (struct node*)malloc(sizeof(struct node));
strcpy(temp->statement, s);
temp->link =top;
top = temp;
}

void pop(){

struct node* temp;
if(top == NULL)
    printf("\nTHERE IS NO STATEMENTS IN THE STACK\n");
else{
    temp = top;
    //printf("ELEMENT %s" , temp->statement);
    top = top->link;
    temp->link = NULL;
    free(temp);
}
}

void push2(struct node* tempp){
struct node* temp;
temp = (struct node*)malloc(sizeof(struct node));
strcpy(temp->statement , tempp->statement);
temp->link =top2;
top2 = temp;
}
void printStack(){

    struct node *temp,*temp2;
    if(top == NULL)
        printf("\nTHE STACK IS EMPTY\n");

    else{
        temp = top;
        printf("\nHERE ARE THE STATEMENTS IN THE STACK\n\n");
        while(temp != NULL){
              push2(temp);
              temp =temp->link;
        }
        temp2 = top2;
        while(temp2 != NULL){
          puts(temp2->statement); //printf("%s\n" , temp2->statement);
            temp2 =temp2->link;
        }
    }
    top2 = NULL;
}

void writeInFile(){
FILE *out;
out = fopen("output.txt","w");
struct node *temp,*temp2;
if(top == NULL){
     printf("\nTHE STACK IS EMPTY\n");
}
else{
temp = top;
        while(temp != NULL){
              push2(temp);
              temp =temp->link;
        }
        temp2 = top2;
        while(temp2 != NULL){
                fprintf(out,"%s\n" , temp2->statement);
                temp2 =temp2->link;
        }
    }
    top2 = NULL;
    fclose(out);
}
