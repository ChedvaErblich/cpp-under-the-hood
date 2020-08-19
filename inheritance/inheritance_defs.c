#include <stdio.h>

#include "inheritance_defs.h"

/*/// PhysicalBox Defs ///////////*/

void PHYSICALBOX_CTOR_PBDDD_(PhysicalBox * const this, double l, double w, double h)
{
    BOX_CTOR_BDDD_((Box *)this, l, w, h);

    this->material.material = OTHER;

    printf("Material created, set to Other\n");

    PHYSICALBOX_PRINTP_CPB_(this);
}

void PHYSICALBOX_CTOR_PBDDDT_(PhysicalBox * const this, double l, double w, double h, Types t)
{
    const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };

    BOX_CTOR_BDDD_((Box *)this, l, w, h);

    this->material.material = t;

    printf("Material created, set to %s\n", names[t]);

    PHYSICALBOX_PRINTP_CPB_(this);
}
void PHYSICALBOX_CTOR_PBT_(PhysicalBox * const this, Types t)
{
    const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };

    BOX_CTOR_BD_((Box *)this, 1);

    this->material.material = t;

    printf("Material created, set to %s\n", names[t]);

    PHYSICALBOX_PRINTP_CPB_(this);
}

void PHYSICALBOX_DTOR_PB_(PhysicalBox * const this)
{
    const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };

    printf("PhysicalBox dtor, %f x %f x %f, ", this->box.length, this->box.width, this->box.height);

    printf("%s; ", names[this->material.material]);

    BOX_DTOR_B_((Box *)this);
}

void PHYSICALBOX_PRINTP_CPB_(const PhysicalBox * const this)
{
    const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };

    printf("PhysicalBox, made of %s; ", names[this->material.material]);
    BOX_PRINT_B_((Box *)this);
}

/*// WeightBox Defs ///////////*/

void WEIGHTBOX_CTOR_WBDDDD_(WeightBox * const this, double l, double w, double h, double wgt)
{
    BOX_CTOR_BDDD_((Box *)this, l, w, h);

    this->weight = wgt;

    WEIGHTBOX_PRINTW_CWB_(this);
}
void WEIGHTBOX_CTOR_WBCWB_(WeightBox * const this, const WeightBox * const other)
{
    BOX_CTOR_BD_((Box *)this, 1);

    this->weight = other->weight;

    WEIGHTBOX_PRINTW_CWB_(this);
}

void WEIGHTBOX_DTOR_WB_(WeightBox * const this)
{
    printf("Destructing WeightBox; ");
    WEIGHTBOX_PRINTW_CWB_(this);

    BOX_DTOR_B_((Box *)this);
}

WeightBox* WEIGHTBOX_ASSIGNMENT_OPERATOR_WBCWB_(WeightBox* const this, const WeightBox * const other)
{
    this->weight = other->weight;
    return this;
}

void WEIGHTBOX_PRINTW_CWB_(const WeightBox * const this)
{
    printf("WeightBox, weight: %f; ", this->weight);

    BOX_PRINT_B_((Box *)this);
}