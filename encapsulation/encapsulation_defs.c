#include <stdio.h>
#include "encapsulation_defs.h"

/*/// Box Defs ///////////*/

void BOX_CTOR_BD_(Box * const this, double dim){
    this->length = dim;
    this->width = dim;
    this->height = dim;

    BOX_PRINT_B_(this);
}

void BOX_CTOR_BDDD_(Box * const this, double l, double w, double h){
    this->length = l;
    this->width = w;
    this->height = h;

    BOX_PRINT_B_(this);
}

void BOX_DTOR_B_(Box * const this)
{
    printf("Box destructor, %f x %f x %f\n", this->width, this->height, this->length);
}


void BOX_OPERATOR_SELF_MULT_BD_(Box * const this, double mult)
{
    this->width *= mult;
    this->height *= mult;
    this->length *= mult;
}

void BOX_PRINT_B_(Box * const this){
    printf("Box: %f x %f x %f\n", this->length, this->width, this->height);
}

/*/// Shelf ///////////*/

const char* const DEF_MSG = "The total volume held on the shelf is";
const char *massage = DEF_MSG;

void SHELF_SETBOX_SICB_(Shelf * const this, int index, const Box *dims){
    this->boxes[index] = *dims;
}

double SHELF_GETVOLUME_CS_(const Shelf * const this){
    double vol = 0;
    size_t i = 0;
    for (; i < 3; ++i)
        vol += this->boxes[i].width * this->boxes[i].height * this->boxes[i].length;

    return vol;
}

void SHELF_PRINT_CS_(const Shelf * const this){
    printf("%s %f\n", massage, SHELF_GETVOLUME_CS_(this));
}