#include <stdio.h>

typedef struct VTable VTable_t;

typedef struct PublicTransport PublicTransport_t;
typedef struct Minibus Minibus_t;
typedef struct Taxi Taxi_t;
typedef struct Special_Taxi Special_Taxi_t;
typedef struct PublicConvoy PublicConvoy_t;





struct VTable
{
    void (*display_t)(void *);
    void (*wash_t)(void *, int minutes);
    void (*dtor_t) (void*);
};

int max_func_int(int t1, int t2);

void pt_print_info(void * pt);
void v_print_info(void);
void mi_print_info(Minibus_t * m);
PublicTransport_t i_print_info_pt(int i);
void taxi_display(Taxi_t s);




/********************************PublicTransport******************/

struct PublicTransport
{
    VTable_t * vptr;
    int m_license_plate;
};

void TransportDisplay(void *transport);
void TransportCtor(PublicTransport_t *transport);
void TransportCCtor(PublicTransport_t *this, PublicTransport_t *other);
void TransportDtor(void *transport);
void print_count();
int get_ID(PublicTransport_t *transport);

/********************************Minibus******************/

struct Minibus
{
    PublicTransport_t PublicTransport;
    int m_numSeats;
};

void MinibusDisplay(void *minibus);
void MinibusCtor(Minibus_t *minibus);
void MinibusCCtor(Minibus_t *this, Minibus_t *other);
void MinibusDtor(void *minibus);
void wash(void * minibus, int minutes);

/********************************Taxi******************/
struct Taxi
{
   PublicTransport_t PublicTransport;
};

void TaxiDisplay(void *taxi);
void TaxiCtor(Taxi_t *taxi);
void TaxiCCtor(Taxi_t *this, Taxi_t *other);
void TaxiDtor(void *taxi);

/********************************SpeicalTaxi******************/

struct Special_Taxi
{
   Taxi_t taxi;
};

void STaxiDisplay(void *staxi);
void STaxiCtor(Special_Taxi_t *staxi);
void STaxiCCtor(Special_Taxi_t *this, Special_Taxi_t *other);
void STaxiDtor(void *staxi);

/********************************Convoy******************/
struct PublicConvoy
{
    PublicTransport_t PublicTransport;
    PublicTransport_t *m_pt1;
    PublicTransport_t *m_pt2;
    Minibus_t m_m;
    Taxi_t m_t;
};

void ConvoyDisplay(void *convoy);
void ConvoyCtor(PublicConvoy_t *convoy);
void ConvoyCCtor(PublicConvoy_t *this, PublicConvoy_t *other);
void ConvoyDtor(void *convoy);
