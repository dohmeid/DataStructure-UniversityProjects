//  NAME : DOHA HMEID  || ID : 1190120  || SECTION : 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define S 30 //each tree element size
#define Z 150 //each line form a file size
#define SIZE 17 //hash table size

struct AVLnode
{
    char name[S];
    char gender[S];
    char admissionDate[S];
    char birthDate[S];
    char illness[S];
    char address[S];
    char bloodType[S];
    struct AVLnode *left;
    struct AVLnode *right;
    int height;
};
struct AVLnode *root = NULL;

struct hashTable
{
    int state;
    /* state = 0 : Empty /data not present
     * state = 1 : Occupied /some data already present
       state = 2 : Deleted /data was present,but deleted */
    char name[S]; //key
    char gender[S];
    char admissionDate[S];
    char birthDate[S];
    char illness[S];
    char address[S];
    char bloodType[S];
};
struct hashTable *array;

//TREE FUNCTIONS :
struct AVLnode* MakeEmpty(struct AVLnode* T );
int getHeight (struct AVLnode*);
int MAX (int,int);
struct AVLnode* singleRotateLeft(struct AVLnode*);
struct AVLnode* singleRotateRight(struct AVLnode*);
struct AVLnode* doubleRotateLeft(struct AVLnode*);
struct AVLnode* doubleRotateRight(struct AVLnode*);
struct AVLnode* minNode(struct AVLnode*);

void readFile();
struct AVLnode * insert(struct AVLnode*,char data[S]);
void insertFromUser();
void display(struct AVLnode*);
void search(struct AVLnode *t);
struct AVLnode* find(char key[S],struct AVLnode*);
struct AVLnode* deletePatient(struct AVLnode*,char key[S]);
int displaySameIllness(struct AVLnode*,char key[S]);
void write (struct AVLnode*,FILE *f);
void writeInFile(struct AVLnode*);
void hashOperations();

//HASH FUNCTIONS :
int ASCII(char key[S]);
int hashcode(int key);
void initializeArray();
void insertHash(char line[Z]);
void readHash();
void printHash();
void insertHashFromUser();
int searchHash(char key[S]);
void deleteHash(char key[S]);
void writeHash();

int main()
{
 //   root = MakeEmpty(root);
    int number,flag = 0,a,flag2 =0;
    char key[S];
    while(1)
    {
        printf("\nSelect an option: \n");
        printf("  1.Read File Read and load the data\n");
        printf("  2.Insert a new patient with all its associated data\n");
        printf("  3.Find a patient and update his/her information if found\n");
        printf("  4.List all patients in lexicographic order with their associated information\n");
        printf("  5.List all patients that have the same illness\n");
        printf("  6.Delete a patient from the system\n");
        printf("  7.Save all patients in a file\n");
        printf("  8.Create hash table and implement it's operations\n");
        printf("  9.Exit\n");

        if(flag == 0)
            printf(" Note : you should read the file (option 1) before any other operation\n");
        flag = 1;
        scanf("%d",&number);

        switch(number)
        {

        case 1:
            readFile();
            printf("\nReading the file is done successfully\n");
            break;

        case 2:
            insertFromUser();
            break;

        case 3:
            search(root);
            break;

        case 4:
            display(root);
            break;

        case 5:
            printf("ENTER THE ILLNESS YOU WANT TO : ");
            scanf("%s", &key);
            printf("HERE ARE ALL THE PATEINTS THAT HAVE %s :\n", key);
            a = displaySameIllness(root,key);
            if(a == 0)
                printf("THERE IS NO PATEINTS THAT HAVE %s\n", key);
            break;

        case 6:
            printf("ENTER THE NAME OF THE PATIENT YOU WANT TO DELETE: \n");
            scanf("%s", &key);
            deletePatient(root, key);
            break;

        case 7:
            writeInFile(root);
            flag2++;
            printf("DONE\n");
            break;

        case 8:
            if(flag2 == 0)
                printf("MAKE SURE TO SAVE THE PATIENT'S DATA BY CHOOSING OPTION 7 ,THEN TRY AGAIN THIS OPTION\n");
            else
                printf("\n***************************************************************************************************\n");
            printf("***************************************************************************************************\n\n");
            hashOperations();
            break;

        case 9:
            exit(0);
            break;

        default :
            printf("you entered a wrong number (Invalid number) \n");
        }
    }
    return 0;
}

