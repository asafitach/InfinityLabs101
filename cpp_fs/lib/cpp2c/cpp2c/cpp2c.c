
#include <stdlib.h>
#include "cpp2c.h"

static int s_count = 0;

int max_func_int(int t1, int t2)
{
    return ((t1 > t2) ? t1 : t2);
}

void mi_print_info(Minibus_t * m)
{
    m->PublicTransport.vptr->wash_t(m, 3);
}

void pt_print_info(void * pt)
{
    PublicTransport_t *tmp = (PublicTransport_t *) pt;
    tmp->vptr->display_t(pt);
}

void v_print_info(void);
void mi_print_info(Minibus_t * m);
PublicTransport_t i_print_info_pt(int i)
{
    Minibus_t ret = {0};
    MinibusCtor(&ret);
    printf("print_info(int i)\n");
    ret.PublicTransport.vptr->display_t(&ret);

    PublicTransport_t copy_ret = {0};
    TransportCCtor(&copy_ret, &(ret.PublicTransport));
    MinibusDtor(&ret);
    return copy_ret;
}

void taxi_display(Taxi_t s)
{
    Taxi_t tmp = {0};
    TaxiCCtor(&tmp, &s);
    tmp.PublicTransport.vptr->display_t(&tmp);
    TaxiDtor(&tmp);
}


/********************************PublicTransport******************/
VTable_t g_transport_vptr = {TransportDisplay, NULL, TransportDtor};

void TransportDisplay(void * transport)
{
    printf("PublicTransport::display()");
    printf("%d \n", ((PublicTransport_t *)transport)->m_license_plate);
}

void TransportCtor(PublicTransport_t * transport)
{   
    transport->m_license_plate = ++s_count;
    transport->vptr = &g_transport_vptr;
    printf("PublicTransport::Ctor() %d \n", transport->m_license_plate);
}

void TransportCCtor(PublicTransport_t * this, PublicTransport_t * other)
{   
    (void) other;
    this->m_license_plate = ++s_count;
    this->vptr = &g_transport_vptr;
     printf("PublicTransport::CCtor() %d \n", this->m_license_plate);
}

void TransportDtor(void * transport)
{   
    --s_count;
    printf("PublicTransport::Dtor()");
    printf("%d \n", ((PublicTransport_t *)transport)->m_license_plate);
}

int get_ID(PublicTransport_t * transport)
{
    return transport->m_license_plate;
}

void print_count()
{
    printf("s_count  %d\n", s_count);
}

/********************************Minibus******************/

VTable_t g_minibus_vptr = {MinibusDisplay, wash, MinibusDtor};


void MinibusDisplay(void * minibus)
{
    printf("Minibus::display() ID %d", get_ID((PublicTransport_t *) minibus));
    printf(" num seats:%d \n", ((Minibus_t *)minibus)->m_numSeats);
}
void MinibusCtor(Minibus_t * minibus)
{
    TransportCtor((PublicTransport_t *) minibus);
    minibus->PublicTransport.vptr = &g_minibus_vptr;
    minibus->m_numSeats = 20;
    printf("Minibus::Ctor()\n");

}
void MinibusCCtor(Minibus_t * this, Minibus_t * other)
{
    TransportCCtor((PublicTransport_t *) this, (PublicTransport_t *) other);
    this->PublicTransport.vptr = &g_minibus_vptr;
    this->m_numSeats = other->m_numSeats;
    printf("Minibus::CCtor()\n");
}
void MinibusDtor(void * minibus)
{
    printf("Minibus::Dtor()\n");
    TransportDtor(minibus);
}

void wash(void * minibus, int minutes)
{
    printf("wash (%d) ID: %d\n", minutes, get_ID((PublicTransport_t *)minibus));
}

/********************************SpeicalTaxi******************/

VTable_t g_taxi_vptr = {TaxiDisplay, NULL, TaxiDtor};


