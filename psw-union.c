#include <stdio.h>

typedef union
{
    unsigned char byte;

    struct
    {
        unsigned char P   : 1;
        unsigned char OV  : 1;
        unsigned char RS0 : 1;
        unsigned char RS1 : 1;
        unsigned char F0  : 1;
        unsigned char AC  : 1;
        unsigned char CY  : 1;
        unsigned char bit7: 1;
    } bits;

} PSW;

int main()
{
    PSW psw;

    psw.byte = 0x00;

    printf("Initial PSW : 0x%02X\n", psw.byte);

    /* Set Carry */
    psw.bits.CY = 1;
    printf("\nSet Carry\n");
    printf("PSW : 0x%02X\n", psw.byte);

    /* Set Overflow */
    psw.bits.OV = 1;
    printf("\nSet Overflow\n");
    printf("PSW : 0x%02X\n", psw.byte);

    /* Select Register Bank 2 */
    psw.bits.RS0 = 0;
    psw.bits.RS1 = 1;
    printf("\nSelect Register Bank 2\n");
    printf("PSW : 0x%02X\n", psw.byte);

    /* Clear Carry */
    psw.bits.CY = 0;
    printf("\nClear Carry\n");
    printf("PSW : 0x%02X\n", psw.byte);

    return 0;
}