struct AVLnode* MakeEmpty(struct AVLnode* T )
{
    if( T != NULL )
    {
        MakeEmpty( T->left );
        MakeEmpty( T->right );
        free(T);
    }
    return NULL;
}

int getHeight (struct AVLnode* t)
{
    if(t == NULL)
        return -1;
    else
        return t->height;
}

int MAX (int x, int y)
{
    if(x>y)
        return x;
    else
        return y;
}

struct AVLnode* singleRotateLeft(struct AVLnode* x)
{
    struct AVLnode* y;
    y = x->right;
    x->right  = y->left;
    y->left = x;
    x->height = 1 + MAX(getHeight(x->left), getHeight(x->right));
    y->height = 1 + MAX(getHeight(x), getHeight(y->right));
    return y;
}

struct AVLnode* singleRotateRight(struct AVLnode* y)
{
    struct AVLnode* x;
    x = y->left;
    y->left  = x->right;
    x->right = y;
    y->height = 1 + MAX(getHeight(y->right), getHeight(y->left));
    x->height = 1 + MAX(getHeight(y), getHeight(x->left));
    return x;
}

struct AVLnode* doubleRotateLeft(struct AVLnode* K3)
{
    K3->left  = singleRotateLeft(K3->left);
    return singleRotateRight(K3);
}

struct AVLnode* doubleRotateRight(struct AVLnode* K3)
{
    K3->right  = singleRotateRight(K3->right);
    return singleRotateLeft(K3);
}

struct AVLnode* minNode( struct AVLnode* t)
{
    if( t == NULL )
        return NULL;
    else if( t->left == NULL )
        return t;
    else
        return minNode( t->left );
}

void readFile()
{
    FILE *in;
    in = fopen("patients.txt","r");
    if(in == NULL)
    {
        printf("can't open the file\n");
        exit(1);
    }

    else
    {
        printf("file opened successfully\n");
        char line[Z],p1[Z];
        while(fgets ( line, sizeof(line), in ) != NULL )
        {
            //printf(line); // puts(line);
            strcpy(p1, line);
            root = insert(root,p1);
        }
    }
    fclose(in);
}

struct AVLnode* insert(struct AVLnode *t,char data[Z])
{
    char key[S];
    if(t == NULL)
    {
        t = (struct AVLnode*)malloc(sizeof(struct AVLnode));
        char *pp ;
        int i = 1;
        pp = strtok(data,"#");
        strcpy(key, pp);
        while(pp != NULL)
        {
            switch (i)
            {
            case 1:
                strcpy(t->name, pp);
                break;

            case 2:
                strcpy(t->gender, pp);
                break;

            case 3:
                strcpy(t->admissionDate, pp);
                break;

            case 4:
                strcpy(t->birthDate, pp);
                break;

            case 5:
                strcpy(t->illness, pp);
                break;

            case 6:
                strcpy(t->address, pp);
                break;

            case 7:
                strcpy(t->bloodType, pp);
                break;

            default :
                printf("THERE IS SOMETHING WRONG WITH THE DATA ORDER ,PLEASE CHECK THE DATA FILE\n");
            }
            pp = strtok(NULL,"#");
            i++;
        }
        t->height = 0;
        t->left = NULL;
        t->right = NULL;
    }

