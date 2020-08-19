#include "polymorphism_defs.h"
#include <stdio.h>
#include <stdlib.h>

int next_id = 0; /*for DefaultTextFormatter*/

/*/// TextFormatter Defs ///////////*/

funcPtr textFormatter_VT[] =
        {
                textFormatter_Dtor,
                textFormatter_Print
        };

void textFormatter_Dtor(TextFormatter * const textFormatter)
{}

void textFormatter_Print(TextFormatter * const textFormatter, const char* text)
{}

/*/// DefaultTextFormatter Defs ///////////*/

funcPtr DefaultTextFormatter_VT[] =
        {
                DefaultTextFormatter_Dtor,
                DefaultTextFormatter_Print
        };

void DefaultTextFormatter_Ctor(DefaultTextFormatter * const this)
{
    this->textFormatter.vt = DefaultTextFormatter_VT;

    this->id = next_id++;

    printf("--- DefaultTextFormatter Default CTOR\n########## C %d ##########\n", this->id);
}

void DefaultTextFormatter_CopyCtor(DefaultTextFormatter * const this, const DefaultTextFormatter *const other)
{
    this->textFormatter.vt = other->textFormatter.vt;

    this->id = next_id++;

    printf("--- DefaultTextFormatter Copy CTOR, from id: %d\n########## C %d ##########\n", other->id, this->id);
}

DefaultTextFormatter* DefaultTextFormatter_AssimentOperator(DefaultTextFormatter * const this, const DefaultTextFormatter *const other)
{
    this->textFormatter.vt = other->textFormatter.vt;

    printf("--- DefaultTextFormatter operator=(), from id: %d to id: %d\n", other->id, this->id);

    return this;
}

void DefaultTextFormatter_Dtor(DefaultTextFormatter * const this)
{
    printf("--- DefaultTextFormatter DTOR\n########## D %d ##########\n", this->id);

    this->textFormatter.vt = textFormatter_VT;

    this->textFormatter;
}

void DefaultTextFormatter_Print(const DefaultTextFormatter * const this, const char* text)
{
    printf("%-60s |", "[DefaultTextFormatter::print(const char*)]");
    printf("%s\n", text);
}

DefaultTextFormatter* generateFormatterArray()
{
    return malloc(sizeof(DefaultTextFormatter) * 3);
}

/*/// PrePostFixer Defs ///////////*/

funcPtr PrePostFixer_VT[] =
        {
                PrePostFixer_Dtor,
                PrePostFixer_print_c,
                PrePostFixer_Print_lc,
                (funcPtr)PrePostFixer_getDefaultSymbol
        };

void PrePostFixer_Ctor_cc(PrePostFixer *const this, const char* prefix, const char* postfix)
{
    DefaultTextFormatter_Ctor((DefaultTextFormatter *)this);

    this->defaultTextFormatter.textFormatter.vt = PrePostFixer_VT;

    this->pre = prefix;
    this->post = postfix;

    printf("--- PrePostFixer CTOR: \"%s\"...\"%s\"\n", this->pre, this->post);
}

void PrePostFixer_Dtor(PrePostFixer *const this)
{
    printf("--- PrePostFixer DTOR: \"%s\"...\"%s\"\n", this->pre, this->post);

    this->defaultTextFormatter.textFormatter.vt = DefaultTextFormatter_VT;

    DefaultTextFormatter_Dtor((DefaultTextFormatter *)this);
}

void PrePostFixer_Print_lc(PrePostFixer *const this, long num, char symbol)
{
    printf("%-60s | ", "[PrePostFixer::print(long, char)]");
    printf("-->\n");

    if (symbol)
    {
        printf("%-60s | ", "[PrePostFixer::print_num(long, char)]");
        printf("%s%c%ld%s\n", this->pre, symbol, num, this->post);
    }
    else
    {
        printf("%-60s | ", "[PrePostFixer::print_num(long)]");
        printf("%s%ld%s\n", this->pre, num, this->post);
    }
}

