#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>

int oat_numberofentries = 0;
int dht_numberofentries = 0;
double Load_Factor = 0.7;
int Capacity = 10;
int OAT_Collissions = 0;
int DHT_Collissions = 0;

struct OAT_node
{
    char CourseName[50];
    int CreditHours;
    char CourseCode[50];
    char Department[50];
    char Topics[200];
    int key;
};

struct DHT_node
{
    char CourseName[50];
    int CreditHours;
    char CourseCode[50];
    char Department[50];
    char Topics[200];
    int key;
};

struct OAT_node *OAT_Array;
struct DHT_node *DHT_Array;

int main()
{
    Clear_Out_File();
    Initiate_Table();
    Load_Input_File();
    int Select;
    int Search_Choice;
    char CourseName[50];
    int CreditHours;
    char CourseCode[50];
    char Department[50];
    char Topics[200];
    char Stop1;
    char Stop2;
    char newline;
    char Letter;
    double current_load_factor;
    while(1)
        {
            printf("1. Print hashed tables.\n2. Print out table size and the load factor. \n3. Print out the used hash functions. \n4. Insert a new record to hash table. \n5. Search for a specific word. \n6. Delete a specific record.\n7. Compare between the two methods in terms of number of collisions occurred.\n8. Save hash table.\n");
            printf("Select Option: ");
            scanf("%d",&Select);
            printf("\n");
            switch(Select)
            {
                case 1:
                    Print_OAT();
                    printf("\n---------------------------------------\n");
                    Print_DHT();
                    printf("\n---------------------------------------\n");
                    break;
                case 2:
                    current_load_factor = (double)oat_numberofentries / Capacity;
                    printf("=> For Open Addressing <=\n-------------------\nTable Size = %d.\nOccupied Cells = %d.\nMain Load Factor = %f.\nCurrent Load Factor = %f.\n\n************************\n\n",Capacity,oat_numberofentries,Load_Factor,current_load_factor);
                    current_load_factor = (double)dht_numberofentries / Capacity;
                    printf("=> For Double Hashing <=\n-------------------\nTable Size = %d.\nOccupied Cells = %d.\nMain Load Factor = %f.\nCurrent Load Factor = %f.\n\n",Capacity,dht_numberofentries,Load_Factor,current_load_factor);
                    break;
                case 3:
                    printf("=> For Open Addressing <=\n-------------------\n\nHash(key) = key mod Capacity\n\n*****************\n\n");
                    printf("=> For Double Hashing <=\n-------------------\n\nHash(key,i) = [ h1(key) + i*h2(key)] mod Capacity\nwhere:\nh1(key) = key mod Capacity\nh2(key) = 7 - (key mod 7).\n\n");
                    break;
                case 4:
                    printf("\n");
                    scanf("%c",&newline);
                    printf("Course Name: ");
                    scanf("%[^\t\n]", CourseName);
                    scanf("%c",&Stop1);

                    printf("Credit Hours: ");
                    scanf("%d",&CreditHours);

                    printf("Course Code: ");
                    scanf("%s",CourseCode);

                    scanf("%c",&newline);
                    printf("Department: ");
                    scanf("%[^\t\n]",Department);

                    scanf("%c",&newline);
                    printf("Topics: ");
                    scanf("%[^\t\n]",Topics);
                    scanf("%c",&Stop2);

                    OAT_Insert(CourseName,CreditHours,CourseCode,Department,Topics);
                    DHT_Insert(CourseName,CreditHours,CourseCode,Department,Topics);
                    printf("Inserted!");
                    break;
                case 5:
                    printf("\n");
                    scanf("%c",&newline);
                    printf("Course Name: ");
                    scanf("%[^\t\n]", CourseName);
                    scanf("%c",&Stop1);

                    printf("1. Open Addressing Table.\n2. Double Hashing Table.\n");
                    scanf("%d",&Search_Choice);
                    if(Search_Choice == 1)
                        {
                            OAT_Searching(CourseName);
                        }
                    else if(Search_Choice == 2)
                        {
                            DHT_Searching(CourseName);
                        }
                    break;
                case 6:
                    printf("\n");
                    scanf("%c",&newline);
                    printf("Course Name: ");
                    scanf("%[^\t\n]", CourseName);
                    scanf("%c",&Stop1);
                    OAT_Deleting(CourseName);
                    DHT_Deleting(CourseName);
                    break;
                case 7:
                    printf("Number of Open-Addressing Hashing (Linear) Collisions Occurred: %d\n",OAT_Collissions);
                    printf("Number of Double Hashing Collisions Occurred: %d\n",DHT_Collissions);

                    if(OAT_Collissions > DHT_Collissions)
                        {
                            printf("\nOpen Addressing has more collisions than Double Hashing!\n");
                        }

                    else if(DHT_Collissions > OAT_Collissions)
                        {
                            printf("\nDouble Hashing has more collisions than Open Addressing!\n");
                        }

                    else
                        {
                            printf("\nBoth Have the same collision rate!\n");
                        }
                    break;
                case 8:
                    Save_DHT();
                    printf("\nTable Saved on file!\n");
                    printf("\nBye!\n");
                    exit(0);
                    break;

                default:
                    printf("\nWrong input! Try Again Please!\n\n");
                    break;
            }
            printf("\n\n");
        }
    return 0;
}

