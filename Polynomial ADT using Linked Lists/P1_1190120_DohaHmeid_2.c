//NAME : DOHA MUTAZ HMEID
//ID : 1190120
//SECTION : 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define S 30

struct node{
  int coefficient;
  int exponent;
  struct node* left;
  struct node* right;
};
//i made 3 doubly linked lists , each list stores one equation
struct node *root1 = NULL ,*root2 = NULL, *root3 = NULL;

void readFile();
void insertChar(char *a ,char ch , int p);
void printLists(struct node *);
void show();
void polyAdd(struct node* ,struct node * ,struct node *);
void polyMul(struct node* ,struct node* ,struct node*);
void removeNode(struct node *);
void writeInFile(int , int, int);
int printAndEvaluate(struct node * ,int );

int main()
{
    struct node *resultRoot1 = NULL;
    resultRoot1=(struct node *)malloc(sizeof(struct node));
    struct node *addResultRoot2 = NULL;
    addResultRoot2 = (struct node *)malloc(sizeof(struct node));
    struct node *subResultRoot2 = NULL;
    subResultRoot2=(struct node *)malloc(sizeof(struct node));
    struct node *mulResultRoot2 = NULL;
    mulResultRoot2=(struct node *)malloc(sizeof(struct node));

    int x ,addAnswer =0,subAnswer =0 ,mulAnswer =0, number,c=0;
    while(1){

    printf("\nSelect an option: \n");
    printf("  1.Read File\n");
    printf("  2.Show equations\n");
    printf("  3.Addition operation\n");
    printf("  4.Subtraction operation\n");
    printf("  5.Multiplication operation\n");
    printf("  6.Store the results of all operations in a file\n");
    printf("  7.Exit\n");
    if(c==0)
    printf("NOTE : YOU MUST READ THE FILE (OPTION 1) BEFORE SELECTING ANY OTHER OPTION\n");
    c++;
    scanf("%d",&number);

    switch(number){

    case 1: readFile();
            printf("Reading the file is done successfully\n");
            break;

    case 2: show();
            break;

    case 3:
            polyAdd(resultRoot1 , root1 , root2);
            polyAdd(addResultRoot2 , root3 , resultRoot1 );
            //if i wanted to check the list elements use printLists(addResultRoot2);
            printf("Addition operation is done , here is the resulting equation:  ");
            addAnswer = printAndEvaluate(addResultRoot2,addAnswer);
            break;

    case 4:
            polySub(resultRoot1 , root1 , root2);
            polySub(subResultRoot2 , resultRoot1 , root3 );
           //if i wanted to check the list elements use printLists(subResultRoot2);
            printf("\nSubtraction operation is done , here is the resulting equation:  ");
            subAnswer = printAndEvaluate(subResultRoot2,subAnswer);
            break;

    case 5:
            polyMul(resultRoot1, root1 , root2);
            polyMul(mulResultRoot2 , resultRoot1 , root3 );
            //printLists(mulResultRoot2);
            printf("\nMultiplication operation is done , here is the resulting equation:  ");
            removeNode(mulResultRoot2);
            mulAnswer = printAndEvaluate(mulResultRoot2,mulAnswer);
            break;

    case 6: writeInFile(addAnswer,subAnswer,mulAnswer);
            printf("DONE\n");
            break;

    case 7: exit(0);
            break;

    default : printf("you entered a wrong number (Invalid number) \n");
    }
    }
    return 0;
}