void PrePostFixer_print_c(const PrePostFixer *const this, char* text)
{
    printf("%-60s | ", "[PrePostFixer::print(const char*)]");
    printf("%s%s%s\n", this->pre, text, this->post);
}

char PrePostFixer_getDefaultSymbol(const PrePostFixer *const this) /*inline*/
{
    return '\0';
}

/*/// PrePostDollarFixer Defs ///////////*/

funcPtr PrePostDollarFixer_VT[] =
        {
                PrePostDollarFixer_Dtor,
                PrePostFixer_print_c,
                PrePostDollarFixer_Print_lc,
                PrePostDollarFixer_GetDefaultSymbol
        };


void PrePostDollarFixer_Ctor_cc(PrePostDollarFixer *const this, const char* prefix, const char* postfix)
{
    PrePostFixer_Ctor_cc((PrePostFixer*)this, prefix, postfix);

    this->postFixer.defaultTextFormatter.textFormatter.vt = PrePostDollarFixer_VT;

    printf("--- PrePostDollarFixer CTOR: \"%s\"...\"%s\"\n", this->postFixer.pre, this->postFixer.post);
}

void PrePostDollarFixer_CopyCtor(PrePostDollarFixer *const this, PrePostDollarFixer *const other)
{
    DefaultTextFormatter_CopyCtor(this, other);

    this->postFixer.pre = other->postFixer.pre;
    this->postFixer.post = other->postFixer.post;

    this->postFixer.defaultTextFormatter.textFormatter.vt = PrePostDollarFixer_VT;

    printf("--- PrePostDollarFixer Copy CTOR: \"%s\"...\"%s\"\n", this->postFixer.pre, this->postFixer.post);
}

void PrePostDollarFixer_Dtor(PrePostDollarFixer *const this)
{
    printf("--- PrePostDollarFixer DTOR: \"%s\"...\"%s\"\n", this->postFixer.pre, this->postFixer.post);

    this->postFixer.defaultTextFormatter.textFormatter.vt = PrePostFixer_VT;

    PrePostFixer_Dtor((PrePostFixer *)this);
}

void PrePostDollarFixer_Print_ic(const PrePostDollarFixer * const  this, int num, char symbol)
{
    printf("%-60s | ", "[PrePostDollarFixer::print(int, char)]");
    printf("-->\n");

    /*PrePostDollarFixer_Print_lc(this, (long)num, symbol);*/
    this->postFixer.defaultTextFormatter.textFormatter.vt[2](this, (long)num, symbol);
}

void PrePostDollarFixer_Print_lc(const PrePostDollarFixer * const this, long num, char symbol)
{
    printf("%-60s | ", "[PrePostDollarFixer::print(long, char)]");
    printf("-->\n");

    PrePostFixer_Print_lc((PrePostFixer *)this, num, symbol);
}

void PrePostDollarFixer_Print_dc(const PrePostDollarFixer * const this, double num, char symbol)
{
    printf("%-60s | ", "[PrePostDollarFixer::print(double, char)]");
    printf("%s%c%f%s\n", this->postFixer.pre, symbol, num, this->postFixer.post);
}

char PrePostDollarFixer_GetDefaultSymbol(const PrePostDollarFixer *const this)
{
    return '$';
}

/*/// PrePostHashFixer Defs ///////////*/

funcPtr PrePostHashFixer_VT[] =
        {
                PrePostHashFixer_Dtor,
                PrePostFixer_print_c,
                PrePostHashFixer_Print_lc,
                (funcPtr *)PrePostHashFixer_GetDefaultSymbol
        };