void Clear_Out_File()
{
    FILE *fopens;
    fopens = fopen("saved_courses.txt","w");
    fprintf(fopens,"%s","");
    fclose(fopens);
}

void Load_Input_File()
{
    char line[300];
    char CourseName[50];
    int CreditHours;
    char CourseCode[50];
    char Department[50];
    char Topics[200];
    FILE *f = fopen("offered_courses.txt","r");

    while(fgets(line,300,f))
        {
            if(strlen(line) > 1)
                {
                    char *token = strtok(line,":");
                    strcpy(CourseName,token);
                    ///printf("%s\n",CourseName);
                    token = strtok(NULL, "#");
                    CreditHours = atoi(token);
                    ///printf("Credit Hours: %d\n",CreditHours);
                    token = strtok(NULL, "#");
                    strcpy(CourseCode,token);
                    ///printf("Course Code: %s\n",CourseCode);
                    token = strtok(NULL, "#/");
                    strcpy(Department,token);
                    ///printf("Department: %s\n",Department);
                    token = strtok(NULL,"/");
                    strcpy(Topics,token);
                    ///printf("Topics: %s\n",Topics);
                    OAT_Insert(CourseName,CreditHours,CourseCode,Department,Topics);
                    DHT_Insert(CourseName,CreditHours,CourseCode,Department,Topics);
                }
        }
    fclose(f);
    printf("File Loaded!\n=================\n");
}

void OAT_Insert(char* CourseName, int CreditHours, char* CourseCode, char* Department, char* Topics)
{
    int key,index;
    double temp;
    int counts=0;
    key = valueofstring(CourseName);
    ///printf("%s value is %d, ",CourseName, key);
    index = hash_OAT_function(key);
    int cell;
    cell = index;
    ///printf("Index = %d\n",index);

    while(OAT_Array[cell].key == 1)//if cell is not empty
        {///printf("\nLinear: Collision of key %d at index %d\n",key,cell);
            OAT_Collissions++;
            cell = hash_OAT_function(cell + 1); // increment by 1 and if we exceed 9 it goes back to zero
            counts++;//counts number of trying to insert along the table
            if(cell == index)//if wee take a full loop and none is empty
                {
                    printf("\nLinear: Hash Table is FULL!\n");
                    return;
                }
        }


    //assign values to the cell
    OAT_Array[cell].key = 1;// 1 means that we're going to give the cell a value to save
    strcpy(OAT_Array[cell].CourseName,CourseName);
    OAT_Array[cell].CreditHours = CreditHours;
    strcpy(OAT_Array[cell].CourseCode,CourseCode);
    strcpy(OAT_Array[cell].Department,Department);
    strcpy(OAT_Array[cell].Topics,Topics);
    oat_numberofentries++;//update the hash table size
    ///printf("|%s| inserted Successfully!\n",OAT_Array[index].CourseName);

    //checking load factor to decide of rehashing or not
    temp = (double)oat_numberofentries / Capacity ;
    if(temp > Load_Factor)
        {
            printf("\n\nREHASHING (Linear)!\n\n");
            rehashing(1);
        }

}


