#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

//***************FUNCTION DECLARATION*****************
void homeScreen();
void loadItemData();
void loadCart();
void mainMenu();
void displayItems();
int addtoCart(int);
void signUp();
void signIn();
void signOut();
void openCart();
void removefromCart(int);
void clearCart();
void contactUs();

//********************STRUCTURES***********************
struct item
{
    int itemID;
    char itemName[20];
    int price;
    int discount;
    int gst;
    float buyPrice;
};

struct user
{
    char name[30];
    char address[70];
    char email[30];
    char username[15];
    char password[15];
    char number[11];
};

struct cart
{
    int itemId;
    char itemName[20];
    float buyprice;
};

//*********************GLOABAL VARIABLES**************************
struct item items[50];
struct user u;
struct cart c[50];
int isSignedIn = 0, itemsinCart = 0;

//************************MAIN FUNCTION****************************
void main(){
    homeScreen();
    mainMenu();
}

//************************HOME SCREEN*******************************
void homeScreen(){
    printf("==========================================\n");
    printf("==========================================\n");
    printf("||\t\t\t\t\t||\n");
    printf("||\t\t**********\t\t||\n");
    printf("||\t\tAK DRESSES\t\t||\n");
    printf("||\t\t**********\t\t||\n");
    printf("||\tInhale fashion, Exhale style\t||\n");
    printf("||\t\t\t\t\t||\n");
    printf("==========================================\n");
    printf("==========================================\n\n");
    printf("Press any key to continue : ");
    loadItemData();
    getch();
}

//******************LOADING DATA OF ITEM FILE***************************
void loadItemData(){
    int i=0;
    FILE *ptr;
    ptr=fopen("items.txt","r");

    //skipping first line from items.txt file by saving it in some random string
    char random[100];
    fgets(random, 100, ptr);
    //then loading items in array from second line
    while((fscanf(ptr, "%d %s %d %d", &items[i].itemID, items[i].itemName, &items[i].price, &items[i].discount))!=EOF){

        if(items[i].price > 500)
            items[i].gst=18;
        else
            items[i].gst=0;

        items[i].buyPrice = (items[i].price * (100+items[i].gst) / 100.0) * (100 - items[i].discount) / 100;  
        i++;
    }
    fclose(ptr);
}

//************************MAIN MENU WINDOW****************************
void mainMenu(){
    int opt;
    system("cls");
    printf("==================================================\n");
    printf("==================================================\n");
    printf("||\t\t\t\t\t\t||\n");
    printf("||\t\tOption     Function\t\t||\n");
    printf("||\t\t1.\tDisplay Items\t\t||\n");
    if(isSignedIn==0){
        printf("||\t\t2.\tSign Up\t\t\t||\n");
        printf("||\t\t3.\tSign In\t\t\t||\n");
    }
    else{
        printf("||\t\t2.\tSign Out\t\t||\n");
        printf("||\t\t3.\tCart\t\t\t||\n");
    }

    printf("||\t\t4.\tContact Us\t\t||\n");
    printf("||\t\t\t\t\t\t||\n");
    printf("==================================================\n");
    printf("==================================================\n\n");

    if(isSignedIn==1){
        printf("\nWelcome, %s\n", u.name);
        printf("Username : %s\n", u.username);
        printf("Email : %s\n", u.email);
    }

    printf("\nPlease enter you choice : ");
    scanf("%d", &opt);
    fflush(stdin);

    //<----------------------------SWITCH STATEMEMTNS---------------------------------->
    switch (opt)
    {
        case 1:
            system("cls");
            displayItems();
            break;
        case 2:
            system("cls");
            if(isSignedIn==0)
                signUp();
            else
                signOut();
            break;
        
        case 3:
            system("cls");
            if(isSignedIn==0)
                signIn();
            else
                openCart();
            break;

        case 4: 
            system("cls");
            contactUs();
            break;

        default:
            printf("\n\nInvalid Input!!\n\n");
            printf("Press any key to continue : ");
            getch();
            mainMenu();
    }
}

//************************DISPLAY ITEMS**************************

