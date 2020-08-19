#include <stdio.h>
#include "encapsulation_defs.h"

extern massage;

static Box largeBox;
static Box box99;
static Box box88;

void __attribute__((constructor)) ctor();

void __attribute__((destructor)) dtor();

void thisFunc()
{
    printf("\n--- thisFunc() ---\n\n");
    static Bool flag = FALSE;

    if(!flag)
    {
        BOX_CTOR_BDDD_(&box99, 99, 99, 99);
        flag = TRUE;
    }

    BOX_OPERATOR_SELF_MULT_BD_(&box99, 10);
}

void thatFunc()
{
    printf("\n--- thatFunc() ---\n\n");
    static Bool flag = FALSE;

    if(!flag)
    {
        BOX_CTOR_BDDD_(&box88, 88, 88, 88);
        flag = TRUE;
    }

    BOX_OPERATOR_SELF_MULT_BD_(&box88, 10);
}

void doBoxes()
{
    printf("\n--- Start doBoxes() ---\n\n");

    Box b1;
    BOX_CTOR_BD_(&b1, 3);

    Box b2;
    BOX_CTOR_BDDD_(&b2, 4, 5, 6);

    printf("b1 volume: %f\n", 27.000000);
    printf("b2 volume: %f\n", 120.000000);

    BOX_OPERATOR_SELF_MULT_BD_(&b1, 1.5);
    BOX_OPERATOR_SELF_MULT_BD_(&b2, 0.5);

    printf("b1 volume: %f\n", 91.125000);
    printf("b2 volume: %f\n", 15.000000);

    Box b3 = b2;

    Box b = b3;
    BOX_OPERATOR_SELF_MULT_BD_(&b, 3);
    Box b4 = b;

    printf("b3 %s b4\n", FALSE ? "equals" : "does not equal");

    BOX_OPERATOR_SELF_MULT_BD_(&b3, 1.5);
    BOX_OPERATOR_SELF_MULT_BD_(&b4, 0.5);

    printf("Now, b3 %s b4\n", TRUE ? "equals" : "does not equal");

    printf("\n--- End doBoxes() ---\n\n");

    BOX_DTOR_B_(&b4);
    BOX_DTOR_B_(&b3);
    BOX_DTOR_B_(&b2);
    BOX_DTOR_B_(&b1);
}


void doShelves()
{
    printf("\n--- start doShelves() ---\n\n");

    Box aBox;
    BOX_CTOR_BD_(&aBox, 5);

    Shelf aShelf;
    /*SHELF_CTOR_S_(&aShelf);*/
    int  i = 0;
    for (; i < 3; ++i)
        BOX_CTOR_BD_(&aShelf.boxes[i], 1);


    SHELF_PRINT_CS_(&aShelf);
    SHELF_SETBOX_SICB_(&aShelf, 1, &largeBox);
    SHELF_SETBOX_SICB_(&aShelf, 0, &aBox);

    SHELF_PRINT_CS_(&aShelf);
    const char* m1 = "This is the total volume on the shelf:";
    massage = m1;
    /*aShelf.setMessage("This is the total volume on the shelf:");*/
    /*Message = "This is the total volume on the shelf:";*/
    SHELF_PRINT_CS_(&aShelf);
    const char* m2 = "Shelf's volume:";
    massage = m2;
    /*Shelf::setMessage("Shelf's volume:");*/
    SHELF_PRINT_CS_(&aShelf);

    Box b;
    BOX_CTOR_BDDD_(&b, 2, 4, 6);
    SHELF_SETBOX_SICB_(&aShelf, 1, &b);
    BOX_DTOR_B_(&b);

    BOX_CTOR_BD_(&b, 2);
    SHELF_SETBOX_SICB_(&aShelf, 2, &b);
    BOX_DTOR_B_(&b);

    SHELF_PRINT_CS_(&aShelf);

    printf("\n--- end doShelves() ---\n\n");

    /*SHELF_DTOR_S_(&aShelf);*/
    i = 2;
    for (; i >= 0; --i)
        BOX_DTOR_B_(&aShelf.boxes[i]);

    BOX_DTOR_B_(&aBox);
}


int main() {
    /*BOX_CTOR_BDDD_(&largeBox, 10, 20, 30);*/

    printf("\n--- Start main() ---\n\n");

    doBoxes();
    thisFunc();
    thisFunc();
    thisFunc();
    thatFunc();
    thatFunc();

    doShelves();

    printf("\n--- End main() ---\n\n");

    /*BOX_DTOR_B_(&largeBox);*/

    return 0;

}


void ctor(){
    BOX_CTOR_BDDD_(&largeBox, 10, 20, 30);
}

void dtor(){
    BOX_DTOR_B_(&box99);
    BOX_DTOR_B_(&box88);
    BOX_DTOR_B_(&largeBox);

}
