#include <stdlib.h>

#include "cpp2c.h"

#define SIZE 4

int main()
{
   int i =0;
   /* line 1*/
   Minibus_t m = {0};
   MinibusCtor(&m);

   /* line 2*/
   mi_print_info(&m);

   /* line 3*/
   PublicTransport_t tmp = i_print_info_pt(3);
   tmp.vptr->display_t(&tmp);
   TransportDtor(&tmp); 

   /* line 4*/
   Minibus_t * minibus1 = ( Minibus_t *) malloc(sizeof(Minibus_t));
   MinibusCtor(minibus1);

   Taxi_t * taxi = (Taxi_t *) malloc(sizeof(Taxi_t));
   TaxiCtor(taxi);
   
   Minibus_t * minibus2 = ( Minibus_t *) malloc(sizeof(Minibus_t));
   MinibusCtor(minibus2);

   PublicTransport_t *array[] = { (PublicTransport_t *)minibus1, (PublicTransport_t *)taxi, (PublicTransport_t *)minibus2 };
   
   /* first for */
   for (i = 0; i < 3; i++)
   {
      array[i]->vptr->display_t(array[i]);
   }

   for (i = 0; i < 3; i++)
   {
      array[i]->vptr->dtor_t(array[i]);
      free(array[i]);
   }
   
   /* second loop */
   PublicTransport_t arr2[] = {{0}, {0}, {0}};
   Minibus_t mini = {0};
   MinibusCtor(&mini);
   TransportCCtor(&arr2[0],(PublicTransport_t *)&mini);
   MinibusDtor(&mini);

   Taxi_t t ={0};
   TaxiCtor(&t);
   TransportCCtor(&arr2[1], (PublicTransport_t *)&t);
   TaxiDtor(&t);

   PublicTransport_t pt ={0};
   TransportCtor(&pt);
   arr2[2] = pt;


   for (i = 0; i < 3; i++)
   {
      arr2[i].vptr->display_t(&arr2[i]);
   }
   
   pt_print_info(&arr2[0]);
   print_count();

   Minibus_t m2 = {0};
   MinibusCtor(&m2);
   print_count();

   Minibus_t arr3[4] = {{0}, {0} ,{0} ,{0}};
   for (i = 0; i < 4; i++)
   {
      MinibusCtor(&arr3[i]);
   }
   
   Taxi_t *arr4 = (Taxi_t *) malloc(sizeof(Taxi_t ) *4);
   for (i = 0; i < 4; i++)
   {
      TaxiCtor(&arr4[i]);
   }

   for (int i = 3; i >= 0; i--)
   {
      TaxiDtor(&arr4[i]);
   }
   free(arr4);
   
   printf("%d \n", max_func_int(1, 2));
   printf("%d \n", max_func_int(1, 2.0f));


   Special_Taxi_t st={0};
   STaxiCtor(&st);
   taxi_display(st.taxi); 
   
   PublicConvoy_t *ts1 = malloc(sizeof(PublicConvoy_t));
   ConvoyCtor(ts1);

   PublicConvoy_t *ts2 = malloc(sizeof(PublicConvoy_t));
   ConvoyCCtor(ts2, ts1);

   ts1->PublicTransport.vptr->display_t(ts1);
   ts2->PublicTransport.vptr->display_t(ts2);

   ts1->PublicTransport.vptr->dtor_t(ts1);
   ts2->PublicTransport.vptr->display_t(ts2);
   ts2->PublicTransport.vptr->dtor_t(ts2);



   /* clean up */ 

   STaxiDtor(&st);

   for (i = 3; i >= 0; i--)
   {
      MinibusDtor(&arr3[i]);
   }

   MinibusDtor(&m2);
   
   for (int i = 2; i >= 0; i--) 
   {
      TransportDtor(&arr2[i]);
   }

   MinibusDtor(&m);

   
    return 0;


}