void displayItems(){
    printf("==================================\n");
    printf("==================================\n");
    printf("||\t\t\t\t||\n");
    printf("||\tOur Collections\t\t||\n");
    printf("||\t\t\t\t||\n");
    printf("==================================\n");
    printf("==================================\n\n");

    printf("\nITEM ID\t\tNAME\t\t\tPRICE(Rs.)\tDISCOUNT(%)\tGST(%)\tBUY PRICE(Rs.)\n");
    printf("==========================================================================================\n\n");

    int i=0, id;
    char shop;
    while(items[i].itemID){
        printf("%d\t\t%s\t\t%d\t\t%d\t\t%d\t%.2f\n", items[i].itemID, items[i].itemName, items[i].price, items[i].discount, items[i].gst, items[i].buyPrice);
        i++;
    }
    if(isSignedIn==0){
        printf("\n\nPlease Sign in to buy items!!\n\n");
        printf("Press any key to go to main menu : \n\n");
        getch();
        mainMenu();
    }
    else{
        C:
        printf("\n\nWrite the item id of an item to add it to cart : ");
        scanf("%d", &id);
        fflush(stdin);
        int res = addtoCart(id);
        if(res == 0){
            printf("\nInvalid item Id!! Enter a valid Id!!\n");
            goto C;
        }
        else{
            printf("\nItem added successfully!!\n");
        }
        fflush(stdin);
        printf("\nDo you want to do more shopping(y/n)?\n");
        scanf("%c", &shop);
        if(shop=='Y' || shop=='y')
            goto C;
        else
            mainMenu();
    }

}

//**************************SIGN UP*******************************

void signUp(){
    system("cls");
    int userNotExist=1;
    char username2[10];

    FILE *auth_ptr, *add_ptr, *name_ptr, *user_ptr, *email_ptr, *order_ptr;
    auth_ptr = fopen("E:\\C Project\\data\\authenticator.txt","a+");
    user_ptr = fopen("E:\\C Project\\data\\user.txt","a+");
    add_ptr = fopen("E:\\C Project\\data\\address.txt","a+");
    name_ptr = fopen("E:\\C Project\\data\\name.txt","a+");
    email_ptr = fopen("E:\\C Project\\data\\email_mob.txt","a+");

    A:
    printf("==========================\n");
    printf("==========================\n");
    printf("||\t\t\t||\n");
    printf("||\tSign Up\t\t||\n");
    printf("||\t\t\t||\n");
    printf("==========================\n");
    printf("==========================\n\n");
    fflush(stdin);
    printf("Please enter your name : ");
    scanf("%[^\n]s", u.name);
    fflush(stdin);
    printf("Please enter your address : ");
    scanf("%[^\n]s", u.address);
    fflush(stdin);
    printf("Please enter your mobile number : ");
    scanf("%s", u.number);
    fflush(stdin);
    printf("Please enter a username (spaces are not allowed) : ");
    scanf("%s", u.username);
    fflush(stdin);
    printf("Please enter your email address : ");
    scanf("%s", u.email);
    fflush(stdin);
    printf("Please enter password : ");
    scanf("%s", u.password);
    fflush(stdin);

    //<----------------CHECKING IF USERNAME ALREADY EXISTS------------------>
    while(fscanf(user_ptr, "%s", username2)!=EOF){
        userNotExist = strcmp(u.username, username2);
        if(userNotExist==0)
            break;
    }

    if(userNotExist==0){
        printf("\n\nUsername already exists!!\n");
        printf("Press any key to fill again : \n\n");
        getch();
        system("cls");
        goto A;
    }
    else{
        fprintf(auth_ptr, "%s\n", u.password);
        fprintf(user_ptr, "%s\n", u.username);
        fprintf(add_ptr, "%s\n", u.address);
        fprintf(name_ptr, "%s\n", u.name);
        fprintf(email_ptr, "%s %s\n", u.number, u.email);
        char base[100]="E:\\C Project\\Orders\\", temp_username[20];
        strcat(temp_username ,u.username);
        strcat(temp_username ,".txt");
        strcat(base ,temp_username);
        order_ptr = fopen(base, "a");

        fclose(auth_ptr);
        fclose(user_ptr);
        fclose(add_ptr);
        fclose(name_ptr);
        fclose(email_ptr);
        fclose(order_ptr);

        printf("\nSigned up Successfully!!\n");
        printf("\nPress any key to continue : !!\n");
        getch();
        mainMenu();
    }
}

