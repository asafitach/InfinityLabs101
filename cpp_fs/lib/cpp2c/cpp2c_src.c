#include <stdio.h>
#include <stdlib.h>
#include "cpp2c_src.h"

int g_public_transportation_count = 0;


v_table_t g_public_transportation_v_ptr = {PTdisplay, NULL};
v_table_t g_public_convoy_v_ptr = {PCdisplay, NULL};
v_table_t g_minibus_v_ptr = {Mdisplay, Mwash};
v_table_t g_taxi_v_ptr = {Tdisplay, NULL};
v_table_t g_spacial_taxi_v_ptr = {STdisplay, NULL};

/*********************** public transport ************************************/
/*********************** basics **********************************************/

void CtorPublicTransport(public_transportation_t *this)
{
    this->m_license_plate = ++g_public_transportation_count;
    this->virtual_function = &g_public_transportation_v_ptr;

    printf("PublicTransport::Ctor()%d\n", this->m_license_plate);
}

void DtorPublicTransport(public_transportation_t *this)
{
    --g_public_transportation_count;
    printf("PublicTransport::Dtor()%d\n", this->m_license_plate);
}

void CCtorPublicTransport(public_transportation_t *this, const public_transportation_t *other)
{
    this->m_license_plate = ++g_public_transportation_count;
    this->virtual_function = &g_public_transportation_v_ptr;
    printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
}

/*********************** class methods ***************************************/
void PTdisplay(void *PT)
{
    printf("PublicTransport::display(): %d\n", (((public_transportation_t *)PT)->m_license_plate));
}

int get_ID(public_transportation_t *this)
{
    return (this->m_license_plate);
}

/*********************** minibus *********************************************/
/*********************** basics **********************************************/
void CtorMinibus(minibus_t *this)
{
    this->m_num_of_seats = 20;
    CtorPublicTransport(&(this->parrent));
    this->parrent.virtual_function = &g_minibus_v_ptr;
    printf("Minibus::Ctor()\n");
}

void CCtorMinibus(minibus_t *this, minibus_t *other)
{
    this->m_num_of_seats = 20;
    CCtorPublicTransport(&(this->parrent), &(other->parrent));
    this->parrent.virtual_function = &g_minibus_v_ptr;
    printf("Minibus::CCtor()\n");
}

void DtorMinibus(minibus_t *this)
{
    printf("Minibus::Dtor()\n");
    DtorPublicTransport(&(this->parrent));
}

/*********************** class methods ***************************************/
void Mdisplay(void *minibus)
{
    printf("Minibus::display() ID:%d num seats:%d\n", get_ID(&((minibus_t *)minibus)->parrent), (((minibus_t *)minibus)->m_num_of_seats));
}

void Mwash(void *minibus, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n", minutes, get_ID(&((minibus_t *)minibus)->parrent));
}

/*********************** taxi ************************************************/
/*********************** basics **********************************************/
void CtorTaxi(taxi_t *this)
{
    CtorPublicTransport(&(this->parrent));
    (this->parrent).virtual_function = &g_taxi_v_ptr;
    printf("Taxi::Ctor()\n");
}

void CCtorTaxi(taxi_t *this, taxi_t *other)
{
    CCtorPublicTransport(&(this->parrent), &(other->parrent));
    (this->parrent).virtual_function = &g_taxi_v_ptr;
    printf("Taxi::CCtor()\n");
}

void DtorTaxi(taxi_t *this)
{
    printf("Taxi::Dtor()\n");
    DtorPublicTransport(&(this->parrent));
}

/*********************** class methods ***************************************/
void Tdisplay(void *taxi)
{
    printf("Taxi::display() ID:%d\n", get_ID(&((taxi_t *)taxi)->parrent));
}


/*********************** special taxi ****************************************/
/*********************** basics **********************************************/
void CtorSpacialTaxi(spacial_taxi_t *this)
{
    CtorTaxi(&(this->parrent));
    (this->parrent).parrent.virtual_function = &g_spacial_taxi_v_ptr;
    printf("SpecialTaxi::Ctor()\n");
}

