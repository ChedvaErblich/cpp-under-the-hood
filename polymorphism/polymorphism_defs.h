#ifndef UNDER_THE_HOOD3_POLYMORPHISM_DEFS_H
#define UNDER_THE_HOOD3_POLYMORPHISM_DEFS_H

typedef void(*funcPtr)();

/*/// TextFormatter ///////////*/

/*typedef struct TextFormatter_VT
{
    void (*dtor)(TextFormatter) ;
    void * print;
}TextFormatter_VT;*/

typedef struct TextFormatter
{
    funcPtr *vt;
}TextFormatter;

void textFormatter_Dtor(TextFormatter * const textFormatter);
void textFormatter_Print(TextFormatter * const textFormatter, const char* text);

/*/// DefaultTextFormatter ///////////*/

/*typedef struct DefaultTextFormatter_VT
{
    void *(dtor)(DefaultTextFormatter) ;
    void * print;
}DefaultTextFormatter_VT;*/

typedef struct Ider
{
    char pad;
}Ider;

typedef struct DefaultTextFormatter
{
    TextFormatter textFormatter;

    Ider ider;

    /*const*/ int id;
}DefaultTextFormatter;

void DefaultTextFormatter_Ctor(DefaultTextFormatter * const this);
void DefaultTextFormatter_CopyCtor(DefaultTextFormatter * const this, const DefaultTextFormatter *const other);
DefaultTextFormatter* DefaultTextFormatter_AssimentOperator(DefaultTextFormatter * const this, const DefaultTextFormatter *const other);
void DefaultTextFormatter_Dtor(DefaultTextFormatter * const this);
void DefaultTextFormatter_Print(const DefaultTextFormatter * const this, const char* text);
DefaultTextFormatter* generateFormatterArray();

/*/// PrePostFixer ///////////*/

/*typedef struct PrePostFixer_VT
{
    void * dtor;

    void * print;

    void * print_lc;
}PrePostFixer_VT;*/

typedef struct PrePostFixer
{
    DefaultTextFormatter defaultTextFormatter;

    const char* pre;
    const char* post;
}PrePostFixer;

void PrePostFixer_Ctor_cc(PrePostFixer *const this, const char* prefix, const char* postfix);
void PrePostFixer_Dtor(PrePostFixer *const this);
void PrePostFixer_Print_lc(PrePostFixer *const this, long num, char symbol);
void PrePostFixer_print_c(const PrePostFixer *const this, char* text);
char PrePostFixer_getDefaultSymbol(const PrePostFixer *const this); /*inline*/
/*/// PrePostDollarFixer ///////////*/

typedef struct PrePostDollarFixer
{
    PrePostFixer postFixer;
}PrePostDollarFixer;

/*/// PrePostDollarFixer Defs ///////////*/

void PrePostDollarFixer_Ctor_cc(PrePostDollarFixer *const this, const char* prefix, const char* postfix);
void PrePostDollarFixer_CopyCtor(PrePostDollarFixer *const this, PrePostDollarFixer *const other);
void PrePostDollarFixer_Dtor(PrePostDollarFixer *const this);
void PrePostDollarFixer_Print_ic(const PrePostDollarFixer * const  this, int num, char symbol);
void PrePostDollarFixer_Print_lc(const PrePostDollarFixer * const this, long num, char symbol);
void PrePostDollarFixer_Print_dc(const PrePostDollarFixer * const this, double num, char symbol);
char PrePostDollarFixer_GetDefaultSymbol(const PrePostDollarFixer *const this);

/*/// PrePostHashFixer ///////////*/

typedef struct PrePostHashFixer
{
    PrePostDollarFixer postDollarFixer;

    int precision;
}PrePostHashFixer;

/*/// PrePostHashFixer Defs ///////////*/

void PrePostHashFixer_Ctor_i(PrePostHashFixer * const this, int prc);
void PrePostHashFixer_Dtor(PrePostHashFixer *const  this);
void PrePostHashFixer_Print_ic(const PrePostHashFixer * const this, int num, char symbol);
void PrePostHashFixer_Print_lc(const PrePostHashFixer * const this, long num, char symbol);
char PrePostHashFixer_GetDefaultSymbol(const PrePostHashFixer * const this);

/*/// PrePostFloatDollarFixer ///////////*/

typedef struct PrePostFloatDollarFixer
{
    PrePostDollarFixer postDollarFixer;
}PrePostFloatDollarFixer ;

/*/// PrePostFloatDollarFixer Defs ///////////*/

void PrePostFloatDollarFixer_Ctor_cc(PrePostFloatDollarFixer * const  this, const char* prefix, const char* postfix);
void PrePostFloatDollarFixer_Dtor(PrePostFloatDollarFixer *const  this);
void PrePostFloatDollarFixer_Print_f(const PrePostFloatDollarFixer * const this, float num);
void PrePostFloatDollarFixer_Print_fc(const PrePostFloatDollarFixer * const this, float num, char symbol);
char PrePostFloatDollarFixer_GetDefaultSymbol(const PrePostFloatDollarFixer * const this);

/*/// PrePostChecker ///////////*/

typedef struct PrePostChecker
{
    PrePostFloatDollarFixer postFloatDollarFixer;
}PrePostChecker;


void PrePostChecker_Ctor(PrePostChecker * const this);
void PrePostChecker_Dtor(PrePostChecker * const this);
void PrePostChecker_PrintThisSymbolUsingFunc(const PrePostChecker * const this);
void PrePostChecker_PrintThisSymbolDirectly(const PrePostChecker *const this);
void PrePostChecker_PrintDollarSymbolByCastUsingFunc(const PrePostChecker *const this);
void PrePostChecker_PrintDollarSymbolByScopeUsingFunc(const PrePostChecker *const this);
void PrePostChecker_PrintDollarSymbolByCastDirectly(const PrePostChecker *const this);
void PrePostChecker_PrintDollarSymbolByScopeDirectly(const PrePostChecker *const this);

/*/// Multiplier ///////////*/

typedef struct  Multiplier
{
    DefaultTextFormatter defaultTextFormatter;

    int times;
}Multiplier;

/*/// Multiplier Defs ///////////*/

void Multiplier_Dtor(Multiplier *const this);
void Multiplier_Print(Multiplier *const this, const char* text);

#endif /*/UNDER_THE_HOOD3_POLYMORPHISM_DEFS_H*/