//****************************SIGN IN**************************
void signIn(){

    int userFound = 0, row=0;
    char username[15], password[15];

    FILE *auth_ptr, *add_ptr, *name_ptr, *user_ptr, *email_ptr;
    
    B:
    auth_ptr = fopen("E:\\C Project\\data\\authenticator.txt","r");
    user_ptr = fopen("E:\\C Project\\data\\user.txt","r");
    add_ptr = fopen("E:\\C Project\\data\\address.txt","r");
    name_ptr = fopen("E:\\C Project\\data\\name.txt","r");
    email_ptr = fopen("E:\\C Project\\data\\email_mob.txt","r");

    system("cls");
    printf("==========================\n");
    printf("==========================\n");
    printf("||\t\t\t||\n");
    printf("||\tSign In\t\t||\n");
    printf("||\t\t\t||\n");
    printf("==========================\n");
    printf("==========================\n\n");
    fflush(stdin);
    
    printf("Please enter username : ");
    scanf("%s", username);
    printf("Please enter password : ");
    scanf("%s", password);

    while(
            (fscanf(user_ptr, "%s", u.username)!=EOF) && 
            (fscanf(auth_ptr, "%s", u.password)!=EOF)
        ){
        ++row;
        if(strcmp(username, u.username)==0 && strcmp(password, u.password)==0){
            userFound=1;
            break;
        }
    }
    fclose(user_ptr);
    fclose(auth_ptr);

    if(userFound==1){
        int i = 0; isSignedIn = 1;
        while (
            (fgets(u.address, sizeof(u.address), add_ptr)) &&
            (fgets(u.name, sizeof(u.name), name_ptr)) &&
            (fgets(u.number, sizeof(u.number)+1, email_ptr)) &&
            (fgets(u.email, sizeof(u.email), email_ptr))
        ) { 
            i++; 
            if(i == row ) 
                break;   
        } 
        fclose(add_ptr);
        fclose(name_ptr);
        fclose(email_ptr);
        

        printf("\n\nSigned In successfully!!\n\n");
        printf("\nPress any key to continue : \n");
        getch();
        loadCart();
        mainMenu();
    }
    else{
        fclose(add_ptr);
        fclose(name_ptr);
        fclose(email_ptr);
        printf("Username or Password is incorrect!! \nTo try again press any key : ");
        getch();
        goto B;
    }   
}

//******************LOADING THE CART*************************
void loadCart(){
    itemsinCart=0;

    FILE *orders;
    char base[100]="E:\\C Project\\Orders\\", temp_username[30]="";
    strcat(temp_username ,u.username);
    strcat(temp_username ,".txt");
    strcat(base ,temp_username);

    orders = fopen(base,"r");

    while(fscanf(orders, "%d %s %f", &c[itemsinCart].itemId, c[itemsinCart].itemName, &c[itemsinCart].buyprice)!=EOF){
        ++itemsinCart;
    }
    fclose(orders);
}

//*****************ADDING INTO CART***************************
int addtoCart(int id){
    int i=0;

    FILE *orders;
    char base[100]="E:\\C Project\\Orders\\", temp_username[30]="";
    strcat(temp_username ,u.username);
    strcat(temp_username ,".txt");
    strcat(base ,temp_username);

    orders = fopen(base,"a+");
    
    while(items[i].itemID){
        if(items[i].itemID == id){
            fprintf(orders, "%d %s %.2f \n", items[i].itemID, items[i].itemName, items[i].buyPrice);
            fclose(orders);
            loadCart();
            return 1;
        }
        ++i;
    }
    fclose(orders);
    return 0;
}