void DHT_Insert(char* CourseName, int CreditHours, char* CourseCode, char* Department, char* Topics)
{
    int i=0;
    int key,index;
    double temp;
    int counts=0;
    key = valueofstring(CourseName);
    ///printf("%s value is %d, ",CourseName, key);
    index = hash_DHT_function(key,i);
    int cell;
    cell = index;
    ///printf("Index = %d\n",index);

    while(DHT_Array[cell].key == 1)//if cell is not empty
        {///printf("\nDouble: Collision of key %d at index %d\n",key,cell);
            DHT_Collissions++;
            i = i+1;
            cell = hash_DHT_function(cell + 1,i); // increment by 1 and if we exceed 9 it goes back to zero
            counts++;//counts number of trying to insert along the table
            if(cell == index)//if wee take a full loop and none is empty
                {
                    printf("\nDouble: Hash Table is FULL! or no place to insert\n");
                    return;
                }
        }


    //assign values to the cell
    DHT_Array[cell].key = 1;// 1 means that we're going to give the cell a value to save
    strcpy(DHT_Array[cell].CourseName,CourseName);
    DHT_Array[cell].CreditHours = CreditHours;
    strcpy(DHT_Array[cell].CourseCode,CourseCode);
    strcpy(DHT_Array[cell].Department,Department);
    strcpy(DHT_Array[cell].Topics,Topics);
    dht_numberofentries++;//update the hash table size
    ///printf("|%s| inserted Successfully at index %d!\n",DHT_Array[index].CourseName,index);

    //checking load factor to decide of rehashing or not
    temp = (double) dht_numberofentries / Capacity ;
    if(temp > Load_Factor)
        {
            printf("\n\nREHASHING! (Double)\n\n");
            rehashing(2);
        }
}


int valueofstring(char* Name)
{
    int result = 0;
    int i = 0;
    while(Name[i]!= NULL)
        {
            if(Name[i] != 32 )
                {
                    result = result + Name[i];
                }
            i++;
        }
        return result;
}

// open addressing linear hash function
int hash_OAT_function(int key)
{
    return key % Capacity;
}

// double hash function
int hash_DHT_function(int key,int i)
{
    int h1 = key % Capacity;
    int h2 = 7 - (key % 7);
    int Results;
    Results = (h1 + i*h2) % Capacity;
    return Results;
}

//initialize tables with null
void Initiate_Table()
{
    //oat
    OAT_Array = (struct OAT_node*) malloc(Capacity * sizeof (struct OAT_node));

    for(int i=0;i<Capacity;i++)
        {
            OAT_Array[i].key = 0;
            strcpy(OAT_Array[i].CourseName,"");
            OAT_Array[i].CreditHours = 0;
            strcpy(OAT_Array[i].CourseCode,"");
            strcpy(OAT_Array[i].Department,"");
            strcpy(OAT_Array[i].Topics,"");
        }
///////////////////////////////////////////////////////////////////////////////
    //dht
    DHT_Array = (struct DHT_node*) malloc(Capacity * sizeof (struct DHT_node));

    for(int j=0;j<Capacity;j++)
        {
            DHT_Array[j].key = 0;
            strcpy(DHT_Array[j].CourseName,"");
            DHT_Array[j].CreditHours = 0;
            strcpy(DHT_Array[j].CourseCode,"");
            strcpy(DHT_Array[j].Department,"");
            strcpy(DHT_Array[j].Topics,"");
        }
    printf("Tables Initiated!\n");
}