void TaxiDisplay(void *taxi)
{
    printf("Taxi::display() ID %d\n", get_ID((PublicTransport_t *) taxi));
}
void TaxiCtor(Taxi_t *taxi)
{
    TransportCtor((PublicTransport_t *) taxi);
    taxi->PublicTransport.vptr = &g_taxi_vptr;
    printf("Taxi::Ctor()\n");
}
void TaxiCCtor(Taxi_t *this, Taxi_t *other)
{
    TransportCCtor((PublicTransport_t *) this, (PublicTransport_t *) other);
    this->PublicTransport.vptr = &g_taxi_vptr;
    printf("Taxi::CCtor()\n");
}
void TaxiDtor(void *taxi)
{
    printf("Taxi::Dtor()\n");
    TransportDtor(taxi);
}

/********************************Taxi******************/

VTable_t g_staxi_vptr = {STaxiDisplay, NULL, STaxiDtor};


void STaxiDisplay(void *staxi)
{
    printf("SpecialTaxi::display() ID %d\n", get_ID((PublicTransport_t *) staxi));
}
void STaxiCtor(Special_Taxi_t *staxi)
{
    TaxiCtor((Taxi_t *) staxi);
    staxi->taxi.PublicTransport.vptr = &g_staxi_vptr;
    printf("SpecialTaxi::Ctor()\n");
}
void STaxiCCtor(Special_Taxi_t *this, Special_Taxi_t *other)
{
    TaxiCCtor((Taxi_t *) this, (Taxi_t *) other);
    this->taxi.PublicTransport.vptr = &g_staxi_vptr;
    printf("SpecialTaxi::CCtor()\n");
}
void STaxiDtor(void *staxi)
{
    printf("SpecialTaxi::Dtor()\n");
    TaxiDtor(staxi);
}
/********************************Convoy******************/
VTable_t g_convoy_vptr = {ConvoyDisplay, NULL, ConvoyDtor};


void ConvoyDisplay(void *convoy)
{
    PublicConvoy_t *con = (PublicConvoy_t *) convoy;
    con->m_pt1->vptr->display_t(con->m_pt1);
    con->m_pt2->vptr->display_t(con->m_pt2);
    con->m_m.PublicTransport.vptr->display_t(&con->m_m);
    con->m_t.PublicTransport.vptr->display_t(&con->m_t);

}
void ConvoyCtor(PublicConvoy_t *convoy)
{
    Minibus_t * mini = NULL;
    Taxi_t * taxi = NULL;

    TransportCtor((PublicTransport_t *) convoy);

    mini = (Minibus_t *) malloc(sizeof(Minibus_t));
    MinibusCtor(mini);
    convoy->m_pt1 = (PublicTransport_t *) mini;

    taxi = (Taxi_t *) malloc(sizeof(Taxi_t));
    TaxiCtor(taxi);
    convoy->m_pt2 = (PublicTransport_t *)taxi;

    MinibusCtor(&convoy->m_m);
    TaxiCtor(&convoy->m_t);

    convoy->PublicTransport.vptr = &g_convoy_vptr;

}
void ConvoyCCtor(PublicConvoy_t *this, PublicConvoy_t *other)
{
   
    TransportCtor((PublicTransport_t *) this);
   
    this->m_pt1 = (PublicTransport_t *) malloc(sizeof(Minibus_t));
    MinibusCtor( (Minibus_t *)this->m_pt1);

    this->m_pt2 = (PublicTransport_t *) malloc(sizeof(Taxi_t));
    TaxiCtor((Taxi_t *)this->m_pt2);
    
    MinibusCCtor(&this->m_m, &other->m_m);
    TaxiCCtor(&this->m_t, &other->m_t);
    this->PublicTransport.vptr = &g_convoy_vptr;

}
void ConvoyDtor(void *convoy)
{
    PublicConvoy_t *con = (PublicConvoy_t *) convoy;
    MinibusDtor(con->m_pt1);
    free(con->m_pt1);

    TaxiDtor(con->m_pt2);
    free(con->m_pt2);

    TaxiDtor(&con->m_t);
    MinibusDtor(&con->m_m);

    TransportDtor(&con->PublicTransport);
}
