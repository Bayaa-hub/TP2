#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "struct.h"

Customer createCustomer()
{
    Customer infocustomer;

    FILE *file = fopen("customer_info.bin", "r+b");
    if (file == NULL)
    {
        file = fopen("customer_info.bin", "w+b");

        Entete entete = {1, 0};
        Customer_Block b1;
        b1.NB = 0;

        fseek(file, 0, SEEK_SET);
        fwrite(&entete, sizeof(Entete), 1, file);

        fwrite(&b1, sizeof(Customer_Block), 1, file);
    }
    Entete entete;
    fseek(file, 0, SEEK_SET);
    fread(&entete, sizeof(Entete), 1, file);

    Customer_Block lastBlock;
    fseek(file, sizeof(Entete) + sizeof(Customer_Block) * (entete.nbblock - 1), SEEK_SET);
    fread(&lastBlock, sizeof(Customer_Block), 1, file);

    printf("Enter your first name:\n");
    scanf("%s", infocustomer.firstName);

    printf("Enter your last name:\n");
    scanf("%s", infocustomer.lastName);

    printf("Enter your ID:\n");
    scanf("%d", &infocustomer.customerID);

    printf("Enter your contact info:\n");
    scanf("%99s", infocustomer.contactInfo);

    if (lastBlock.NB < 204)
    {
        lastBlock.tab[lastBlock.NB] = infocustomer;
        lastBlock.NB += 1;

        fseek(file, sizeof(Entete) + sizeof(Customer_Block) * (entete.nbblock - 1), SEEK_SET);
        fwrite(&lastBlock, sizeof(Customer_Block), 1, file);
    }
    else
    {
        Customer_Block newBlock;
        newBlock.tab[0] = infocustomer;
        newBlock.NB = 1;

        fseek(file, 0, SEEK_END);
        fwrite(&newBlock, sizeof(Customer_Block), 1, file);

        entete.nbblock += 1;
        fseek(file, 0, SEEK_SET);
        fwrite(&entete, sizeof(Entete), 1, file);
    }

    entete.nins += 1;
    fseek(file, 0, SEEK_SET);
    fwrite(&entete, sizeof(Entete), 1, file);

    fclose(file);

    return infocustomer;
}

Game creategame()
{
    Game game_info;

    FILE *file = fopen("game_info.bin", "r+b");
    if (file == NULL)
    {
        file = fopen("game_info.bin", "w+b");

        Entete entete = {1, 0};
        Game_Block b1;
        b1.NB = 0;

        fseek(file, 0, SEEK_SET);
        fwrite(&entete, sizeof(Entete), 1, file);

        fwrite(&b1, sizeof(Game_Block), 1, file);
    }

    Entete entete;
    fseek(file, 0, SEEK_SET);
    fread(&entete, sizeof(Entete), 1, file);

    Game_Block lastBlock;
    fseek(file, sizeof(Entete) + sizeof(Game_Block) * (entete.nbblock - 1), SEEK_SET);
    fread(&lastBlock, sizeof(Game_Block), 1, file);

    printf("Enter the title of the game:\n");
    scanf("%99s", game_info.title);

    printf("Enter the rental price of the game:\n");
    scanf("%f", &game_info.rentalPrice);

    if (lastBlock.NB < 108)
    {
        lastBlock.tab[lastBlock.NB] = game_info;
        lastBlock.NB += 1;

        fseek(file, sizeof(Entete) + sizeof(Game_Block) * (entete.nbblock - 1), SEEK_SET);
        fwrite(&lastBlock, sizeof(Game_Block), 1, file);
    }
    else
    {

        Game_Block newBlock;
        newBlock.tab[0] = game_info;
        newBlock.NB = 1;

        fseek(file, 0, SEEK_END);
        fwrite(&newBlock, sizeof(Game_Block), 1, file);

        entete.nbblock += 1;
        fseek(file, 0, SEEK_SET);
        fwrite(&entete, sizeof(Entete), 1, file);
    }

    entete.nins += 1;
    fseek(file, 0, SEEK_SET);
    fwrite(&entete, sizeof(Entete), 1, file);

    fclose(file);

    return game_info;
}

int calculateDays(Date start, Date end)
{
    int days = (end.year - start.year) * 365 + (end.month - start.month) * 30 + (end.day - start.day);
    return days > 0 ? days : 0;
}

Rental createRental()
{
    Rental rental_info;

    FILE *file = fopen("rental_info.bin", "r+b");
    if (file == NULL)
    {
        file = fopen("rental_info.bin", "w+b");

        Entete entete = {1, 0};
        Rental_Block b1;
        b1.NB = 0;

        fseek(file, 0, SEEK_SET);
        fwrite(&entete, sizeof(Entete), 1, file);

        fwrite(&b1, sizeof(Rental_Block), 1, file);
    }

    Entete entete;
    fseek(file, 0, SEEK_SET);
    fread(&entete, sizeof(Entete), 1, file);

    Rental_Block lastBlock;
    fseek(file, sizeof(Entete) + sizeof(Rental_Block) * (entete.nbblock - 1), SEEK_SET);
    fread(&lastBlock, sizeof(Rental_Block), 1, file);

    printf("Enter rental ID:\n");
    scanf("%d", &rental_info.rentalID);

    rental_info.customer = createCustomer();
    rental_info.game = creategame();

    printf("Enter the rental date (day month year):\n");
    scanf("%d %d %d", &rental_info.rentalDate.day, &rental_info.rentalDate.month, &rental_info.rentalDate.year);

    printf("Enter the return date (day month year):\n");
    scanf("%d %d %d", &rental_info.returnDate.day, &rental_info.returnDate.month, &rental_info.returnDate.year);

    int rentalDays = calculateDays(rental_info.rentalDate, rental_info.returnDate);
    float totalPrice = rentalDays * rental_info.game.rentalPrice;

    printf("Total price for rental: %.2f\n", totalPrice);

    if (lastBlock.NB < 325)
    {
        lastBlock.tab[lastBlock.NB] = rental_info;
        lastBlock.NB += 1;

        fseek(file, sizeof(Entete) + sizeof(Rental_Block) * (entete.nbblock - 1), SEEK_SET);
        fwrite(&lastBlock, sizeof(Rental_Block), 1, file);
    }
    else
    {
        Rental_Block newBlock;
        newBlock.tab[0] = rental_info;
        newBlock.NB = 1;

        fseek(file, 0, SEEK_END);
        fwrite(&newBlock, sizeof(Rental_Block), 1, file);

        entete.nbblock += 1;
        fseek(file, 0, SEEK_SET);
        fwrite(&entete, sizeof(Entete), 1, file);
    }

    entete.nins += 1;
    fseek(file, 0, SEEK_SET);
    fwrite(&entete, sizeof(Entete), 1, file);

    fclose(file);

    return rental_info;
}

int searchRental(int rentalID, Rental *foundRental)
{

    FILE *file = fopen("rental_info.bin", "rb");
    if (file == NULL)
    {
        printf("Error: Could not open file.\n");
        return 0;
    }

    Entete entete;
    fseek(file, 0, SEEK_SET);
    fread(&entete, sizeof(Entete), 1, file);

    for (int i = 0; i < entete.nbblock; i++)
    {
        Rental_Block block;
        fseek(file, sizeof(Entete) + sizeof(Rental_Block) * i, SEEK_SET);
        fread(&block, sizeof(Rental_Block), 1, file);
        for (int j = 0; j < block.NB; j++)
        {
            if (block.tab[j].rentalID == rentalID)
            {
                *foundRental = block.tab[j];
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);
    printf("Rental with ID %d not found.\n", rentalID);
    return 0;
}