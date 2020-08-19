#ifndef __ENCAPSULATION_DEFS_H__
#define __ENCAPSULATION_DEFS_H__

typedef enum{
    FALSE,
    TRUE
} Bool;

/*/// Box ///////////*/

typedef struct Box{
    double length;
    double width;
    double height;
}Box;

void BOX_CTOR_BD_(Box * const this, double dim);
void BOX_CTOR_BDDD_(Box * const this, double l, double w, double h);

void BOX_DTOR_B_(Box * const this);

void BOX_OPERATOR_SELF_MULT_BD_(Box * const this, double mult);

void BOX_PRINT_B_(Box * const this);

/*/// Shelf ///////////*/

typedef struct Shelf{
    Box boxes[3];
}Shelf;


void SHELF_SETBOX_SICB_(Shelf * const this, int index, const Box *dims);
double SHELF_GETVOLUME_CS_(const Shelf * const this);
void SHELF_PRINT_CS_(const Shelf * const this);


#endif /* _ENCAPSULATION_DEFS_H__ */