void readFile(){

    FILE *in;
    in = fopen("equations.txt","r");
    if(in==NULL){//or if(!in)
       printf("can't open the file\n");
       exit(1);
    }
    else{
        printf("file opened successfully\n");
        struct node* temp1 ;
        struct node* temp2 ;
        struct node* temp3 ;
        temp1=(struct node*)malloc(sizeof(struct node));
        temp2=(struct node*)malloc(sizeof(struct node));
        temp3=(struct node*)malloc(sizeof(struct node));

        char line[S],p1[S]; char *p2;
        int count =0;
        while(fgets ( line, sizeof(line), in ) != NULL ){
            //printf(line);  puts(line);
            count++;
            strcpy(p1,line);

            //INSERTING + BEFORE EVERY -
            for(int i=1 ; i<=strlen(p1);i++){
            if(p1[i] == '-'){
               insertChar(p1,'+',(i));
               i=i+1;
             }
           }
           insertChar(p1,'+',0);

           //MAKING SURE THAT ALL COEFFICENTS ARE IN THE EQUATION AND INSERTING 1 AS A COEFFICIEN WHEN THERE IS NO ONE EXAMPLE: x+3x becomes 1x+3x
         for(int i=0 ; i<=strlen(p1);i++){
                if(p1[i] == '+' && p1[i+1] == 'x' )
                insertChar(p1,'1',(i+1));

                else if(p1[i] == '+' && p1[i+1] == '-' && p1[i+2] == 'x')
                insertChar(p1,'1',(i+2));
            }
            //DIVIDING EACH EQUAION BASED ON THE + SIGN
           p2 = strtok(p1,"+");

            while(p2 != NULL){
               int h=0;
           for(int j=0 ; j<strlen(p2) ; j++ ){
                    if (p2[j] == 'x')
                     h++;}

           for(int i=0 ; i<strlen(p2);i++){
                if(p2[i] == 'x'){
            int c=0;
            char f[strlen(p2)];
            while(c<i){
                f[c]= p2[1+c-1];
                c++;
            }
            f[c] ='\0';
            if(count == 1)
             temp1->coefficient = atoi(f);
             else if (count == 2)
                temp2->coefficient = atoi(f);
             else if(count == 3)
                temp3->coefficient = atoi(f);
                }
             else if(h==0){
               int cc=0;
               char ff[strlen(p2)];
               while(cc<5){
                ff[cc]= p2[1+cc-1];
                cc++;
            }
               ff[cc] ='\0';
               if(count == 1)
                  temp1->coefficient = atoi(ff);
               else if (count == 2)
                 temp2->coefficient = atoi(ff);
               else if(count == 3)
                temp3->coefficient = atoi(ff);
             }
                 if(p2[i] == 'x' && p2[i+1] == '^'){
                     if(count == 1)
                       temp1->exponent =(p2[i+2]-'0');
                    else if (count == 2)
                       temp2->exponent =(p2[i+2]-'0');
                    else if(count == 3)
                       temp3->exponent =(p2[i+2]-'0');
                 }

                 else if (p2[i] == 'x' && p2[i+1] != '^')
                 {
                      if(count == 1)
                       temp1->exponent =1;
                    else if (count == 2)
                       temp2->exponent =1;
                    else if(count == 3)
                       temp3->exponent =1;
                 }
                 else if(h==0){
                    if(count == 1)
                        temp1->exponent =0;
                    else if (count == 2)
                        temp2->exponent =0;
                    else if(count == 3)
                        temp3->exponent =0;
                 }
           }
           //INSERTING ELEMENRTS TO EACH LINKED LIST
           if(count == 1){
                    //IF I WANT TO CHECK ELEMENS BEFORE INSERTING THEM USE : printf("coeff:%d  exp:%d\n",temp1->coefficient, temp1->exponent);
                       temp1->left=NULL;
                       temp1->right=NULL;

                      if(root1 == NULL ){
                        root1 =temp1;
                      }
                      else{
                         struct node *t;
                         t =root1;
                         while(t->right != NULL){
                              t = t->right;
                                   }
                          t->right=temp1;
                          temp1->left=t;
                       }
                        temp1=(struct node*)malloc(sizeof(struct node));

           }
           else if (count == 2){
                   //    printf("coeff:%d  exp:%d\n",temp2->coefficient, temp2->exponent);
                       temp2->left=NULL;
                       temp2->right=NULL;

                      if(root2 == NULL)
                        root2 =temp2;
                      else{
                         struct node *t;
                         t =root2;
                         while(t->right != NULL){
                              t = t->right;
                                   }
                          t->right=temp2;
                          temp2->left=t;
                       }
                         temp2=(struct node*)malloc(sizeof(struct node));
           }
           else if(count == 3){
                    //   printf("coeff:%d  exp:%d\n",temp3->coefficient, temp3->exponent);
                       temp3->left=NULL;
                       temp3->right=NULL;

                      if(root3 == NULL)
                        root3 =temp3;
                      else{
                         struct node *t;
                         t =root3;
                         while(t->right != NULL){
                              t = t->right;
                                   }
                          t->right=temp3;
                          temp3->left=t;
                       }
                         temp3=(struct node*)malloc(sizeof(struct node));
                        }
            p2 = strtok(NULL,"+");
            }
}
}
/* JUST TO CHECK THAT ELEMENTS ARE INSERTED CORRECTLY TO THE LISTS
printf("\nLIST 1 \n");
printLists(root1);
printf("\nLIST 2 \n");
printLists(root2);
printf("\nLIST 3 \n");
printLists(root3);*/
fclose(in);
}

//THIS FUNCTION TO ADD A CHARACTER IN A STRING , I USED IT IN READFILE FUNCTION
void insertChar(char *a ,char ch , int p){
int i = strlen(a) ;
if(p>=0 && p<=i){
  for( ; i>=p ; i--)
    a[i+1]=a[i];
   a[p] =ch;
}
else
    printf("invalid index position");
}

