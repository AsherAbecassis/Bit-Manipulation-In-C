//
//  main.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define SIZE 8
typedef char board[SIZE][SIZE];
board bin_board;

//-------





//1
void Ex1();
void fileToBainary(char * fileName);
void updateSalary(char* filename, float threshold);
void printToDisplay(char * filename);



//2
void Ex2();
char* codingToShortString(char* dig_str);
void displayShortString(char* short_dig_str);



//3
void Ex3();
unsigned long long boardToBits(board bin_board);
void fillBoard(board bin_board);
void displayBinaryBoard(unsigned long long coded_bin_board);



//*********************************************************************************

int main()
{
    int select = 0, i, all_Ex_in_loop = 0;
    printf("Run menu once or cyclically?\n(Once - enter 0, cyclically - enter other number) ");
    if (scanf("%d", &all_Ex_in_loop) == 1)
        do
        {
            for (i = 1; i <= 3; i++)
                printf("Ex%d--->%d\n", i, i);
            printf("EXIT-->0\n");
            do {
                select = 0;
                printf("please select 0-3 : ");
                scanf("%d", &select);
            } while ((select < 0) || (select > 3));
            switch (select)
            {
            case 1: Ex1(); break;
            case 2: Ex2(); break;
            case 3: Ex3(); break;
            
            
            }
        } while (all_Ex_in_loop && select);
        return 0;
}







//EX1--------------------------------------


typedef struct employee {
    int code;
    char name[15];
    float salary;
} Employee;



void fileToBainary(char * fileName)
{
    FILE *ptr;
    
    ptr = fopen(fileName,"wb");
    
    if(ptr==NULL)
    {  printf("\n Unable to open the file ");
             exit(1);
    }
    
    
    
    int size;
    
    Employee *emp;
    printf("enter how many emp\n");
    scanf("%d",&size);
    
    emp = (Employee*)malloc(size * sizeof(Employee));
    
    for(int i=0;i<size;i++)
    {
        printf("enter name\n");
        rewind(stdin);
        gets(emp[i].name);
        
        printf("enter code\n");
        scanf("%d",&emp[i].code);
        
        
        printf("enter salary\n");
        scanf("%fl",&emp[i].salary);
        
        
        fwrite(&emp[i], sizeof(Employee), 1, ptr);
        
    }
 
    free(emp);
    fclose(ptr);
}


void updateSalary(char* filename, float threshold){
    
    FILE * file = fopen(filename, "rb");
    FILE *tmp = fopen("temp.bin", "wb");
    
    
    if(file==NULL)
    {  printf("\n Unable to open the file ");
             exit(1);
    }
    if(tmp==NULL)
    {  printf("\n Unable to open the file ");
             exit(1);
    }
    
    int n;
    
    Employee emp;
    fread(&emp, sizeof(Employee), 1, file);
    
    while (!feof(file)) {
        printf("add selary to %s ",emp.name);
        scanf("%d",&n);
        n+=emp.salary;
        if(n<threshold)
        {
            emp.salary=n;
            fwrite(&emp, sizeof(Employee), 1, tmp);
            //for uptate the file we create new one
        }
       
        n=0;
        
        fread(&emp, sizeof(Employee), 1, file);
    }
    
    fclose(file);
    fclose(tmp);
    remove(filename);
    rename("temp.bin",filename);//update the new file
    
    
    
}






// print the binary file
void printToDisplay(char * filename)
{
    FILE * file = fopen(filename, "rb");
    
    if(file==NULL)
    {  printf("\n Unable to open the file ");
             exit(1);
    }
    
    Employee emp;
    fread(&emp, sizeof(Employee), 1, file);
    
    while (!feof(file)) {
        
       
        printf("%d %s %lf \n",emp.code,emp.name,emp.salary);
        
        fread(&emp, sizeof(Employee), 1, file);
    }
    fclose(file);
    
    
    
}


void Ex1(){
    
    
    fileToBainary("test.bin");
    updateSalary("test.bin",5000);


    printf("\n\n");
    printToDisplay("test.bin");
    printf("\n\n");
}


//------------------------end------------------------------------


//Ex2





char* codingToShortString(char* dig_str){
    
    
    int n=(int)strlen(dig_str);
    
    unsigned char a;
    unsigned  char b;
    unsigned char sum;
    int new_size=0;
    char *new_str;
    int count=0;
    if(n%2==0)
    {
        //even
        new_size = n/2;
        new_str =(char *)malloc(new_size * sizeof(char));
        
        
    }
    else{
        //odd
        new_size=(n/2)+1;
        new_str =(char *)malloc(new_size * sizeof(char));
        a=dig_str[0] << 4;
        a=a>>4;
        new_str[0]=a;
        count++;
    }
    
    if(dig_str[0]=='0')
    {
        new_str[0]='0';
        return new_str;
    }
    
    
    
    
    for(int i=count+1;i<n;i+=2)
    {
        a=dig_str[i-1];
        b=dig_str[i];
        
        //Bit Manipulation
        a=a<<4;//left shift 00110001
        b=b<<4;//left shift 00010000
        b=b>>4;//right shift 00000001
        sum=a^b;//xor
        new_str[count]=sum;
        count++;
    }
    
    
    
    
    return new_str;
  
    
}

