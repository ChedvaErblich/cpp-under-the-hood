#include "polymorphism_defs.h"
#include <stdio.h>
#include <stdlib.h>

extern Multiplier_VT;
void doPrePostFixer()
{
    PrePostFixer angleBrackets;

    printf("\n--- start doPrePostFixer() ---\n\n");

    PrePostFixer_Ctor_cc(&angleBrackets, "<<< ", " >>>");
    PrePostFixer_print_c(&angleBrackets, "Hello World!");
    PrePostFixer_Print_lc(&angleBrackets, -777, '\0');
    PrePostFixer_Print_lc(&angleBrackets, 350, '#');
    PrePostFixer_Print_lc(&angleBrackets, (long int)3.14, '\0');

    printf("\n--- end doPrePostFixer() ---\n\n");

    PrePostFixer_Dtor(&angleBrackets);
}

void doPrePostDollarFixer()
{
    PrePostDollarFixer asterisks;

    printf("\n--- start doPrePostDollarFixer() ---\n\n");

    PrePostDollarFixer_Ctor_cc(&asterisks, "***** ", " *****");
    PrePostDollarFixer_Print_ic(&asterisks, -777, '$');
    PrePostDollarFixer_Print_ic(&asterisks, 350, '#');
    PrePostDollarFixer_Print_dc(&asterisks, 3.14, '$');

    printf("\n--- end doPrePostDollarFixer() ---\n\n");

    PrePostDollarFixer_Dtor(&asterisks);
}

void doPrePostChecker()
{
    PrePostChecker check;

    printf("\n--- start doPrePostChecker() ---\n\n");

    PrePostChecker_Ctor(&check);
    PrePostChecker_PrintThisSymbolUsingFunc(&check);
    PrePostChecker_PrintThisSymbolDirectly(&check);
    PrePostChecker_PrintDollarSymbolByCastDirectly(&check);
    PrePostChecker_PrintDollarSymbolByScopeDirectly(&check);
    PrePostChecker_PrintDollarSymbolByCastUsingFunc(&check);
    PrePostChecker_PrintDollarSymbolByScopeUsingFunc(&check);

    printf("\n--- end doPrePostChecker() ---\n\n");

    PrePostChecker_Dtor(&check);
}

void doPrePostFloatDollarFixer()
{
    PrePostFloatDollarFixer hashes;
    PrePostDollarFixer hashes2;

    printf("\n--- start doPrePostFloatDollarFixer() ---\n\n");

    PrePostFloatDollarFixer_Ctor_cc(&hashes, "### ", " ###");
    PrePostFloatDollarFixer_Print_f(&hashes, -777);
    PrePostFloatDollarFixer_Print_fc(&hashes,350, '#');
    PrePostFloatDollarFixer_Print_f(&hashes, 3.14);

    PrePostDollarFixer_CopyCtor(&hashes2, &hashes);

    PrePostDollarFixer_Print_dc(&hashes2, 7.5, '$');
    PrePostDollarFixer_Print_ic(&hashes2,100, '$');

    printf("\n--- start doPrePostFloatDollarFixer() ---\n\n");

    PrePostDollarFixer_Dtor(&hashes2);
    PrePostFloatDollarFixer_Dtor(&hashes);
}

void runAsPrePostFixerRef(const PrePostFixer *const pp)
{
    printf("\n--- start runAsPrePostFixerRef() ---\n\n");

    pp->defaultTextFormatter.textFormatter.vt[2](pp, 123, '\0');

    printf("\n--- end runAsPrePostFixerRef() ---\n\n");
}

void runAsPrePostDollarFixerRef(const PrePostDollarFixer *const pp)
{
    printf("\n--- start runAsPrePostDollarFixerRef() ---\n\n");

    PrePostDollarFixer_Print_ic(pp, 123, '$');

    printf("\n--- end runAsPrePostDollarFixerRef() ---\n\n");
}

void runAsPrePostDollarFixerObj(const PrePostDollarFixer * const pp)
{
    PrePostDollarFixer tmp;
    PrePostDollarFixer_CopyCtor(&tmp, pp);

    printf("\n--- start runAsPrePostDollarFixerObj() ---\n\n");

    PrePostDollarFixer_Print_ic(&tmp ,123 , '$');

    printf("\n--- end runAsPrePostDollarFixerObj() ---\n\n");

    PrePostDollarFixer_Dtor(&tmp);
}

void runAsPrePostHashFixerRef(const PrePostHashFixer *const pp)
{
    printf("\n--- start runAsPrePostHashFixerRef() ---\n\n");

    PrePostHashFixer_Print_ic(pp, 123, '#');

    printf("\n--- end runAsPrePostHashFixerRef() ---\n\n");
}