//THIS FUCTION PRINTS A LIST'S ELEMENTS . I USED IT TO CHECK LIST'S ELEMENTS DURING THE PROJECT
void printLists( struct node *root){
struct node* t = root;
if(t == NULL)
  printf("THE LIST IS EMPTY");
else{
    int i = 1;
    while(t != NULL){
      printf("coefficient%d = %d\t exponent%d = %d \n" ,i, t->coefficient ,i,t->exponent);
       i++;
      t = t->right;
    }
    }
}

//THIS FUCTION PRINTS THE EQUATIONS TO THE USER
void show(){
FILE *in;
    in = fopen("equations.txt","r");
    if(in==NULL){
       printf("can't open the file\n");
       exit(1);
    }
    else{
        char line[S];
        printf("\nHere are the equations:\n");
        while(fgets ( line, sizeof(line), in ) != NULL )
            printf(line); // puts(line);
            printf("\n");
}
fclose(in);
}

//THIS FUCTION ADDS 2 LIST (EQUATIONS) AND STORES THE RESULT IN ANOTHER LIST
void polyAdd(struct node *result ,struct node *polyy1 ,struct node *polyy2){
   struct node* poly1 = polyy1;
   struct node* poly2 = polyy2;

while(poly1->right!=NULL && poly2->right!=NULL ){

    if(poly1->exponent > poly2->exponent){
            result->coefficient = poly1->coefficient;
            result->exponent = poly1->exponent;
            poly1 = poly1->right ;
    }
    else if (poly1->exponent < poly2->exponent){
            result->coefficient = poly2->coefficient;
            result->exponent = poly2->exponent;
            poly2 = poly2->right ;
    }
    else {
            result->exponent = poly1->exponent;
            result->coefficient = poly1->coefficient + poly2->coefficient;
            poly1 = poly1->right ;
            poly2 = poly2->right ;
    }
        result->right=(struct node *)malloc(sizeof(struct node));
        result->right->left = result->right;
        result=result->right;
        result->right=NULL;
}
while(poly1->right!=NULL || poly2->right!=NULL){
        if(poly1->right!=NULL){
            result->coefficient = poly1->coefficient;
            result->exponent = poly1->exponent;
            poly1 = poly1->right ;
        }
        if(poly2->right !=NULL){
            result->coefficient = poly2->coefficient;
            result->exponent = poly2->exponent;
            poly2 = poly2->right ;
        }
        result->right=(struct node *)malloc(sizeof(struct node));
        result->right->left = result->right;
        result=result->right;
        result->right=NULL;
}

if(poly1->right==NULL && poly2->right==NULL ){

    if(poly1->exponent > poly2->exponent){
            result->coefficient = poly1->coefficient;
            result->exponent = poly1->exponent;
    }

    else if (poly1->exponent < poly2->exponent){
            result->coefficient = poly2->coefficient;
            result->exponent = poly2->exponent;
    }

    else {
            result->exponent = poly1->exponent;
            result->coefficient = poly1->coefficient + poly2->coefficient;
    }
}
}

//THIS FUCTION SUBTRACTS 2 LIST (EQUATIONS) AND STORES THE RESULT IN ANOTHER LIST
void polySub(struct node *result ,struct node *polyy1 ,struct node *polyy2){

   struct node* poly1 = polyy1;
   struct node* poly2 = polyy2;

while(poly1->right!=NULL && poly2->right!=NULL ){

    if(poly1->exponent > poly2->exponent){
            result->coefficient = poly1->coefficient;
            result->exponent = poly1->exponent;
            poly1 = poly1->right ;
    }

    else if (poly1->exponent < poly2->exponent){
            result->coefficient = -1 * poly2->coefficient;
            result->exponent = poly2->exponent;
            poly2 = poly2->right ;
    }

    else {
            result->exponent = poly1->exponent;
            result->coefficient = poly1->coefficient - poly2->coefficient;
            poly1 = poly1->right ;
            poly2 = poly2->right ;
    }
        result->right=(struct node *)malloc(sizeof(struct node));
        result->right->left = result->right;
        result=result->right;
        result->right=NULL;
}

while(poly1->right!=NULL || poly2->right!=NULL){
        if(poly1->right!=NULL){
            result->coefficient = poly1->coefficient;
            result->exponent = poly1->exponent;
            poly1 = poly1->right ;
        }
        if(poly2->right !=NULL){
            result->coefficient = -1* poly2->coefficient;
            result->exponent = poly2->exponent;
            poly2 = poly2->right ;
        }
        result->right=(struct node *)malloc(sizeof(struct node));
        result->right->left = result->right;
        result=result->right;
        result->right=NULL;
}

if(poly1->right==NULL && poly2->right==NULL ){

    if(poly1->exponent > poly2->exponent){
            result->coefficient = poly1->coefficient;
            result->exponent = poly1->exponent;
    }

    else if (poly1->exponent < poly2->exponent){
            result->coefficient = -1* poly2->coefficient;
            result->exponent = poly2->exponent;
    }

    else {
            result->exponent = poly1->exponent;
            result->coefficient = poly1->coefficient - poly2->coefficient;
    }
}


}