    else if(strcmp(key, t->name) < 0)
    {
        t->left = insert(t->left,data );
        if(getHeight(t->left) - getHeight(t->right) >= 2)
        {
            if(strcmp(key, t->left->name) < 0)
                t = singleRotateRight(t);
            else
                t = doubleRotateLeft(t);
        }
    }

    else if(strcmp(key, t->name) > 0)
    {
        t->right = insert(t->right, data );
        if(getHeight(t->right) - getHeight(t->left) >= 2)
        {
            if(strcmp(key, t->right->name) > 0)
                t = singleRotateLeft(t);
            else
                t = doubleRotateRight(t);
        }
    }
    t->height = 1 + MAX(getHeight(t->right), getHeight(t->left));
    return t;
}

void insertFromUser()
{
    char name[S],gender[S],admission[S],birth[S],illness[S],address[S],blood[S];
    printf("\n**********INSERT A NEW PATIENT********** ");
    printf("\nENTER PATEINT'S NAME :");
    scanf("%s",&name);
    printf("ENTER PATEINT'S GENDER (F FOR FEMALE AND M FOR MALE) :");
    scanf("%s",&gender);
    printf("ENTER PATEINT'S ADMISSION DATE :");
    scanf("%s",&admission);
    printf("ENTER PATEINT'S BIRTH DATE :");
    scanf("%s",&birth);
    printf("ENTER PATEINT'S ILLNESS :");
    scanf("%s",&illness);
    printf("ENTER PATEINT'S ADDRESS :");
    scanf("%s",&address);
    printf("ENTER PATEINT'S BLOOD TYPE :");
    scanf("%s",&blood);

    char line[Z] = "";
    strcat(line, name);
    strcat(line, "#");
    strcat(line, gender);
    strcat(line, "#");
    strcat(line, admission);
    strcat(line, "#");
    strcat(line, birth);
    strcat(line, "#");
    strcat(line, illness);
    strcat(line, "#");
    strcat(line, address);
    strcat(line, "#");
    strcat(line, blood);
    root = insert(root,line);
    printf("\n*********NEW PATEINT ADDED*********");
}

void search(struct AVLnode *t)
{
    char name[S];
    printf("\n***********************************************************\n");
    printf("ENTER THE NAME OF THE PATEINT YO WANT TO SEARCH ABOUT : ");
    scanf("%s", &name);

    struct AVLnode *p;
    p = find(name, t);

    if(p == NULL)
        printf("THE PATINT YOU ARE LOOKING FOR IS NOT IN THE LIST\n");
    else
    {
        char ans[10];
        printf("THE PATEINT %s FOUND ,DO YOU WANT TO CHANGE ANY DATA FOR HIM/HER ?(YES/NO)\n", p->name);
        scanf("%s", &ans);
        if(strcmp(ans, "NO") == 0 || strcmp(ans, "No") == 0 || strcmp(ans, "no") == 0)
            printf("OK\n");

        else if(strcmp(ans, "YES") == 0 || strcmp(ans, "Yes") == 0 || strcmp(ans, "yes") == 0)
        {
            int n;
            char nname[S], ng[S], ad[S], bd[S], ill[S], add[S], bt[S];
            printf("PICK A NUMBER FOR THE INFORMATION THAT YOU WANT TO CHANGE : \n");
            printf("1.name\n2.gender\n3.admission date\n4.birth date\n5.illness\n6.address\n7.bloodType");
            scanf("%d", &n);
            switch(n)
            {
            case 1:
                printf("enter the new name : \n");
                scanf("%s", &nname);
                strcpy(p->name, nname);
                break;

            case 2:
                printf("enter the new gender (F for female / M for male) : \n");
                scanf("%s", &ng);
                strcpy(p->gender, ng);
                break;

            case 3:
                printf("enter the new admission date : \n");
                scanf("%s", &ad);
                strcpy(p->admissionDate, ad);
                break;

            case 4:
                printf("enter the new birth date : \n");
                scanf("%s", &bd);
                strcpy(p->birthDate, bd);
                break;

            case 5:
                printf("enter the new illness : \n");
                scanf("%s", &ill);
                strcpy(p->illness, ill);
                break;

            case 6:
                printf("enter the new address : \n");
                scanf("%s", &add);
                strcpy(p->address, add);
                break;

            case 7:
                printf("enter the new blood type : \n");
                scanf("%s", &bt);
                strcpy(p->bloodType, bt);
                break;

            default :
                printf("WRONG NUMBER\n");
            }
            printf("DONE \n");
        }
    }
}