//rehashing if we exceed the load factor
void rehashing(int x)
{
    //reset of number of collisions!
    OAT_Collissions = 0;
    DHT_Collissions = 0;
    int temp = Capacity * 2;

    struct OAT_node *temp_oat_array = OAT_Array;
    OAT_Array = (struct OAT_node*) malloc(temp * sizeof(struct OAT_node));

    struct DHT_node *temp_dht_array = DHT_Array;
    DHT_Array = (struct DHT_node*) malloc(temp * sizeof(struct DHT_node));
    //Rearrange to new hash table after rehashing "Refresh the hash table with new size"
    for(int i=0;i<temp; i++)
        {
            OAT_Array[i].key = 0;
            strcpy(OAT_Array[i].CourseName,"");
            OAT_Array[i].CreditHours = 0;
            strcpy(OAT_Array[i].CourseCode,"");
            strcpy(OAT_Array[i].Department,"");
            strcpy(OAT_Array[i].Topics,"");
            /////////////////////////////////
            DHT_Array[i].key = 0;
            strcpy(DHT_Array[i].CourseName,"");
            DHT_Array[i].CreditHours = 0;
            strcpy(DHT_Array[i].CourseCode,"");
            strcpy(DHT_Array[i].Department,"");
            strcpy(DHT_Array[i].Topics,"");
        }
    oat_numberofentries = 0;
    dht_numberofentries = 0;
    Capacity = temp;

    for(int j = 0; j<temp/2; j++)
        {
            if( x == 1 )
                {
                    if(temp_oat_array[j].key == 1 )
                        {
                            OAT_Insert(temp_oat_array[j].CourseName,temp_oat_array[j].CreditHours,temp_oat_array[j].CourseCode,temp_oat_array[j].Department,temp_oat_array[j].Topics);
                        }
                }

            else if(x == 2)
                {
                    if(temp_dht_array[j].key == 1)
                        {
                            DHT_Insert(temp_dht_array[j].CourseName,temp_dht_array[j].CreditHours,temp_dht_array[j].CourseCode,temp_dht_array[j].Department,temp_dht_array[j].Topics);
                        }
                }
        }
}


void Print_OAT()
{
    printf("\nOpen-Addressing(Linear) Table\n");
    for(int i = 0 ; i<Capacity ; i++)
        {
            if(OAT_Array[i].key == 1)
                {
                    printf("%d) %s\n",i,OAT_Array[i].CourseName);
                }
            else
                {
                    printf("%d) Empty\n",i);
                }
        }
}

void Print_DHT()
{
    printf("\nDouble Hashing Table\n");
    for(int i = 0 ; i<Capacity ; i++)
        {
            if(DHT_Array[i].key == 1)
                {
                    printf("%d) %s\n",i,DHT_Array[i].CourseName);
                }
            else
                {
                    printf("%d) Empty\n",i);
                }
        }
}

void OAT_Searching(char* Name)
{
    int key;
    int index;
    key = valueofstring(Name);
    index = hash_OAT_function(key);
    printf("\nValue = %d\n",key);
    int cell = index;
    while(OAT_Array[cell].key == 1)//if cell is not empty
        {
            if(strcmp(OAT_Array[cell].CourseName,Name) == 0)
                {
                    printf("Founded");
                    printf("\n%s",OAT_Array[cell].CourseCode);
                    return;
                }

            else
                {
                    cell = hash_OAT_function(cell + 1); // increment by 1 and if we exceed 9 it goes back to zero

                    if(cell == index)//if wee take a full loop and none is empty
                        {
                            printf("\nSearching have done along the table without a result!\n");
                        }
                }
        }

    if(OAT_Array[cell].key == 0 )
        {
            printf("\nNot Founded in Table!\n");
        }
}

