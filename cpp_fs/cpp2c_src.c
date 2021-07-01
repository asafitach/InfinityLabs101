#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>

int flag = 0;

void SignalHendler(int param)
{
    if (3 < flag)
    {
        kill(getpid(), 9);
    }
    ++flag;
}


void PCdisplay(void *public_convoy);
void STdisplay(void *s_taxi);
void Tdisplay(void *taxi);
void Mdisplay(void *minibus);
void PTdisplay(void *PT);
void Mwash(void *minibus, int minutes);


int g_public_transportation_count = 0;


typedef struct v_table
{
    void(*display)(void *this);
    void(*wash)(void *minibus, int num);
}v_table_t;


v_table_t g_public_transportation_v_ptr = {PTdisplay, NULL};
v_table_t g_public_convoy_v_ptr = {PCdisplay, NULL};
v_table_t g_minibus_v_ptr = {Mdisplay, Mwash};
v_table_t g_taxi_v_ptr = {Tdisplay, NULL};
v_table_t g_spacial_taxi_v_ptr = {STdisplay, NULL};


typedef struct public_transportation
{
    int m_license_plate;
    v_table_t *virtual_function;
}public_transportation_t;

typedef struct minibus
{
    public_transportation_t parrent;
    int m_num_of_seats;
}minibus_t;

typedef struct taxi
{
    public_transportation_t parrent;
}taxi_t;


typedef struct spacial_taxi
{
    taxi_t parrent;
}spacial_taxi_t;


typedef struct public_convoy
{
    public_transportation_t parrent;
    public_transportation_t *m_ptr1;
    public_transportation_t *m_ptr2;
    minibus_t m_m;
    taxi_t m_t;
}public_convoy_t;




void CtorPublicTransport(public_transportation_t *this)
{
    this->m_license_plate = ++g_public_transportation_count;
    this->virtual_function = &g_public_transportation_v_ptr;

    printf("PublicTransport::Ctor() %d\n", this->m_license_plate);
}

void DtorPublicTransport(public_transportation_t *this)
{
    --g_public_transportation_count;
    printf("PublicTransport::Dtor() %d\n", this->m_license_plate);
}

void CCtorPublicTransport(public_transportation_t *this, const public_transportation_t *other)
{
    this->m_license_plate = ++g_public_transportation_count;
    this->virtual_function = other->virtual_function;
    printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
}

void PTdisplay(void *PT)
{
    printf("PublicTransport::display(): %d\n", (((public_transportation_t *)PT)->m_license_plate));
}

void print_count()
{
    printf("g_public_transportation_count: %d\n", g_public_transportation_count);
}

int get_ID(public_transportation_t *this)
{
    return (this->m_license_plate);
}

void CtorMinibus(minibus_t *this)
{
    this->m_num_of_seats = 20;
    CtorPublicTransport(&(this->parrent));
    this->parrent.virtual_function = &g_minibus_v_ptr;
    printf("Minibus::Ctor()\n");
}

void CCtorMinibus(minibus_t *this, minibus_t *other)
{
    CCtorPublicTransport(&(this->parrent), &(other->parrent));
    this->parrent.virtual_function = &g_minibus_v_ptr;
    printf("Minibus::CCtor()\n");
}

void DtorMinibus(minibus_t *this)
{
    printf("Minibus::Dtor()\n");
    DtorPublicTransport(&(this->parrent));
}

void Mdisplay(void *minibus)
{
    printf("Minibus::display() ID: %d num seats: %d\n", get_ID(&((minibus_t *)minibus)->parrent), (((minibus_t *)minibus)->m_num_of_seats));
}

void Mwash(void *minibus, int minutes)
{
    printf("Minibus::wash(%d) ID: %d\n", minutes, get_ID(&((minibus_t *)minibus)->parrent));
}

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


void Tdisplay(void *taxi)
{
    printf("Taxi::display() ID: %d\n", get_ID(&((taxi_t *)taxi)->parrent));
}

