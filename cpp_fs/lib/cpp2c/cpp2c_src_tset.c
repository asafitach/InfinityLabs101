#include <stdio.h>
#include <stdlib.h>
#include "cpp2c_src.h"



int main(int argc, char **argv, char **envp)
{
    minibus_t m;
    minibus_t mtmp;
    taxi_t ttmp;
    int i;
    public_transportation_t tmp;
    public_transportation_t tmp2;
    public_transportation_t *array[3];

    // v_table_t *mini = &g_minibus_v_ptr;
    // v_table_t *tax = &g_taxi_v_ptr;
    // v_table_t *pt = &g_public_transportation_v_ptr;

    CtorMinibus(&m);
    Mprint_info(&m);
    tmp = PTRprint_info(3);
    CCtorPublicTransport(&tmp2, &tmp);
    DtorMinibus((minibus_t *)&tmp);
    PTdisplay(&tmp2);
    DtorPublicTransport(&tmp2);
    array[0] = malloc(sizeof(minibus_t)); 
    array[1] = malloc(sizeof(taxi_t));
    array[2] = malloc(sizeof(minibus_t));


    CtorMinibus((minibus_t *)array[0]);
    CtorTaxi((taxi_t *)array[1]);
    CtorMinibus((minibus_t *)array[2]);

    for (i = 0; i < 3; ++i) {
        (array[i])->virtual_function->display(array[i]);
    }

    DtorMinibus((minibus_t *)array[0]);
    DtorTaxi((taxi_t *)array[1]);
    DtorMinibus((minibus_t *)array[2]);



    for ( i = 0; i < 3; ++i) {
        free(array[i]);
    }

    public_transportation_t arr2[3] = {0};
    CtorMinibus(&mtmp);
    CCtorPublicTransport(&arr2[0], (public_transportation_t *)&mtmp);
    DtorMinibus(&mtmp);
    CtorTaxi(&ttmp);
    CCtorPublicTransport(&arr2[1], (public_transportation_t *)&ttmp);
    DtorTaxi(&ttmp);
    CtorPublicTransport(&arr2[2]);

    for (i = 0; i < 3; ++i) {
        arr2[i].virtual_function->display(&arr2[i]);
    }

    PTprint_info(&arr2[0]);
    print_info();

    minibus_t m2;
    CtorMinibus(&m2);
    print_info();
    
    minibus_t arr3[4];
    for (i = 0; i < 4; ++i)
    {
        CtorMinibus(&arr3[i]);
    }

    taxi_t *arr4 = malloc(sizeof(taxi_t) * 4);
    for (i = 0; i < 4; ++i)
    {
        CtorTaxi(arr4 + i);
    }

    for (i = 0; i < 4; ++i)
    {
        DtorTaxi(arr4 + 3 -i);
    }

    free(arr4);

    printf("%d\n", max_func(1, 2));
    printf("%d\n", max_func(1, 2.0));

    spacial_taxi_t st;
    CtorSpacialTaxi(&st);
    CCtorTaxi(&ttmp, (taxi_t *)&st);
    taxi_display(&ttmp);
    DtorTaxi(&ttmp);

    public_convoy_t *ts1 = malloc(sizeof(public_convoy_t));
    public_convoy_t *ts2 = malloc(sizeof(public_convoy_t));

    CtorPublicConvoy(ts1);
    ((public_transportation_t *)ts1)->virtual_function->display(ts1);
    CCtorPublicConvoy(ts2, ts1);

     ((public_transportation_t *)ts2)->virtual_function->display(ts2);

    DtorPublicConvoy(ts1);
    free(ts1);

    ((public_transportation_t *)ts2)->virtual_function->display(ts2);
   
    DtorPublicConvoy(ts2);
    free(ts2); 

    /********************** defualt destructors ************************/
    
    DtorSpacialTaxi(&st);

    for (i = 0; i < 4; ++i)
    {
        DtorMinibus(&arr3[3-i]);
    }

    DtorMinibus(&m2);

    for (i = 2; i >= 0; --i)
    {
        DtorPublicTransport(&arr2[i]);
    }

    DtorMinibus(&m);

    return 0;
}