void PrePostHashFixer_Ctor_i(PrePostHashFixer * const this, int prc)
{
    PrePostDollarFixer_Ctor_cc((PrePostDollarFixer *)this,"===> ", " <===");

    this->postDollarFixer.postFixer.defaultTextFormatter.textFormatter.vt = PrePostHashFixer_VT;

    this->precision = prc;

    printf("--- PrePostHashFixer CTOR: \"%s\"...\"%s\", precision: %d\n", this->postDollarFixer.postFixer.pre, this->postDollarFixer.postFixer.post, this->precision);

    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");

    printf("%s[%c%.*f]%s\n", this->postDollarFixer.postFixer.pre, '$', this->precision, 9999.9999, this->postDollarFixer.postFixer.post);
}

void PrePostHashFixer_Dtor(PrePostHashFixer *const  this)
{
    printf("--- PrePostHashFixer DTOR: \"%s\"...\"%s\"\n", this->postDollarFixer.postFixer.pre, this->postDollarFixer.postFixer.post);

    this->postDollarFixer.postFixer.defaultTextFormatter.textFormatter.vt = PrePostDollarFixer_VT;

    PrePostDollarFixer_Dtor((PrePostDollarFixer *)this);
}

void PrePostHashFixer_Print_ic(const PrePostHashFixer * const this, int num, char symbol)
{
    printf("%-60s | ", "[PrePostHashFixer::print(int, char)]");
    printf("-->\n");

    /*print((double)num, symbol);*/
    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");

    printf("%s[%c%.*f]%s\n", this->postDollarFixer.postFixer.pre, symbol, this->precision, (double )num, this->postDollarFixer.postFixer.post);
}

void PrePostHashFixer_Print_lc(const PrePostHashFixer * const this, long num, char symbol)
{
    printf("%-60s | ", "[PrePostHashFixer::print(long, char)]");
    printf("-->\n");

    /*print((double)num, symbol);*/
    printf("%-60s | ", "[PrePostHashFixer::print(double, char)]");

    printf("%s[%c%.*f]%s\n", this->postDollarFixer.postFixer.pre, symbol, this->precision, (float )num, this->postDollarFixer.postFixer.post);
}

char PrePostHashFixer_GetDefaultSymbol(const PrePostHashFixer * const this)
{
    return '#';
}
/*/// PrePostFloatDollarFixer Defs ///////////*/

funcPtr PrePostFloatDollarFixer_VT[] =
        {
                PrePostFloatDollarFixer_Dtor,
                PrePostFixer_print_c,
                PrePostDollarFixer_Print_lc,
                (funcPtr)PrePostFloatDollarFixer_GetDefaultSymbol
        };

void PrePostFloatDollarFixer_Ctor_cc(PrePostFloatDollarFixer * const  this, const char* prefix, const char* postfix)
{
    PrePostDollarFixer_Ctor_cc((PrePostDollarFixer *)this, prefix, postfix);

    this->postDollarFixer.postFixer.defaultTextFormatter.textFormatter.vt = PrePostFloatDollarFixer_VT;

    printf("--- PrePostFloatDollarFixer CTOR: \"%s\"...\"%s\"\n", this->postDollarFixer.postFixer.pre, this->postDollarFixer.postFixer.post);
}

void PrePostFloatDollarFixer_Dtor(PrePostFloatDollarFixer *const  this)
{
    printf("--- PrePostFloatDollarFixer DTOR: \"%s\"...\"%s\"\n", this->postDollarFixer.postFixer.pre, this->postDollarFixer.postFixer.post);

    this->postDollarFixer.postFixer.defaultTextFormatter.textFormatter.vt = PrePostDollarFixer_VT;

    PrePostDollarFixer_Dtor((PrePostDollarFixer *)this);
}

void PrePostFloatDollarFixer_Print_f(const PrePostFloatDollarFixer * const this, float num)
{
    printf("%-60s | ", "[PrePostFloatDollarFixer::print(float)]");
    printf("-->\n");

    PrePostFloatDollarFixer_Print_fc(this, num, '@');
}

char PrePostFloatDollarFixer_GetDefaultSymbol(const PrePostFloatDollarFixer * const this)
{
    return '@';
}