//THIS FUCTION MULTIPLIES 2 LIST (EQUATIONS) AND STORES THE RESULT IN ANOTHER LIST
void polyMul(struct node *result ,struct node *polyy1 ,struct node *polyy2){
   struct node* poly1 = polyy1;
   struct node* poly2 = polyy2;

   while(poly1->right!=NULL){
       while(poly2->right!=NULL ){
           result->coefficient = poly1->coefficient * poly2->coefficient;
           result->exponent = poly1->exponent + poly2->exponent;
           poly2 = poly2->right;

           result->right=(struct node *)malloc(sizeof(struct node));
           result->right->left = result->right;
           result=result->right;
           result->right=NULL;
       }

       if(poly2->right==NULL){
           result->coefficient = poly1->coefficient * poly2->coefficient;
           result->exponent = poly1->exponent + poly2->exponent;
           result->right=(struct node *)malloc(sizeof(struct node));
           result->right->left = result->right;
           result=result->right;
           result->right=NULL;
       }

           poly2 = polyy2;
           poly1 = poly1->right;
   }

     if(poly1->right==NULL){
       while(poly2->right!=NULL ){
           result->coefficient = poly1->coefficient * poly2->coefficient;
           result->exponent = poly1->exponent + poly2->exponent;
           poly2 = poly2->right;

           result->right=(struct node *)malloc(sizeof(struct node));
           result->right->left = result->right;
           result=result->right;
           result->right=NULL;
       }
       if(poly2->right==NULL){
           result->coefficient = poly1->coefficient * poly2->coefficient;
           result->exponent = poly1->exponent + poly2->exponent;
           result->right=NULL;
      }
     }
}

//THIS FUCTION IS USED TO REMOVE THE NODES WITH THE SAME EXPONENT AND ADDING THEIR COEFFCIENTS TO THE FIRST SIMILAR EXPONENT NODE
//I USED IT IN THE MULTIPLY FUNCTION
void removeNode(struct node* root){
    struct node *p1, *p2, *n;
    p1 = root;
    while(p1!=NULL ){
        p2 = p1;
        while(p2->right !=NULL){
            if(p1->exponent == p2->right->exponent) {
                p1->coefficient = p1->coefficient + p2->right->coefficient;
                n = p2->right;
                p2->right = p2->right->right;
                n->right->left = p1;
                n->right =NULL;
                n->left = NULL;
                free(n);
            }
            else
                p2 = p2->right;
        }
        p1 = p1->right;
    }
}

//THIS FUCTION IS USED TO WRITE THE OPEARIONS RESULTS IN A FILE
void writeInFile(int answer1 ,int answer2 ,int answer3){
FILE *out;
out = fopen("results.txt","w");

if(answer1 == 0)
    fprintf(out,"YOU DID NOT IMPLEMENT THE ADDITION OPERATION YET\n");
else
    fprintf(out,"THE ADDITION OPERATION RESULT = %d\n" ,answer1);

if(answer2 == 0)
    fprintf(out,"YOU DID NOT IMPLEMENT THE SUBTRACTION OPERATION YET\n");
else
    fprintf(out,"THE SUBTRACTION OPERATION RESULT = %d\n" ,answer2);

if(answer3 == 0)
    fprintf(out,"YOU DID NOT IMPLEMENT THE MULTIPLICATION OPERATION YET\n");
else
    fprintf(out,"THE MULTIPLICATION OPERATION RESULT = %d\n" ,answer3);

fclose(out);
}

//to print equations and evaluate the value in them
int printAndEvaluate(struct node * a ,int answer){
            //to print the resulting equation
            int x;
            struct node *p ;
            for(p = a ; p!=NULL ; p = p->right){
                printf("%dx^%d " , p->coefficient , p->exponent);
                if(p->right !=NULL)
                    printf("+ ");
            }

            printf("\nEnter a value of the variables x to substitute in the equation :  ");
            scanf("%d" , &x);
            //to substitue x in the equation
            for(p = a ; p!=NULL ; p=p->right){
                answer += p->coefficient * (pow(x,p->exponent));
            }
            printf("The answer when x= %d is %d\n" ,x, answer);

return answer;
}