//*****************OPENING THE CART***************************
void openCart(){

    int i=0, j=0, place, itemid, found=0;
    float totalPrice = 0;

    D:
    system("cls");
    printf("==========================\n");
    printf("==========================\n");
    printf("||\t\t\t||\n");
    printf("||\tYour Cart\t||\n");
    printf("||\t\t\t||\n");
    printf("==========================\n");
    printf("==========================\n\n");

    if(itemsinCart!=0){
        printf("\nITEM ID\t\tNAME\t\tBUY PRICE\n");
        printf("===========================================\n\n");

        while(i<itemsinCart){
            printf("%d \t\t %s \t %.2f\n", c[i].itemId, c[i].itemName, c[i].buyprice);
            totalPrice += c[i].buyprice;
            i++;
        }

        printf("\n===========================================\n");
        printf("\tTOTAL PRICE : %.2f\n", totalPrice);
        printf("===========================================\n\n");

        printf("1. Place your order.\n");
        printf("2. Remove any item.\n");
        printf("3. Go Back.\n");
        printf("Enter your choice : ");
        scanf("%d", &place);
        fflush(stdin);

        switch (place)
        {
        case 1:
            printf("\n\nYour order has been placed!!\n\n");
            clearCart();
            printf("Press any key to continue : ");
            getch();
            goto D;
            break;
        case 2:
            printf("Enter item id of item to be removed : ");
            scanf("%d", &itemid);

            while(j<itemsinCart){
                if(c[j].itemId == itemid){
                    found = 1;
                    break;
                }
                j++;
            }

            if(found == 0){
                printf("\n\nInvalid Id!!\n\n");
                printf("Press any key to continue : ");
                getch();
                openCart();
            }
            else{
                removefromCart(itemid);
                printf("\n\nItem is successfully removed!!\n\n");
                printf("Press any key to continue : ");
                getch();
                openCart();
            }
            break;
        case 3:
            mainMenu();
            break;
        default:
            printf("\nInvalid choice!!\n\n");
            printf("Press any key continue : ");
            getch();
            openCart();
            break;
        }
        
    }
    else{
        printf("\nCart is empty!! Add some Items!!\n\n");
        printf("Press any key to go back : ");
        getch();
        mainMenu();
    }
}

//*****************CLEARING THE CART***************************
void clearCart(){

    FILE *order_ptr;
    char base[100]="E:\\C Project\\Orders\\", temp_username[20];
    strcat(temp_username ,u.username);
    strcat(temp_username ,".txt");
    strcat(base ,temp_username);
    order_ptr = fopen(base, "w");
    fclose(order_ptr);
    loadCart();
}

//********REMOVING PARTICULAR ITEM FROM THE CART***************
void removefromCart(int id){
    int i=0;

    FILE *orders;
    char base[100]="E:\\C Project\\Orders\\", temp_username[30]="";
    strcat(temp_username ,u.username);
    strcat(temp_username ,".txt");
    strcat(base ,temp_username);

    orders = fopen(base,"w");

    while(i<itemsinCart){
        if(c[i].itemId != id)
            fprintf(orders, "%d %s %.2f \n", c[i].itemId, c[i].itemName, c[i].buyprice);
        i++;
    }
    
    fclose(orders);
    loadCart();
}

//************************SIGN OUT*****************************
void signOut(){
    isSignedIn=0;
    mainMenu();
}

//************************CONTACT US****************************
void contactUs(){
    printf(" =========================================================\n");
    printf(" =========================================================\n");
    printf(" ||\t\t\t\t\t\t\t||\n");
    printf(" ||\t\t\tContact Us\t\t\t||\n");
    printf(" ||\t\t______________________________\t\t||\n");
    printf(" ||\t\t\t\t\t\t\t||\n");
    printf(" ||\t\tPhone: 000-700-0501-020\t\t\t||\n");
    printf(" ||\t\tMON-FRI: 09:00 AM TO 20:00 PM\t\t||\n");
    printf(" ||\t\tSAT: 09:30 AM TO 18:30 PM\t\t||\n");
    printf(" ||\t\t______________________________\t\t||\n");
    printf(" ||\t\t\t\t\t\t\t||\n");
    printf(" ||\t\tEmail: akdresses1999@gmail.com\t\t||\n");
    printf(" ||\t\t______________________________\t\t||\n");
    printf(" ||\t\t\t\t\t\t\t||\n");
    printf(" ||\t\tFacebook: Ak Dresses\t\t\t||\n");
    printf(" ||\t\tInstagram: ak_dresses_1999\t\t||\n");
    printf(" ||\t\tTwitter: ak_dresses_1999\t\t||\n");
    printf(" ||\t\t\t\t\t\t\t||\n");

    printf(" =========================================================\n");
    printf(" =========================================================\n\n");

    printf("Press any key to go back : ");
    getch();
    mainMenu();

}