void displayShortString(char* short_dig_str){
    
    int size= (int)strlen(short_dig_str);
    unsigned char a;
    unsigned char b;
    int count=0;
    unsigned char hh;
    unsigned char sum,sum2;
    int flag=0;
    
        //if str start with 0
        if(short_dig_str[0]=='0')
        {
            printf("0 = ");
            a=short_dig_str[0];
            for (int x = 4; x < 8; x++) {
                  printf("%d", !!((a << x) & 0x80));
            }
            printf("\n");
            return;
        }
    
    

    //----print in base 10
    
        a = short_dig_str[0];
    char gg;
    int oo=0;
        for (int x = 0 ; x < 4; x++) {
          if((gg=!!((a << x) & 0x80)) == 0)
              oo++;
          }
       
        
    if(oo==4)
    {
        a=a^'0';
        printf("%c",a);
        flag=1;
            
    }
        
    
    for(int i=flag;i<size;i++)
    {


        a=b=short_dig_str[i];

        a=a>>4;
        b=b<<4;
        b=b>>4;
        sum= a ^ '0';
        sum2= b ^'0';
        printf("%c%c",sum,sum2);


    }
    printf(" = ");

    
    
    //------print by base 2
    
  
        a = short_dig_str[0];
    char g;
    int o=0;
        for (int x = 0 ; x < 4; x++) {
          if((g=!!((a << x) & 0x80)) == 0)
              o++;
          }
       
        
    if(o==4)//for the first bits in str[0]
    {
        for (int x = 4; x < 8; x++) {
              printf("%d", !!((a << x) & 0x80));
            
            
    }
        printf(" ");
        count++;
    }
    
    
    for(int j=count;j<size;j++)
    {
        hh=short_dig_str[j];
        for (int x = 0; x < 8; x++) {
              printf("%d", !!((hh << x) & 0x80));
            if(x==3)
            {
                printf(" ");
            }
          }
        printf(" ");
        
    }
    printf("\n");
    
    
    
    
    
    
    
}


void Ex2(){
    
    char *s;
     s=codingToShortString("8996745");
    printf("\n\n");
    displayShortString(s);
    printf("\n\n");
}



//---------------------------------end---------------------






//EX3

unsigned long long boardToBits(board bin_board)
{
    
    
    
    unsigned long long num=0;
    int n;
 
    
    int count =0;
    
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            n=(bin_board[i][j] - 48);
            if(n==1)
            {
                num ^= 1ull << count; //for poss in the bits
            }
            
            
            count++;
            
        }
    }
    
 
    
    

    return num;
    
    
}

void fillBoard(board bin_board)
{
    srand((int)time(NULL));
    int n;
    char a;
   
    
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            n= rand()%2;
            a=n +48;
            bin_board[i][j]=a;
        }
    }
    
    
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            printf("%c " ,bin_board[i][j]);
            
        }
        printf("\n");
        
    }
    
    
    
    
}



void displayBinaryBoard(unsigned long long coded_bin_board)
{
    
    unsigned long long num1=coded_bin_board;
    int n;
    
    int i=0,j=0;
    
    board chess_mat;
    for (int x = 0; x <64; x++) {
          
        n= !!((num1 >> x) & 0x01);
        if(n==0)
        {
            chess_mat[i][j]='0';
            j++;
            //printf("0 ");
        }
        else{
           
            chess_mat[i][j]='1';
            j++;
            //printf("1 ");
        }
        
        if(j==8)
        {
            j=0;
            i++;
        }
        
        //printf("%d ", !!((num >> x) & 0x01));
        
        
    }
    
    
    for( int c=0;c<SIZE;c++)
    {
        for(int r=0;r<SIZE;r++)
        {
            printf("%c ", chess_mat[c][r]);
        }
        printf("\n");
    }
    
    
}




void Ex3(){
    
    unsigned long long num;
    board chess;
    printf("\n\n");
    fillBoard(chess);
    num=boardToBits(chess);
    printf("\n\n");
    printf("unsigned long long =  %llu \n \n \n",num);
    
    displayBinaryBoard(num);
    printf("\n\n");
    
}


//int main(int argc, const char * argv[]) {
//
//
//    //-----------
//    //1
//
//
//
//    fileToBainary("test.bin");
//    updateSalary("test.bin",5000);
//
//
//    printf("\n\n");
//    printToDisplay("test.bin");
//
//
//    //----------------
//    //2
//
//
//    char *s;
//     s=codingToShortString("4651093");
//    displayShortString(s);
//    printf("\n\n");
////------------------
//    //3
//
//    unsigned long long num;
//    board chess;
//
//    fillBoard(chess);
//    num=boardToBits(chess);
//    printf("\n\n");
//    printf("unsigned long long =  %llu \n \n \n",num);
//
//    displayBinaryBoard(num);
//
//
//
//
//
//
//    return 0;
//}
