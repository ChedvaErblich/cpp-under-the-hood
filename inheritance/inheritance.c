#include <stdio.h>

#include "inheritance_defs.h"


void DOMATERIALS_()
{
    Materials mat;
    struct MatTest { Materials mat; Material_t mat_t;} MatTest ;
    Material_t mat1;
    const char* const names[] = { "Plastic", "Metal", "Wood", "Paper", "Other" };
    Material_t mat2;

    printf("\n--- Start doMaterials() ---\n\n");

    printf("Size of Materials: %lu\n", sizeof(Materials));
    printf("Size of mat: %lu\n", sizeof(mat));
    printf("Size of Materials::Types: %lu\n", sizeof(Types));
    printf("Size of Material_t: %lu\n", sizeof(Material_t));

    printf("Size of Materials + Material_t: %lu\n", sizeof(MatTest));

    mat1.material = OTHER;
    printf("Material created, set to %s\n", names[mat1.material]);

    mat2.material = METAL;
    printf("Material created, set to %s\n", names[mat2.material]);

    printf("\n--- End doMaterials() ---\n\n");
}

void DOPHYSICALBOX_()
{
    PhysicalBox pb1;
    PhysicalBox pb2;
    PhysicalBox pb3;
    PhysicalBox pb4;

    printf("\n--- Start doPhysicalBox() ---\n\n");

    PHYSICALBOX_CTOR_PBDDDT_(&pb1, 8, 6, 4, PLASTIC);

    PHYSICALBOX_CTOR_PBT_(&pb2, WOOD);

    PHYSICALBOX_CTOR_PBDDD_(&pb3, 7, 7, 7);

    printf("\npb4 is copy-constructed from pb1\n");
    pb4 = pb1;

    PHYSICALBOX_PRINTP_CPB_(&pb4);
    PHYSICALBOX_PRINTP_CPB_(&pb1);

    printf("pb4 %s pb1\n", TRUE ? "equals" : "does not equal");

    printf("\npb4 is copy-assigned from pb3\n");
    pb4 = pb3;

    PHYSICALBOX_PRINTP_CPB_(&pb4);
    PHYSICALBOX_PRINTP_CPB_(&pb3);

    printf("pb4 %s pb3\n", TRUE ? "equals" : "does not equal");

    printf("\n--- End doPhysicalBox() ---\n\n");

    PHYSICALBOX_DTOR_PB_(&pb4);
    PHYSICALBOX_DTOR_PB_(&pb3);
    PHYSICALBOX_DTOR_PB_(&pb2);
    PHYSICALBOX_DTOR_PB_(&pb1);
}

void DOWEIGHTBOX_()
{
    WeightBox pw1;
    WeightBox pw2;
    WeightBox pw3;
    WeightBox pw4;

    printf("\n--- Start doWeightBox() ---\n\n");

    WEIGHTBOX_CTOR_WBDDDD_(&pw1, 8, 6, 4, 25);

    WEIGHTBOX_CTOR_WBDDDD_(&pw2, 1, 2, 3, 0.0);

    WEIGHTBOX_CTOR_WBDDDD_(&pw3, 10, 20, 30, 15);

    printf("\npw4 is copy-constructed from pw1\n");

    WEIGHTBOX_CTOR_WBCWB_(&pw4, &pw1);

    WEIGHTBOX_PRINTW_CWB_(&pw4);
    WEIGHTBOX_PRINTW_CWB_(&pw1);
    printf("pw4 %s pw1\n", FALSE ? "equals" : "does not equal");

    printf("\npw4 is copy-assigned from pw3\n");
    WEIGHTBOX_ASSIGNMENT_OPERATOR_WBCWB_(&pw4, &pw3);
    WEIGHTBOX_PRINTW_CWB_(&pw4);
    WEIGHTBOX_PRINTW_CWB_(&pw3);
    printf("pw4 %s pw3\n", FALSE ? "equals" : "does not equal");

    printf("\n--- End doWeightBox() ---\n\n");

    WEIGHTBOX_DTOR_WB_(&pw4);
    WEIGHTBOX_DTOR_WB_(&pw3);
    WEIGHTBOX_DTOR_WB_(&pw2);
    WEIGHTBOX_DTOR_WB_(&pw1);
}


int main()
{
    printf("\n--- Start main() ---\n\n");

    DOMATERIALS_();

    DOPHYSICALBOX_();

    DOWEIGHTBOX_();

    printf("\n--- End main() ---\n\n");

    return 0;
}