struct AVLnode* find(char key[S], struct AVLnode *t)
{
    if(t == NULL)
        return NULL;
    if(strcmp(key, t->name) < 0)
        return find(key, t->left);
    else if(strcmp(key, t->name) > 0)
        return find(key, t->right);
    else
        return t;
}

//to print all patients in lexicographic order with their associated information in order
void display(struct AVLnode* t)
{
    if( t != NULL)
    {
        display(t->left);
        printf("\n name : %s",t->name);
        printf("\n gender : %s",t->gender);
        printf("\n admission date : %s",t->admissionDate);
        printf("\n birth date : %s",t->birthDate);
        printf("\n illness : %s",t->illness);
        printf("\n address : %s",t->address);
        printf("\n blood type : %s",t->bloodType);
        printf("\n********************************************************");
        display(t->right);
    }
}

int displaySameIllness(struct AVLnode* t, char key[S])
{
    int i = 0;
    if(t != NULL)
    {
        displaySameIllness(t->left,key);
        if(strcmp(t->illness, key)== 0)
        {
            printf("%s\n", t->name);
            i++;
        }
        displaySameIllness(t->right,key);
    }
    return i;
}

struct AVLnode* deletePatient(struct AVLnode* t, char key[S])
{
    if (t == NULL)
    {
        return t;
    }

//If the key to be deleted is smaller than the root's key, then it lies in left subtree
    if(strcmp(key, t->name) < 0)
        t->left = deletePatient(t->left, key);

// If the key to be deleted is greater than the root's key, then it lies in right subtree
    else if( strcmp(key, t->name) > 0 )
        t->right = deletePatient(t->right, key);

// if key is same as root's key, then This is the node to be deleted
    else
    {
        // node with only one child or no child
        if( (t->left == NULL) || (t->right == NULL) )
        {
            struct AVLnode *temp = t->left?t->left:t->right;

            // No child case
            if (temp == NULL)
            {
                temp = t;
                t = NULL;
            }
            else // One child case
                *t = *temp; // Copy the contents of the non-empty child

            free(temp);
        }

        else
        {
            // node with two children: Get the inorder successor (smallest in the right subtree)
            struct AVLnode* temp = minNode(t->right);

            // Copy the inorder successor's data to this node
            strcpy(t->name, temp->name);
            strcpy(t->gender, temp->gender);
            strcpy(t->admissionDate, temp->admissionDate);
            strcpy(t->birthDate, temp->birthDate);
            strcpy(t->illness, temp->illness);
            strcpy(t->address, temp->address);
            strcpy(t->bloodType, temp->bloodType);

            // Delete the inorder successor
            t->right = deletePatient(t->right, temp->name);
        }
    }

    // If the tree had only one node then return
    if (t == NULL)
        return t;

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    t->height = 1 + MAX(getHeight(t->left), getHeight(t->right));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether this node became unbalanced)
    int balance = getHeight(t->left) - getHeight(t->right);

    // If this node becomes unbalanced, then there are 4 cases
    // Left Left Case
    if ( balance > 1 && (getHeight(t->left->left) - getHeight(t->left->right))>= 0 )
        return singleRotateRight(t);

    // Left Right Case
    if ( balance > 1 && (getHeight(t->left->left) - getHeight(t->left->right)) < 0 )
    {
        t->left =  singleRotateLeft(t->left);
        return singleRotateRight(t);
    }

    // Right Right Case
    if ( balance < -1 && (getHeight(t->right->left) - getHeight(t->right->right)) <= 0 )
        return singleRotateLeft(t);

    // Right Left Case
    if ( balance < -1 && (getHeight(t->right->left) - getHeight(t->right->right)) > 0 )
    {
        t->right = singleRotateRight(t->right);
        return singleRotateLeft(t);
    }
    return t;
}

