#ifndef struct_h
#define struct_h

typedef struct {
    int customerID;
    char firstName[50];
    char lastName[50];
    char contactInfo[100];
} Customer;

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    char title[100];
    float rentalPrice;
} Game;

typedef struct {
    int rentalID;
    Customer customer;
    Game game;
    Date rentalDate;
    Date returnDate;
} Rental;

#endif 