void CCtorSpacialTaxi(spacial_taxi_t *this, spacial_taxi_t *other)
{
    CCtorTaxi(&(this->parrent), &(other->parrent));
    (this->parrent).parrent.virtual_function = &g_spacial_taxi_v_ptr;
    printf("SpecialTaxi::CCtor()\n");
}    
    
void DtorSpacialTaxi(spacial_taxi_t *this)
{
    printf("SpecialTaxi::Dtor()\n");
    DtorTaxi(&(this->parrent));
}

/*********************** class methods ***************************************/
void STdisplay(void *s_taxi)
{
    printf("SpecialTaxi::display() ID:%d\n", get_ID(&((spacial_taxi_t *)s_taxi)->parrent.parrent));
}

/*********************** public convoy ***************************************/
/*********************** basics **********************************************/

void CtorPublicConvoy(public_convoy_t *this)
{
    CtorPublicTransport(&(this->parrent));

    this->m_ptr1 = (public_transportation_t *)malloc(sizeof(minibus_t));
    CtorMinibus((minibus_t *)(this->m_ptr1));

    this->m_ptr2 = (public_transportation_t *)malloc(sizeof(taxi_t));
    CtorTaxi((taxi_t *)(this->m_ptr2));

    CtorMinibus(&(this->m_m));
    CtorTaxi(&(this->m_t));
    this->parrent.virtual_function = &g_public_convoy_v_ptr;
}

void CCtorPublicConvoy(public_convoy_t *this, public_convoy_t *other)
{
    CCtorPublicTransport(&(this->parrent), &(other->parrent));

    CCtorMinibus(&(this->m_m), &(other->m_m));
    CCtorTaxi(&(this->m_t), &(other->m_t));

    this->m_ptr1 = (public_transportation_t *)malloc(sizeof(minibus_t));
    CCtorMinibus((minibus_t *)(this->m_ptr1), (minibus_t *)(other->m_ptr1));

    this->m_ptr2 = (public_transportation_t *)malloc(sizeof(taxi_t));
    CCtorTaxi((taxi_t *)(this->m_ptr2), (taxi_t *)(other->m_ptr2));
    this->parrent.virtual_function = &g_public_convoy_v_ptr;
}

void DtorPublicConvoy(public_convoy_t *this)
{
    DtorMinibus((minibus_t *)(this->m_ptr1));
    DtorTaxi((taxi_t *)(this->m_ptr2));
    DtorTaxi((taxi_t *)&(this->m_t));
    DtorMinibus((minibus_t *)&(this->m_m));
    DtorPublicTransport(&(this->parrent));
}

/*********************** class methods ***************************************/
void PCdisplay(void *public_convoy)
{
    public_convoy_t *pc = (public_convoy_t *)public_convoy;
    public_transportation_t *tmpp;

    tmpp = pc->m_ptr1;
    tmpp->virtual_function->display(tmpp);

    tmpp = pc->m_ptr2;
    tmpp->virtual_function->display(tmpp);

    tmpp = &(pc->m_m);
    tmpp->virtual_function->display(tmpp);

    tmpp = &(pc->m_t);
    tmpp->virtual_function->display(tmpp);
}

/*********************** global **********************************************/

void print_count()
{
    printf("g_public_transportation_count: %d\n", g_public_transportation_count);
}

void print_info()
{
    printf("s_count: %d\n", g_public_transportation_count);
}

int max_func(const int t1, const int t2)
{
    return ((t1 > t2) ? t1 : t2);
} 
void PTprint_info(public_transportation_t *a)
{
    a->virtual_function->display(a);
}


void Mprint_info(minibus_t *m)
{
    m->parrent.virtual_function->wash(m, 3);
}

public_transportation_t PTRprint_info(int i)/* Public Transportation Return */
{
    minibus_t ret = {0};
    CtorMinibus(&ret);
    printf("print_info(int i)\n");
    ret.parrent.virtual_function->display(&ret);

    public_transportation_t copy_ret = {0};
    CCtorPublicTransport(&copy_ret, &ret);
    DtorMinibus(&ret);
    return (copy_ret);
}

void taxi_display(taxi_t *s)
{
    s->parrent.virtual_function->display(s);
}

/*********************************************************/
