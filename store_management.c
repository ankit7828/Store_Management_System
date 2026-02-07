#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
char name[100]; // name of customer
char add[100]; // address of customer
long long int num; // contact number of customer
int count = 0; // number of products in cart
int bill = 0; // total bill before discount
int total = 0; // total bill after discount

int sn[100], s = 0; // serial number for each product
char product[100][50]; // store product information each row is a product
int p = 0;
int quentity[100], q = 0; // quentity of each product purchased
int price[100], pr = 0; // price of each product purchased

typedef struct data // format in which purchase data is stored
{
    char name[50];
    char address[100];
    int total_bill;
    long long int number;
    int day, month, year, hr, min, sec;
} sdata;

void display() // print the purchase history
{
    FILE *fp;
    fp = fopen("storedata.txt", "r");
    sdata s1; // store and display one record at a time
    printf("\nName                  Address                         Number                Price        Date       Time\n");
    printf("------------------------------------------------------------------------------------------------------------\n");
    while (fread(&s1, sizeof(sdata), 1, fp)) // read binary data from file 
    {
        printf("%-20s| %-30s| %-20lld| RS.%-5d| %d-%d-%d | %d:%d:%d |\n", s1.name, s1.address, s1.number, s1.total_bill, s1.day, s1.month, s1.year, s1.hr, s1.min, s1.sec);
        printf("------------------------------------------------------------------------------------------------------------\n");
    }
    fclose(fp);
}
void appened() // add a new record manually in file
{
    sdata *s;
    FILE *fp;
    int n, i;
    printf("enter how many records you want to enter : ");
    scanf("%d", &n);
    s = (sdata *)calloc(n, sizeof(sdata)); // Allocates memory for n structures
    fp = fopen("storedata.txt", "a"); // Opens file in append mode
    for (i = 0; i < n; i++)
    {
        fflush(stdin); // clear input buffer and hndle Undefined behavior in C
        printf("\nEnter name : ");
        gets(s[i].name);
        fflush(stdin);
        printf("\nEnter address : ");
        gets(s[i].address);
        fflush(stdin);
        printf("\nenter mobile number : ");
        scanf("%lld", &s[i].number);
        printf("\nEnter total bill : ");
        scanf("%d", &s[i].total_bill);
        printf("enter day month year hour min sec in sequence : ");
        scanf("%d%d%d%d%d%d", &s[i].day, &s[i].month, &s[i].year, &s[i].hr, &s[i].min, &s[i].sec);
        fwrite(&s[i], sizeof(sdata), 1, fp); // Appends record at end of file
    }
    printf("\nRecord added successfully\n");
    fclose(fp);
}
void noofrecords() // Count number of records in file or total purchases.
{
    FILE *fp;
    fp = fopen("storedata.txt", "r");
    fseek(fp, 0, SEEK_END); // Moves file pointer at the last byte
    int n = ftell(fp) / sizeof(sdata); // returns current file position
    printf("\nnumber of records are : %d ", n);
    fclose(fp);
}
void search() // Search customer by name
{
    FILE *fp;
    fp = fopen("storedata.txt", "r");
    sdata s1;
    char ser_name[100];
    int flag = 0; // indicate status
    fflush(stdin);
    printf("enter name to search : ");
    gets(ser_name);
    fflush(stdin);
    while (fread(&s1, sizeof(sdata), 1, fp)) // read binary data from file 
    {
        if (strcmp(s1.name, ser_name) == 0)
        {
            flag = 1;
            printf("\nName                  Address                         Number                Price        Date       Time\n");
            printf("------------------------------------------------------------------------------------------------------------\n");
            printf("%-20s| %-30s| %-20lld| RS.%-5d| %d-%d-%d | %d:%d:%d |\n", s1.name, s1.address, s1.number, s1.total_bill, s1.day, s1.month, s1.year, s1.hr, s1.min, s1.sec);
            printf("------------------------------------------------------------------------------------------------------------\n");
        }
    }
    if (flag == 0){
        printf("\nRecord not found\n");
    }
    fclose(fp);
}
void update() // Modify existing customer record
{
    FILE *fp, *fp2;
    fp = fopen("storedata.txt", "r"); // Read from original file
    fp2 = fopen("temp2.txt", "w"); // Write updated data to temporary file
    sdata s1;
    int flag = 0; // to check whether the record was found
    fflush(stdin);
    printf("enter name to update : ");
    char ser_name[100];
    gets(ser_name);
    fflush(stdin);
    while (fread(&s1, sizeof(sdata), 1, fp)) // Reads each record from original file
    {
        if (strcmp(s1.name, ser_name) == 0)
        {
            flag = 1;
            fflush(stdin);
            printf("\nEnter new address : ");
            gets(s1.address);
            fflush(stdin);
            printf("\nenter new mobile number : ");
            scanf("%lld", &s1.number);
            printf("\nEnter new total bill : ");
            scanf("%d", &s1.total_bill);
            printf("enter new day month year hour min sec in sequence : ");
            scanf("%d%d%d%d%d%d", &s1.day, &s1.month, &s1.year, &s1.hr, &s1.min, &s1.sec);
        }
        fwrite(&s1, sizeof(sdata), 1, fp2);
    }
    fclose(fp);
    fclose(fp2);
    if (flag == 1){
        fp = fopen("storedata.txt", "w");
        fp2 = fopen("temp2.txt", "r");
        while (fread(&s1, sizeof(sdata), 1, fp2))
        {
            fwrite(&s1, sizeof(sdata), 1, fp);
        }
        fclose(fp);
        fclose(fp2);
        printf("\nData updated successfully\n");
    }else{
        printf("\nrocord not found\n");
    }
}
void delete() // Delete a customer record
{
    FILE *fp, *fp2;
    fp = fopen("storedata.txt", "r");
    fp2 = fopen("temp2.txt", "w");
    sdata s1; // Stores one record at a time
    int flag = 0;
    fflush(stdin);
    printf("enter name to delete : ");
    char ser_name[100];
    gets(ser_name);
    fflush(stdin);
    while (fread(&s1, sizeof(sdata), 1, fp))
    {
        if (strcmp(s1.name, ser_name) == 0){
            flag = 1;
        }else{
            fwrite(&s1, sizeof(sdata), 1, fp2);
        }
    }
    fclose(fp);
    fclose(fp2);
    if (flag == 1){
        fp = fopen("storedata.txt", "w");
        fp2 = fopen("temp2.txt", "r");
        while (fread(&s1, sizeof(sdata), 1, fp2))
        {
            fwrite(&s1, sizeof(sdata), 1, fp);
        }
        fclose(fp);
        fclose(fp2);
        printf("\nRecord deleted successfully\n");
    }else{
        printf("\nrecord not found\n");
    }
}
void sort_total_on_screen() // Sort by total bill in descending order
{
    sdata *s, s1;
    FILE *fp;
    fp = fopen("storedata.txt", "r");
    int i, j;
    fseek(fp, 0, SEEK_END); // Moves pointer to end of file
    int n = ftell(fp) / sizeof(sdata); // total file size in bytes
    s = (sdata *)calloc(n, sizeof(sdata));
    rewind(fp); // Moves file pointer back to start of file
    for (i = 0; i < n; i++){
        fread(&s[i], sizeof(sdata), 1, fp); // Reads all records from file into memory array s
    }
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (s[i].total_bill < s[j].total_bill)
            {
                s1 = s[i];
                s[i] = s[j];
                s[j] = s1;
            }
        }
    }
    printf("\nName                  Address                         Number                Price        Date       Time\n");
    printf("------------------------------------------------------------------------------------------------------------\n");
    for (i = 0; i < n; i++)
    {
        printf("%-20s| %-30s| %-20lld| RS.%-5d| %d-%d-%d | %d:%d:%d |\n", s[i].name, s[i].address, s[i].number, s[i].total_bill, s[i].day, s[i].month, s[i].year, s[i].hr, s[i].min, s[i].sec);
        printf("------------------------------------------------------------------------------------------------------------\n");
        fclose(fp);
    }
}
void sort_total_in_file() // Rewrite the original file with sorted data
{
    sdata *s, s1;
    FILE *fp;
    fp = fopen("storedata.txt", "r");
    int i, j;
    fseek(fp, 0, SEEK_END); // Moves pointer to end of file
    int n = ftell(fp) / sizeof(sdata); // total file size in bytes
    s = (sdata *)calloc(n, sizeof(sdata));
    rewind(fp); // Moves file pointer back to start of file
    for (i = 0; i < n; i++)
    {
        fread(&s[i], sizeof(sdata), 1, fp); // Reads all records from file into memory array s
    }
    fclose(fp);
    for (i = 0; i < n; i++) // sorting logic simple selection sort
    {
        for (j = i + 1; j < n; j++)
        {
            if (s[i].total_bill < s[j].total_bill)
            {
                s1 = s[i];
                s[i] = s[j];
                s[j] = s1;
            }
        }
    }
    fp = fopen("storedata.txt", "w");
    printf("\nName                  Address                         Number                Price        Date       Time\n");
    printf("------------------------------------------------------------------------------------------------------------\n");
    for (i = 0; i < n; i++) // Displays each sorted record and Writes it back to the file in sorted order
    {
        printf("%-20s| %-30s| %-20lld| RS.%-5d| %d-%d-%d | %d:%d:%d |\n", s[i].name, s[i].address, s[i].number, s[i].total_bill, s[i].day, s[i].month, s[i].year, s[i].hr, s[i].min, s[i].sec);
        printf("------------------------------------------------------------------------------------------------------------\n");
        fwrite(&s[i], sizeof(sdata), 1, fp); 
    }
    fclose(fp);
}
void sort_name_on_screen() // Display sorted records on screen File data is NOT modified
{ 
    sdata *s, s1;
    FILE *fp;
    fp = fopen("storedata.txt", "r");
    int i, j;
    fseek(fp, 0, SEEK_END);
    int n = ftell(fp) / sizeof(sdata);
    s = (sdata *)calloc(n, sizeof(sdata));
    rewind(fp);
    for (i = 0; i < n; i++)
    {
        fread(&s[i], sizeof(sdata), 1, fp);
    }
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (strcmp(s[i].name, s[j].name) > 0)
            {
                s1 = s[i];
                s[i] = s[j];
                s[j] = s1;
            }
        }
    }
    printf("\nName                  Address                         Number                Price        Date       Time\n");
    printf("------------------------------------------------------------------------------------------------------------\n");
    for (i = 0; i < n; i++)
    {
        printf("%-20s| %-30s| %-20lld| RS.%-5d| %d-%d-%d | %d:%d:%d |\n", s[i].name, s[i].address, s[i].number, s[i].total_bill, s[i].day, s[i].month, s[i].year, s[i].hr, s[i].min, s[i].sec);
        printf("------------------------------------------------------------------------------------------------------------\n");
        fclose(fp);
    }
}
// for fruits
void Fruits()
{
    int fc, que; // Displays available fruits Shows price per kg fc = fruit code , que = quantity
    printf("\n============================================== Greate choice select a fruit =============================================\n");
    printf("\n101) Mango-------------------------------------1kg----------------------------------RS.200");
    printf("\n102) Apple-------------------------------------1kg----------------------------------RS.250");
    printf("\n103) Banana------------------------------------1kg----------------------------------RS.50");
    printf("\n104) Pineapple---------------------------------1kg----------------------------------RS.70");
    printf("\n105) Papaya------------------------------------1kg----------------------------------RS.60");
    printf("\nplease choose your product code : ");
    scanf("%d", &fc);

    if (fc == 101){
        printf("\nMango is a good choice how many kgs you want : ");
        scanf("%d", &que);
        sn[s] = ++s; // store serial number
        strcpy(product[p++], "Mango"); // store product name
        quentity[q++] = que; // store quantity in kg
        price[pr++] = que * 200; // Stores item price
        bill = bill + que * 200; // Updates total bill
        count++;
    }else if (fc == 102){
        printf("\nApple is a good choice how many kgs you want : ");
        scanf("%d", &que);
        sn[s] = ++s; // store serial number
        strcpy(product[p++], "Apple"); // store product name
        quentity[q++] = que; // store quantity in kg
        price[pr++] = que * 250; // Stores item price
        bill = bill + que * 250; // Updates total bill
        count++;
    }else if (fc == 103){
        printf("\nBanana is a good choice how many kgs you want : ");
        scanf("%d", &que);
        sn[s] = ++s; // store serial number
        strcpy(product[p++], "Banana"); // store product name
        quentity[q++] = que; // store quantity in kg
        price[pr++] = que * 50; // Stores item price
        bill = bill + que * 50; // Updates total bill
        count++;
    }else if (fc == 104){
        printf("\nPineapple is a good choice how many kgs you want : ");
        scanf("%d", &que);
        sn[s] = ++s; // store serial number
        strcpy(product[p++], "Pineapple"); // store product name
        quentity[q++] = que; // store quantity in kg
        price[pr++] = que * 70; // Stores item price
        bill = bill + que * 70; // Updates total bill
        count++;
    }else if (fc == 105){
        printf("\nPapaya is a good choice how many kgs you want : ");
        scanf("%d", &que);
        sn[s] = ++s; // store serial number
        strcpy(product[p++], "Papaya"); // store product name
        quentity[q++] = que; // store quantity in kg
        price[pr++] = que * 60; // Stores item price
        bill = bill + que * 60; // Updates total bill
        count++;
    }else{
        printf("\ninvalid choice\n");
    }
}
// for vegetables
void Vegetables()
{
    int vc, que; // Displays available vegetables Shows price per kg vc = vegetables code , que = quantity
    printf("\n============================================== Greate choice select a vegetable =============================================\n");
    printf("\n201) Tomato------------------------------------1kg-----------------------------------RS.60");
    printf("\n202) Spinach-----------------------------------1kg-----------------------------------RS.20");
    printf("\n203) Beetroot----------------------------------1kg-----------------------------------RS.50");
    printf("\n204) Potato------------------------------------1kg-----------------------------------RS.35");
    printf("\n205) Brinjal-----------------------------------1kg-----------------------------------RS.45");
    printf("\nplease choose your product code : ");
    scanf("%d", &vc);
    if (vc == 201)
    {
        printf("\nTomato is a good choice how many kgs you want : ");
        scanf("%d", &que);
        sn[s] = ++s; // store serial number
        strcpy(product[p++], "Tomatp"); // store product name
        quentity[q++] = que; // store quantity in kg
        price[pr++] = que * 60; // Stores item price
        bill = bill + que * 60; // Updates total bill
        count++;
    }else if (vc == 202){
        printf("\nSpinach is a good choice how many kgs you want : ");
        scanf("%d", &que);
        sn[s] = ++s; // store serial number
        strcpy(product[p++], "Spinach"); // store product name
        quentity[q++] = que; // store quantity in kg
        price[pr++] = que * 20; // Stores item price
        bill = bill + que * 20; // Updates total bill
        count++;
    }else if (vc == 203){
        printf("\nBeetroot is a good choice how many kgs you want : ");
        scanf("%d", &que);
        sn[s] = ++s; // store serial number
        strcpy(product[p++], "BeetRoot"); // store product name
        quentity[q++] = que; // store quantity in kg
        price[pr++] = que * 50; // Stores item price
        bill = bill + que * 50; // Updates total bill
        count++;
    }else if (vc == 204){
        printf("\nPotato is a good choice how many kgs you want : ");
        scanf("%d", &que);
        sn[s] = ++s; // store serial number
        strcpy(product[p++], "Potato"); // store product name
        quentity[q++] = que; // store quantity in kg
        price[pr++] = que * 35; // Stores item price
        bill = bill + que * 35; // Updates total bill
        count++;
    }else if (vc == 205){
        printf("\nBrinjal is a good choice how many kgs you want : ");
        scanf("%d", &que);
        sn[s] = ++s; // store serial number
        strcpy(product[p++], "Brinjal"); // store product name
        quentity[q++] = que; // store quantity in kg
        price[pr++] = que * 45; // Stores item price
        bill = bill + que * 45; // Updates total bill
        count++;
    }else{
        printf("\ninvalid choice\n");
    }
}
// for Cosmaticks
void Cosmaticks()
{
    int cc, que; // Displays available cosmaticks Shows price per kg cc = cosmaticks code , que = quantity
    printf("\n============================================== Greate choice select a cosmatic =============================================\n");
    printf("\n301) Kajal-------------------------------------1per/piece------------------------------RS.50");
    printf("\n302) Lipstic-----------------------------------1per/piece------------------------------RS.20");
    printf("\n303) Nailpolish--------------------------------1per/piece------------------------------RS.30");
    printf("\n304) Facewash----------------------------------1per/piece------------------------------RS.70");
    printf("\n305) Lotion------------------------------------1per/piece------------------------------RS.120");
    printf("\nplease choose your product code : ");
    scanf("%d", &cc);
    if (cc == 301)
    {
        printf("\nKajal is a good choice how many Kajals you want : ");
        scanf("%d", &que);
        sn[s] = ++s; // store serial number
        strcpy(product[p++], "Kajal"); // store product name
        quentity[q++] = que; // store quantity in kg
        price[pr++] = que * 50; // Stores item price
        bill = bill + que * 50; // Updates total bill
        count++;
    }else if (cc == 302){
        printf("\nLipstic is a good choice how many Lipstics you want : ");
        scanf("%d", &que);
        sn[s] = ++s; // store serial number
        strcpy(product[p++], "Lipstics"); // store product name
        quentity[q++] = que; // store quantity in kg
        price[pr++] = que * 20; // Stores item price
        bill = bill + que * 20; // Updates total bill
        count++;
    }else if (cc == 303){
        printf("\nNailpolish is a good choice how many Nailpolishes you want : ");
        scanf("%d", &que);
        sn[s] = ++s; // store serial number
        strcpy(product[p++], "NailPolish"); // store product name
        quentity[q++] = que; // store quantity in kg
        price[pr++] = que * 30; // Stores item price
        bill = bill + que * 30; // Updates total bill
        count++;
    }else if (cc == 304){
        printf("\nFacewash is a good choice how many Facewash you want : ");
        scanf("%d", &que);
        sn[s] = ++s; // store serial number
        strcpy(product[p++], "FaceWadh"); // store product name
        quentity[q++] = que; // store quantity in kg
        price[pr++] = que * 70; // Stores item price
        bill = bill + que * 70; // Updates total bill
        count++;
    }else if (cc == 305){
        printf("\nLotion is a good choice how many Lotions you want : ");
        scanf("%d", &que);
        sn[s] = ++s; // store serial number
        strcpy(product[p++], "Lotion"); // store product name
        quentity[q++] = que; // store quantity in kg
        price[pr++] = que * 120; // Stores item price
        bill = bill + que * 120; // Updates total bill
        count++;
    }else{
        printf("\ninvalid choice\n");
    }
}
// for masala powders
void Masala_Powder()
{
    int mc, que; // Displays available masala Shows price per kg mc = masala code , que = quantity
    printf("\n============================================== Greate choice select a masala =============================================\n");
    printf("\n401) Turmeric----------------------------------1kg------------------------------RS.200");
    printf("\n402) Ginger------------------------------------1kg------------------------------RS.350");
    printf("\n403) Chilli------------------------------------1kg------------------------------RS.100");
    printf("\n404) Coriender---------------------------------1kg------------------------------RS.140");
    printf("\n405) Veg---------------------------------------1kg------------------------------RS.60");
    printf("\nplease choose your product code : ");
    scanf("%d", &mc);
    if (mc == 401){
        printf("\nTurmeric is a good choice how many kgs you want : ");
        scanf("%d", &que);
        sn[s] = ++s; // store serial number
        strcpy(product[p++], "Turmeric"); // store product name
        quentity[q++] = que; // store quantity in kg
        price[pr++] = que * 200; // Stores item price
        bill = bill + que * 200; // Updates total bill
        count++;
    }else if (mc == 402){
        printf("\nGinger is a good choice how many kgs you want : ");
        scanf("%d", &que);
        sn[s] = ++s; // store serial number
        strcpy(product[p++], "Ginger"); // store product name
        quentity[q++] = que; // store quantity in kg
        price[pr++] = que * 350; // Stores item price
        bill = bill + que * 350; // Updates total bill
        count++;
    }else if (mc == 403){
        printf("\nChilli is a good choice how many kgs you want : ");
        scanf("%d", &que);
        sn[s] = ++s; // store serial number
        strcpy(product[p++], "Chilli"); // store product name
        quentity[q++] = que; // store quantity in kg
        price[pr++] = que * 100; // Stores item price
        bill = bill + que * 100; // Updates total bill
        count++;
    }else if (mc == 404){
        printf("\nCoriender is a good choice how many kgs you want : ");
        scanf("%d", &que);
        sn[s] = ++s; // store serial number
        strcpy(product[p++], "Coriender"); // store product name
        quentity[q++] = que; // store quantity in kg
        price[pr++] = que * 140; // Stores item price
        bill = bill + que * 140; // Updates total bill
        count++;
    }else if (mc == 405){
        printf("\nVeg is a good choice how many kgs you want : ");
        scanf("%d", &que);
        sn[s] = ++s; // store serial number
        strcpy(product[p++], "veg"); // store product name
        quentity[q++] = que; // store quantity in kg
        price[pr++] = que * 60; // Stores item price
        bill = bill + que * 60; // Updates total bill
        count++;
    }else{
        printf("\ninvalid choice\n");
    }
}
// for store
void store_menu()
{
    printf("\n============================================== Available products in store =============================================\n");
    printf("\n1) Fruits");
    printf("\n2) Vegetables");
    printf("\n3) Cosmaticks");
    printf("\n4) Masala Powder");
    int ch;
    printf("\n\nEnter your choice : ");
    scanf("%d", &ch);
    switch (ch){
    case 1:
        Fruits();
        break;
    case 2:
        Vegetables();
        break;
    case 3:
        Cosmaticks();
        break;
    case 4:
        Masala_Powder();
        break;
    default:
        printf("\nInvalid choice please start from begining\n");
        break;
    }
}
int main(int argc, char const *argv[])
{
    int ch, shop;
    int ch2;
    time_t t; // data type defined in <time.h>
    t = time(NULL); // returns the current system time
    struct tm tm = *localtime(&t); // converts raw seconds into human-readable date & time
    printf("\n================================================ WELCOME TO AJ&S STORES ================================================\n");
    printf("\nWe are a small team that Provide our customers with the freshest, organically grown fruits, vegetables and spices also we \nprovide cosmaticks for your skin which is purely natural. Offer foods without artificial colors, flavors, or additives.\nSell earth-friendly cleansers; pure, natural supplements; and gentle,cruelty-free body care products. Support organic \nfarms that keep our earth and water pure.");
    printf("\n\nPRESS 1 TO SHOP");
    printf("\nPRESS 0 TO EXIT\n");
    scanf("%d", &ch);
    while (1){
        printf("\nif you want to continue shopping press       : 1.");
        printf("\nif you want to see your bill press           : 2.");
        printf("\nif you want to check History and data press  : 3");
        printf("\nif you want to exit press                    : 0\n");
        scanf("%d", &shop);
        switch (shop){
        case 1:
            store_menu();
            break;
        case 2:
            fflush(stdin);
            printf("\nEnter your name : ");
            gets(name);
            fflush(stdin);
            printf("\nEnter your address : ");
            gets(add);
            fflush(stdin);
            printf("\nEnter your contact number : ");
            scanf("%lld", &num);
            printf("\n======================================== THANK YOU TO VISIT AJ&S STORES ================================================\n\n");
            printf("SN    PRODUCT            QUENTITY            PRICE\n");
            printf("------------------------------------------------------");
            for (int i = 0; i < count; i++)
            {
                printf("\n%d) | %-20s| %dkg    |          RS.%-5d|\n", sn[i], product[i], quentity[i], price[i]);
                printf("------------------------------------------------------");
            }
            printf("\nName               : %s", name);
            printf("\nAddress            : %s", add);
            printf("\nContact no         : %lld", num);
            printf("\nYour total bill is : RS.%d", bill);
            int discount = (bill * 5) / 100;
            total = bill - discount;
            printf("\nYou have received a discount of 5%% : RS.%d", discount);
            printf("\nYour final bill is : RS.%d", (bill - discount));
            printf("\nThank you for shopping you saved RS.%d\n", discount);
            FILE *fp;
            sdata *s;
            s = (sdata *)calloc(1, sizeof(sdata));
            fp = fopen("storedata.txt", "a");
            int i = 0;
            strcpy(s[i].name, name);
            strcpy(s[i].address, add);
            s[i].number = num;
            s[i].day = tm.tm_mday;
            s[i].month = tm.tm_mon + 1;
            s[i].year = tm.tm_year + 1900;
            s[i].total_bill = total;
            s[i].hr = tm.tm_hour;
            s[i].min = tm.tm_min;
            s[i].sec = tm.tm_sec;
            fwrite(&s[i], sizeof(sdata), 1, fp);
            fclose(fp);
            break;
        case 3:
            do
            {
                printf("\n1 : DISPLAY");
                printf("\n2 : APPENED");
                printf("\n3 : NO. OF RECORDS");
                printf("\n4 : SEARCH");
                printf("\n5 : UPDATE");
                printf("\n6 : DELETE");
                printf("\n7 : SORT BY BILL DESC - ON SCREEN");
                printf("\n8 : SORT BY TOTAL DESC - IN FILE");
                printf("\n9 : SORT BY NAME ASC - ON SCREEN");
                printf("\n0 : EXIT");

                printf("\nenter your choice : ");
                scanf("%d", &ch2);

                switch (ch2)
                {
                case 1:
                    display();
                    break;
                case 2:
                    appened();
                    break;
                case 3:
                    noofrecords();
                    break;
                case 4:
                    search();
                    break;
                case 5:
                    update();
                    break;
                case 6:
                    delete ();
                    break;
                case 7:
                    sort_total_on_screen();
                    break;
                case 8:
                    sort_total_in_file();
                    break;
                case 9:
                    sort_name_on_screen();
                    break;
                default:
                    break;
                }
            } while (ch2 != 0);

            break;
        case 0:
            exit(0);
            break;
        default:
            printf("\ninvalid choice\n");
        }
    }
    return 0;
}
