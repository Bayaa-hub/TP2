#ifndef functions_h
#define functions_h
#include <struct.h>
#include <stdio.h>
#include <string.h>

Customer createCustomer();
Rental createRental();
int searchRental(int rentalID, Rental *foundRental);
#endif