void PrePostFloatDollarFixer_Print_fc(const PrePostFloatDollarFixer * const this, float num, char symbol)
{
    printf("%-60s | ", "[PrePostFloatDollarFixer::print(float, char)]");

    printf("%s%c%.2f%s\n", this->postDollarFixer.postFixer.pre, symbol, num, this->postDollarFixer.postFixer.post);
}

/*/// PrePostChecker Defs ///////////*/

funcPtr PrePostChecker_VT[] =
        {
                PrePostChecker_Dtor,
                PrePostFixer_print_c,
                PrePostDollarFixer_Print_lc,
                (funcPtr)PrePostFloatDollarFixer_GetDefaultSymbol
        };

void PrePostChecker_Ctor(PrePostChecker * const this)
{
    PrePostFloatDollarFixer_Ctor_cc((PrePostFloatDollarFixer *)this, "[[[[ ", " ]]]]");

    this->postFloatDollarFixer.postDollarFixer.postFixer.defaultTextFormatter.textFormatter.vt = PrePostChecker_VT;

    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n",this->postFloatDollarFixer.postDollarFixer.postFixer.pre, this->postFloatDollarFixer.postDollarFixer.postFixer.post);
}

void PrePostChecker_Dtor(PrePostChecker * const this)
{
    printf("--- PrePostChecker CTOR: \"%s\"...\"%s\"\n", this->postFloatDollarFixer.postDollarFixer.postFixer.pre, this->postFloatDollarFixer.postDollarFixer.postFixer.post);

    this->postFloatDollarFixer.postDollarFixer.postFixer.defaultTextFormatter.textFormatter.vt = PrePostFloatDollarFixer_VT;

    PrePostFloatDollarFixer_Dtor((PrePostFloatDollarFixer *)this);
}

void PrePostChecker_PrintThisSymbolUsingFunc(const PrePostChecker * const this)
{
    printf("%-60s | ", "[PrePostChecker::printThisSymbolUsingFunc()]");

    printf("Default symbol is %c\n", PrePostFloatDollarFixer_GetDefaultSymbol((PrePostFloatDollarFixer *)this));
}

void PrePostChecker_PrintThisSymbolDirectly(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printThisSymbolDirectly()]");

    printf("Default symbol is %c\n", '@');
}

void PrePostChecker_PrintDollarSymbolByCastUsingFunc(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByCastUsingFunc()]");

    printf("Default symbol is %c\n", ((char(*)())((PrePostDollarFixer *)this)->postFixer.defaultTextFormatter.textFormatter.vt[3])(this));
}

void PrePostChecker_PrintDollarSymbolByScopeUsingFunc(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByScopeUsingFunc()]");

    printf("Default symbol is %c\n", PrePostDollarFixer_GetDefaultSymbol((PrePostDollarFixer *)this));
}

void PrePostChecker_PrintDollarSymbolByCastDirectly(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByCastDirectly()]");

    printf("Default symbol is %c\n", ('$'));
}

void PrePostChecker_PrintDollarSymbolByScopeDirectly(const PrePostChecker *const this)
{
    printf("%-60s | ", "[PrePostChecker::printDollarSymbolByScopeDirectly()]");

    printf("Default symbol is %c\n", '$');
}


/*/// Multiplier Defs ///////////*/

funcPtr Multiplier_VT[] =
        {
                Multiplier_Dtor,
                Multiplier_Print
        };

void Multiplier_Dtor(Multiplier *const this)
{
    printf("--- Multiplier DTOR: times = %d\n", this->times);

    this->defaultTextFormatter.textFormatter.vt = DefaultTextFormatter_VT;

    DefaultTextFormatter_Dtor((DefaultTextFormatter *)this);
}

void Multiplier_Print(Multiplier *const this, const char* text)
{
    int i = 0;
    printf("%-60s | ", "[Multiplier::print(const char*)]");

    for ( ; i < this->times; ++i)
        printf("%s", text);

    printf("\n");
}