void write (struct AVLnode *t,FILE *f)
{
    if(t->left )
        write(t->left,f);

    fprintf(f,"%s,%s,%s,%s,%s,%s,%s",t->name,t->gender,t->admissionDate,t->birthDate,t->illness,t->address,t->bloodType);
    if(t->right )
        write(t->right,f);
}

void writeInFile(struct AVLnode* t)
{
    FILE *out;
    out = fopen("patients_hash.data","w");
    write(t,out);
    fclose(out);
}

//***********************************************************************************************************************************************************************
//***************************************************************** DOWN BELOW ARE THE HASH FUNCTIONS ********************************************************************

//to return the ASCII value of a string
int ASCII(char key[S])
{
    int i=0, sum=0;
    while (key[i] )  // or while(key[i] != '\0')
    {
        sum += key[i];
        i++;
    }
    return sum;
}

//note : here the key is key = ASCII(name);
int hashcode(int key)
{
    return (key % SIZE);
}

void initializeArray()
{
    array = (struct hashTable*) malloc(SIZE*sizeof(struct hashTable*));
    for(int i =0 ; i<SIZE ; i++)
    {
        array[i].state = 0; //empty state
        strcpy(array[i].name,"");
        strcpy(array[i].gender,"");
        strcpy(array[i].admissionDate,"");
        strcpy(array[i].birthDate,"");
        strcpy(array[i].illness,"");
        strcpy(array[i].address,"");
        strcpy(array[i].bloodType,"");
    }
}

void insertHash(char line[Z])
{
    char *pp,p[S];
    int c = 1;
    pp = strtok(line,",");
    strcpy(p, pp);

    int hash = hashcode(ASCII(p)); // p = patient's name = key
    int i = 0;
    int index = (hash + i)%SIZE;
    char name[S],gender[S],admission[S],birth[S],illness[S],address[S],blood[S];

    while(pp != NULL)
    {
        switch(c)
        {
        case 1:
            strcpy(name, pp);
            break;

        case 2:
            strcpy(gender, pp);
            break;

        case 3:
            strcpy(admission, pp);
            break;

        case 4:
            strcpy(birth, pp);
            break;

        case 5:
            strcpy(illness, pp);
            break;

        case 6:
            strcpy(address, pp);
            break;

        case 7:
            strcpy(blood, pp);
            break;

        default :
            printf("THERE IS SOMETHING WRONG WITH THE DATA ORDER ,PLEASE CHECK THE DATA FILE\n");
        }
        pp = strtok(NULL,",");
        c++;
    }

    //if state=0 then it's empty and we put the data in it
    //and if state=2 then there was data but it's deleted and we put the new data
    if(array[index].state == 0 || array[index].state == 2 )
    {
        strcpy(array[index].name, name);
        strcpy(array[index].gender, gender);
        strcpy(array[index].admissionDate, admission);
        strcpy(array[index].birthDate, birth);
        strcpy(array[index].illness, illness);
        strcpy(array[index].address, address);
        strcpy(array[index].bloodType, blood);
        array[index].state = 1 ; //after inserting data at that index ,it will become occupied/used
    }

    else if(array[index].state == 1)  //used/occupied
    {
        int sum =0;
        for(int j=0 ; j<SIZE; j++)
        {
            if(array[j].state == 1) //OCCUPIED
                sum++;
        }
        if(sum == SIZE) //which means all cells in the table are occupied (full)
            printf("THE TABLE IS FULL ,YOU NEED TO MAKE THE SIZE BIGGER\n");

        else  //that means that some cells in the table are empty or deleted so we need to search
        {
            //increment the index until an empty or deleted index is found
            while(array[index].state == 1)
            {
                if(index == SIZE -1)
                    index = 0;
                else
                    index++;
            }
            strcpy(array[index].name, name);
            strcpy(array[index].gender, gender);
            strcpy(array[index].admissionDate, admission);
            strcpy(array[index].birthDate, birth);
            strcpy(array[index].illness, illness);
            strcpy(array[index].address, address);
            strcpy(array[index].bloodType, blood);
            array[index].state = 1 ; //after inserting data at that index ,it will become occupied/used
        }
    }
}

