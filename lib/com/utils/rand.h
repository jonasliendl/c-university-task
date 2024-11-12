#define DIGITS_MIN 1
#define DIGITS_MAX 9
/*
Diese Funktion generiert eine Zufällige Zahl.
Receives the number of digits

Parameter:
    places=0 for init,
    places=1..9 for generating a random number with given places.
    A false number of places will be corrected.
Return value:
    An unsigned integer with given positions (0 - 999 999 999).
    The number of positions can be less if the number starts with 0.
Calling RandZ(1+RandZ(2)%9) generates a random number
    with random number of positions.
Calling RandZ(RandZ(9)) includes the random initialising.
*/
unsigned int RandZ(unsigned char);