DHT_Searching(char* Name)
{
    int i=0;
    int key;
    int index;
    key = valueofstring(Name);
    index = hash_DHT_function(key,i);
    printf("\nValue = %d\n",key);
    int cell = index;
    while(DHT_Array[cell].key == 1)//if cell is not empty
        {
            if(strcmp(DHT_Array[cell].CourseName,Name) == 0)
                {
                    printf("Founded");
                    printf("\n%s",DHT_Array[cell].CourseCode);
                    return;
                }

            else
                {
                    i = i+1;
                    cell = hash_DHT_function(cell + 1,i); // increment by 1 and if we exceed 9 it goes back to zero

                    if(cell == index)//if wee take a full loop and none is empty
                        {
                            printf("\nSearching have done along the table without a result!\n");
                        }
                }
        }

    if(DHT_Array[cell].key == 0 )
        {
            printf("\nNot Founded in Table!\n");
        }
}

void OAT_Deleting(char* Name)
{
    int key;
    int index;
    key = valueofstring(Name);
    index = hash_OAT_function(key);
    printf("\nValue = %d\n",key);
    int cell = index;
    while(OAT_Array[cell].key == 1)//if cell is not empty
        {
            if(strcmp(OAT_Array[cell].CourseName,Name) == 0)
                {
                    printf("Founded");
                    OAT_Array[cell].key = 0;
                    strcpy(OAT_Array[cell].CourseName,"");
                    OAT_Array[cell].CreditHours = 0;
                    strcpy(OAT_Array[cell].CourseCode,"");
                    strcpy(OAT_Array[cell].Department,"");
                    strcpy(OAT_Array[cell].Topics,"");
                    return;
                }

            else
                {
                    cell = hash_OAT_function(cell + 1); // increment by 1 and if we exceed 9 it goes back to zero

                    if(cell == index)//if wee take a full loop and none is empty
                        {
                            printf("\nSearching have done along the table without a result!\n");
                        }
                }
        }

    if(OAT_Array[cell].key == 0 )
        {
            printf("\nNot Founded in Table!\n");
        }
}

void DHT_Deleting(char* Name)
{
    int i=0;
    int key;
    int index;
    key = valueofstring(Name);
    index = hash_DHT_function(key,i);
    printf("\nValue = %d\n",key);
    int cell = index;
    while(DHT_Array[cell].key == 1)//if cell is not empty
        {
            if(strcmp(DHT_Array[cell].CourseName,Name) == 0)
                {
                    printf("Founded");
                    DHT_Array[cell].key = 0;
                    strcpy(DHT_Array[cell].CourseName,"");
                    DHT_Array[cell].CreditHours = 0;
                    strcpy(DHT_Array[cell].CourseCode,"");
                    strcpy(DHT_Array[cell].Department,"");
                    strcpy(DHT_Array[cell].Topics,"");
                    printf("\nDeleted!\n");
                    return;
                }

            else
                {
                    i = i+1;
                    cell = hash_DHT_function(cell + 1,i); // increment by 1 and if we exceed 9 it goes back to zero

                    if(cell == index)//if wee take a full loop and none is empty
                        {
                            printf("\nSearching have done along the table without a result!\n");
                        }
                }
        }

    if(DHT_Array[cell].key == 0 )
        {
            printf("\nNot Founded in Table!\n");
        }
}


void Save_DHT()
{
    FILE *fopens;
    fopens = fopen("saved_courses.txt","w");
    for(int i = 0; i<Capacity ; i++)
        {
            if(DHT_Array[i].key == 1)
            {
                fprintf(fopens,"%s:%d#%s#%s/%s",DHT_Array[i].CourseName,DHT_Array[i].CreditHours,DHT_Array[i].CourseCode,DHT_Array[i].Department,DHT_Array[i].Topics);
            }
        }
    fclose(fopens);
}