void readHash()
{
    FILE *in;
    in = fopen("patients_hash.data","r");
    if(in == NULL)
    {
        printf("can't open the file\n");
        exit(1);
    }

    else
    {
        initializeArray();
        printf("file opened successfully\n");
        char line[Z],p1[Z];
        while(fgets ( line, sizeof(line), in ) != NULL )
        {
            //printf(line); // puts(line);
            strcpy(p1, line);
            insertHash(p1);
        }
    }
    fclose(in);
}

void printHash()
{
    printf("INDEX\tSTATUS\tPATEINT DATA:NAME  GENDER  ADMISSIONDATE  BIRTHDATE  ILLNESS  ADDRESS  BLOODTYPE\n");
    printf("______________________________________________________________________________________________________\n");
    for(int i=0 ; i<SIZE ; i++)
    {
        printf("%d\t",i);
        if(array[i].state == 0)
            printf("EMPTY\t");
        else if(array[i].state == 1)
            printf("OCCUPIED\t");
        else if(array[i].state == 2)
            printf("DELETED\t");

        printf("%s  %s  %s",array[i].name,array[i].gender,array[i].admissionDate);
        printf("  %s  %s  %s",array[i].birthDate,array[i].illness,array[i].address);
        printf("  %s  %s\n", array[i].address,array[i].bloodType);
    }
}

void insertHashFromUser()
{
    char name[S],gender[S],admission[S],birth[S],illness[S],address[S],blood[S];
    printf("\n**********INSERTING A NEW PATIENT/RECORD********** ");
    printf("\nENTER PATEINT'S NAME :");
    scanf("%s",&name);
    printf("ENTER PATEINT'S GENDER (F FOR FEMALE AND M FOR MALE) :");
    scanf("%s",&gender);
    printf("ENTER PATEINT'S ADMISSION DATE :");
    scanf("%s",&admission);
    printf("ENTER PATEINT'S BIRTH DATE :");
    scanf("%s",&birth);
    printf("ENTER PATEINT'S ILLNESS :");
    scanf("%s",&illness);
    printf("ENTER PATEINT'S ADDRESS :");
    scanf("%s",&address);
    printf("ENTER PATEINT'S BLOOD TYPE :");
    scanf("%s",&blood);
//changed to this format because the insertHash is implemented that way and i do not want to make a new function
    char line[Z] = "";
    strcat(line, name);
    strcat(line, ",");
    strcat(line, gender);
    strcat(line, ",");
    strcat(line, admission);
    strcat(line, ",");
    strcat(line, birth);
    strcat(line, ",");
    strcat(line, illness);
    strcat(line, ",");
    strcat(line, address);
    strcat(line, ",");
    strcat(line, blood);
    insertHash(line);
    printf("*********NEW PATEINT ADDED*********\n");
}

