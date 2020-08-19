#ifndef UNDER_THE_HOOD_2_INHERITANCE_DEFS_H
#define UNDER_THE_HOOD_2_INHERITANCE_DEFS_H

#include "encapsulation_defs.h"

/*/// Materials ///////////*/

typedef enum Types
{
    PLASTIC,
    METAL,
    WOOD,
    PAPER,
    OTHER
}Types;

typedef struct Materials
{
    char pad;
}Materials;

typedef struct Material_t
{
    Types material;
}Material_t;

/*/// PhysicalBox ///////////*/

typedef struct PhysicalBox
{
    Box box;

    Material_t material;
}PhysicalBox;

/*/// PhysicalBox Defs ///////////*/

void PHYSICALBOX_CTOR_PBDDD_(PhysicalBox * const this, double l, double w, double h);
void PHYSICALBOX_CTOR_PBDDDT_(PhysicalBox * const this, double l, double w, double h, Types t);
void PHYSICALBOX_CTOR_PBT_(PhysicalBox * const this, Types t);

void PHYSICALBOX_DTOR_PB_(PhysicalBox * const this);

void PHYSICALBOX_PRINTP_CPB_(const PhysicalBox * const this);

/*/// WeightBox ///////////*/

typedef struct WeightBox
{
    Box box;

    double weight;
}WeightBox;

/*/// WeightBox Defs ///////////*/

void WEIGHTBOX_CTOR_WBDDDD_(WeightBox * const this, double l, double w, double h, double wgt);
void WEIGHTBOX_CTOR_WBCWB_(WeightBox * const this, const WeightBox * const other);

void WEIGHTBOX_DTOR_WB_(WeightBox * const this);

WeightBox* WEIGHTBOX_ASSIGNMENT_OPERATOR_WBCWB_(WeightBox* const this, const WeightBox * const other);

void WEIGHTBOX_PRINTW_CWB_(const WeightBox * const this);


#endif /*UNDER_THE_HOOD_2_INHERITANCE_DEFS_H*/