void doMultiplier()
{
    Multiplier m1;
    Multiplier m2;
    Multiplier m3;
    Multiplier m4;

    printf("\n--- start doMultiplier() ---\n\n");

    DefaultTextFormatter_Ctor((DefaultTextFormatter *)&m1);
    m1.defaultTextFormatter.textFormatter.vt = Multiplier_VT;
    m1.times = 3;
    printf("--- Multiplier CTOR: times = %d\n", 3);

    DefaultTextFormatter_Ctor((DefaultTextFormatter *)&m2);
    m2.defaultTextFormatter.textFormatter.vt = Multiplier_VT;
    m2.times = 5;
    printf("--- Multiplier CTOR: times = %d\n", 5);

    DefaultTextFormatter_CopyCtor((DefaultTextFormatter *)&m3, (DefaultTextFormatter *)&m1);
    m3.defaultTextFormatter.textFormatter.vt = Multiplier_VT;
    m3.times = m1.times;

    DefaultTextFormatter_CopyCtor(&m4.defaultTextFormatter, &m2.defaultTextFormatter);
    m4.defaultTextFormatter.textFormatter.vt = Multiplier_VT;
    m4.times = m2.times;

    Multiplier_Print(&m1, "abc ");
    Multiplier_Print(&m2, "abc ");
    Multiplier_Print(&m3,"abc ");
    Multiplier_Print(&m4, "abc ");

    printf("\n--- start doMultiplier() ---\n\n");

    Multiplier_Dtor(&m4);
    Multiplier_Dtor(&m3);
    Multiplier_Dtor(&m2);
    Multiplier_Dtor(&m1);
}

void doFormatterArray()
{
    PrePostDollarFixer prePostDollarFixer;
    Multiplier multiplier;
    PrePostChecker prePostChecker;
    DefaultTextFormatter formatters[3];
    int i;

    printf("\n--- start doFormatterArray() ---\n\n");

    PrePostDollarFixer_Ctor_cc(&prePostDollarFixer, "!!! ", " !!!");
    DefaultTextFormatter_CopyCtor(&formatters[0], (DefaultTextFormatter*)&prePostDollarFixer);
    PrePostDollarFixer_Dtor(&prePostDollarFixer);

    DefaultTextFormatter_Ctor((DefaultTextFormatter*)&multiplier);
    multiplier.defaultTextFormatter.textFormatter.vt = Multiplier_VT;
    multiplier.times = 4;
    printf("--- Multiplier CTOR: times = %d\n", 4);

    DefaultTextFormatter_CopyCtor(&formatters[1], (DefaultTextFormatter*)&multiplier);
    Multiplier_Dtor(&multiplier);

    PrePostChecker_Ctor(&prePostChecker);
    DefaultTextFormatter_CopyCtor(&formatters[2], (DefaultTextFormatter*)&prePostChecker);
    PrePostChecker_Dtor(&prePostChecker);

    for (i = 0; i < 3; ++i)
        DefaultTextFormatter_Print(&formatters[i], "Hello World!");

    printf("\n--- end doFormatterArray() ---\n\n");

    for (i = 2; i >= 0; --i) {
        DefaultTextFormatter_Dtor(&formatters[i]);
    }
}



/*
void doFormatterPtrs()
{
    printf("\n--- start doFormatterPtrs() ---\n\n");

    DefaultTextFormatter* pfmt[] =
            {
                    new PrePostDollarFixer("!!! ", " !!!"),
            new Multiplier(4),
            new PrePostChecker()
            };

    for (int i = 0; i < 3; ++i)
        pfmt[i]->print("Hello World!");

    for (int i = 2; i >= 0; --i)
        delete pfmt[i];

    printf("\n--- end doFormatterPtrs() ---\n\n");
}
*/

void doFormatterDynamicArray()
{
    int i = 0;
    DefaultTextFormatter* formatters;

    printf("\n--- start doFormatterDynamicArray() ---\n\n");

    formatters = generateFormatterArray();

    for (; i < 3; ++i)
        DefaultTextFormatter_Ctor(&formatters[i]);

    for (i = 0; i < 3; ++i)
        DefaultTextFormatter_Print(&formatters[i], "Hello World!");

    for(i = 2; i >= 0; --i)
    {
        DefaultTextFormatter_Dtor(&formatters[i]);
    }

    free(&formatters[0]);
    /*free(&formatters[1]);
     free(&formatters[2]);*/
      printf("\n--- start doFormatterDynamicArray() ---\n\n");
  }

  int main()
  {
      PrePostHashFixer hfix;
      printf("\n--- Start main() ---\n\n");

      doPrePostFixer();
      doPrePostDollarFixer();
      doPrePostFloatDollarFixer();
      doPrePostChecker();

      PrePostHashFixer_Ctor_i(&hfix, 4);
      runAsPrePostFixerRef((PrePostFixer *)&hfix);
      runAsPrePostDollarFixerRef((PrePostDollarFixer *)&hfix);
      runAsPrePostDollarFixerObj((&(hfix.postDollarFixer)));
      runAsPrePostHashFixerRef(&hfix);

      doMultiplier();

       doFormatterArray();
      /*   doFormatterPtrs();*/
     doFormatterDynamicArray();

    printf("\n--- End main() ---\n\n");

    PrePostHashFixer_Dtor(&hfix);

    return 0;
}