int searchHash(char key[S])
{
    int hash = hashcode(ASCII(key));
    int index = (hash + 0)%SIZE;
    int flag;

    if(array[index].state == 0)   //empty
    {
        printf("THE PATEINT %s IS NOT FOUND IN THE TABLE\n",key);
        flag =-1;
    }

    else if (array[index].state == 1 && strcmp(array[index].name,key) == 0)   //occupied
    {
        printf("THE PATEINT %s IS FOUND IN THE TABLE AT INDEX %d \n",key, index);
        flag = index;
    }

    else if(array[index].state == 2)//deleted
    {
        while(array[index].state == 2 && index<SIZE)
        {
            index++;
        }

        if (array[index].state == 1 && strcmp(array[index].name,key) == 0)  //occupied
        {
            printf("THE PATEINT %s IS FOUND IN THE TABLE AT INDEX %d \n",key, index);
            flag = index;
        }
        else
        {
            printf("THE PATEINT %s IS NOT FOUND IN THE TABLE\n",key);
            flag = -1;
        }
    }
    else
    {
        printf("THE PATEINT %s IS NOT FOUND IN THE TABLE\n",key);
        flag = -1;
    }

    return flag;
}

void deleteHash(char key[S])
{
    int j = searchHash(key);
    if(j == -1)
        printf("YOU CAN'T DELETE BECAUSE THE PATEINT %s IS NOT IN THE TABLE", key);
    else
    {
        array[j].state = 2 ;//occupied so change the status from occupied (1) to deleted(2)
        printf("THE STATUS OF THE PATEINT HAS CHANGED FROM OCCUPIED TO DELETED");
    }
}

void writeHash()
{
    FILE *out;
    out = fopen("patients_hash.data","w");
    fprintf(out,"INDEX\tSTATUS\tPATEINT DATA:NAME  GENDER  ADMISSIONDATE  BIRTHDATE  ILLNESS  ADDRESS  BLOODTYPE\n");
    fprintf(out,"______________________________________________________________________________________________________\n");
    for(int i=0 ; i<SIZE ; i++)
    {
        fprintf(out,"%d\t",i);
        if(array[i].state == 0)
            fprintf(out,"EMPTY\t");
        else if(array[i].state == 1)
            fprintf(out,"OCCUPIED\t");
        else if(array[i].state == 2)
            fprintf(out,"DELETED\t");

        fprintf(out,"%s  %s  %s",array[i].name,array[i].gender,array[i].admissionDate);
        fprintf(out,"  %s  %s  %s",array[i].birthDate,array[i].illness,array[i].address);
        fprintf(out,"  %s  %s\n", array[i].address,array[i].bloodType);
    }
    fclose(out);
}

void hashOperations()
{
    int num,f;
    char key[S];
    printf("Welcome to hash menu\n");
    readHash();
    while(1)
    {
        printf("Choose an operation to perform : \n");
        printf("  1.Print the entire hashed table including empty spots\n");
        printf("  2.Print out table size\n");
        printf("  3.Print out the used hash function\n");
        printf("  4.Insert a new record into the hash table\n");
        printf("  5.Search for a specific patient\n");
        printf("  6.Delete a specific record\n");
        printf("  7.Save hash table back to file\n");
        printf("  8.Exit\n");
        scanf("%d",&num);

        switch(num)
        {
        case 1:
            printHash();
            break;

        case 2:
            printf("The size of the table = %d\n",SIZE);
            break;

        case 3:
            printf("The used hash method is open addressing -> linear proping\n");
            printf("And the hash function is : h(key) = key %c %d\n",'%',SIZE);
            break;

        case 4:
            insertHashFromUser();
            break;

        case 5:
            printf("ENTER THE NAME OF THE PATIENT YOU WANT TO SEARCH ABOUT:");
            scanf("%s",&key);

            f = searchHash(key);
            break;

        case 6:
            printf("ENTER THE NAME OF THE PATIENT YOU WANT TO DELETE:\n");
            scanf("%s", &key);
            deleteHash(key);
            break;

        case 7:
            writeHash();
            printf("done\n");
            break;

        case 8:
            exit(0);
            break;

        default :
            printf("you entered a wrong number (Invalid number) \n");
        }
    }
}

