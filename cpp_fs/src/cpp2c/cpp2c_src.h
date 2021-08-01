#ifndef __ILRD_RD101_CPP2C__
#define __ILRD_RD101_CPP2C__

/*********************** v table *********************************************/
typedef struct v_table
{
    void(*display)(void *this);
    void(*wash)(void *minibus, int num);
}v_table_t;



/*********************** public transport ************************************/

typedef struct public_transportation
{
    v_table_t *virtual_function;
    int m_license_plate;
}public_transportation_t;

/*********************** function ********************************************/

void CtorPublicTransport(public_transportation_t *this);
void DtorPublicTransport(public_transportation_t *this);
void CCtorPublicTransport(public_transportation_t *this, const public_transportation_t *other);
void PTdisplay(void *PT);
int get_ID(public_transportation_t *this);



/*********************** minibus *********************************************/
typedef struct minibus
{
    public_transportation_t parrent;
    int m_num_of_seats;
}minibus_t;

/*********************** function **********************************************/
void CtorMinibus(minibus_t *this);
void CCtorMinibus(minibus_t *this, minibus_t *other);
void DtorMinibus(minibus_t *this);
void Mdisplay(void *minibus);
void Mwash(void *minibus, int minutes);



/*********************** taxi ************************************************/
typedef struct taxi
{
    public_transportation_t parrent;
}taxi_t;

/*********************** function **********************************************/
void CtorTaxi(taxi_t *this);
void CCtorTaxi(taxi_t *this, taxi_t *other);
void DtorTaxi(taxi_t *this);
void Tdisplay(void *taxi);



/*********************** special taxi ****************************************/
typedef struct spacial_taxi
{
    taxi_t parrent;
}spacial_taxi_t;

/*********************** function **********************************************/
void CtorSpacialTaxi(spacial_taxi_t *this);
void CCtorSpacialTaxi(spacial_taxi_t *this, spacial_taxi_t *other);
void DtorSpacialTaxi(spacial_taxi_t *this);
void STdisplay(void *s_taxi);

/*********************** public convoy ***************************************/
typedef struct public_convoy
{
    public_transportation_t parrent;
    public_transportation_t *m_ptr1;
    public_transportation_t *m_ptr2;
    minibus_t m_m;
    taxi_t m_t;
}public_convoy_t;

/*********************** function **********************************************/

void CtorPublicConvoy(public_convoy_t *this);
void CCtorPublicConvoy(public_convoy_t *this, public_convoy_t *other);
void DtorPublicConvoy(public_convoy_t *this);
void PCdisplay(void *public_convoy);

/*********************** global **********************************************/

void print_count();
void print_info();
int max_func(const int t1, const int t2);
void PTprint_info(public_transportation_t *a);
void Mprint_info(minibus_t *m);
public_transportation_t PTRprint_info(int i)/* Public Transportation Return */;
void taxi_display(taxi_t *s);


#endif /* __ILRD_RD101_CPP2C__ */