void CtorSpacialTaxi(spacial_taxi_t *this)
{
    CtorTaxi(&(this->parrent));
    (this->parrent).parrent.virtual_function = &g_spacial_taxi_v_ptr;
    printf("Spacial Taxi::Ctor()\n");
}

void CCtorSpacialTaxi(spacial_taxi_t *this, spacial_taxi_t *other)
{
    CCtorTaxi(&(this->parrent), &(other->parrent));
    (this->parrent).parrent.virtual_function = &g_spacial_taxi_v_ptr;
    printf("Spacial Taxi::CCtor()\n");
}
    
    
void DtorSpacialTaxi(spacial_taxi_t *this)
{
    printf("Spacial Taxi::Dtor()\n");
    DtorTaxi(&(this->parrent));
}


void STdisplay(void *s_taxi)
{
    printf("Spacial Taxi::display() ID: %d\n", get_ID(&((spacial_taxi_t *)s_taxi)->parrent.parrent));
}

/*********************************************************/
int max_func(const int t1, const int t2)
{
    return ((t1 > t2) ? t1 : t2);
} 

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

    void DtorPublicConvoy(public_convoy_t *this)
    {
        DtorMinibus((minibus_t *)(this->m_ptr1));
        DtorTaxi((taxi_t *)(this->m_ptr2));
        DtorPublicTransport(&(this->parrent));
    }

    void PCdisplay(void *public_convoy)
    {
        public_convoy_t *pc = (public_convoy_t *)public_convoy;
        pc->m_ptr1->virtual_function->display(pc->m_ptr1);
        pc->m_ptr2->virtual_function->display(pc->m_ptr2);
        pc->m_m.parrent.virtual_function->display(&(pc->m_m));
        pc->m_t.parrent.virtual_function->display(&(pc->m_t));
    }



void PTprint_info(public_transportation_t *a)
{
    a->virtual_function->display(a);
}


void print_info()
{
    printf("s_count: %d\n", g_public_transportation_count);
}

void Mprint_info(minibus_t *m)
{
    m->parrent.virtual_function->wash(m, 3);
}

public_transportation_t PTRprint_info(int i)/* Public Transportation Return */
{
    minibus_t ret;
    ++i;
    CtorMinibus(&ret);
    printf("print_info(int i)\n");
    ret.parrent.virtual_function->display(&ret);
    return *((public_transportation_t*)&ret);
}

void taxi_display(taxi_t *s)
{
    s->parrent.virtual_function->display(s);
}

int main(int argc, char **argv, char **envp)
{
    minibus_t m;
    int i;
    public_transportation_t tmp;
    public_transportation_t tmp2;
    public_transportation_t *array[3];

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
    
    CtorMinibus((minibus_t *)&array[0]);
    CtorTaxi((taxi_t *)&array[1]);
    CtorMinibus((minibus_t *)&array[2]);


    DtorMinibus((minibus_t *)&array[0]);
    DtorTaxi((taxi_t *)&array[1]);
    DtorMinibus((minibus_t *)&array[2]);
/*
    for (i = 0; i < 3; ++i) {
        array[i]->virtual_function->display(&array[i]);
    }


    for ( i = 0; i < 3; ++i) {
        free(array[i]);
    }
*/
/*     PublicTransport arr2[] = { Minibus(), Taxi(), PublicTransport() };/////////////
    //PublicTransport arr2[3];

    for (int i = 0; i < 3; ++i) {
        arr2[i].display();
    }
    print_info(arr2[0]);

    PublicTransport::print_count();
    Minibus m2;
    m2.print_count();

    Minibus arr3[4];
    Taxi *arr4 = new Taxi[4];
    delete[] arr4;

    std::cout << max_func(1, 2) << "\n";
    std::cout << max_func<int>(1, 2.0f)<< "\n";
    SpecialTaxi st;
    taxi_display(st);

    PublicConvoy *ts1 = new PublicConvoy();
    PublicConvoy *ts2 = new PublicConvoy(*ts1);
    ts1->display();
    ts2->display();
    delete ts1;
    ts2->display(); // this crashes. fix the bug!
    delete ts2; */

    return 0;
}