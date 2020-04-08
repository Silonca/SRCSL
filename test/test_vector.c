//#include "../source/auxilliary/vector.h"
#include "vector.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct VectorItem
{
    int a;
    int b;
} VectorItem;

typedef VectorItem Item;

int test_vector(void)
{
    int times = 0,cnt=0;
    Item *t;
    Vector vector;
    vector_init( &vector);    

    srand( (unsigned int)time(NULL));

    while(1)
    {
        char c;
		int a;
        scanf("mode:%c", &c);
        switch(c)
        {
            case 'i':
            {
                if( scanf("times:%d", &times) == 0)
                    break;
                for( a= 0; a < times; ++a)
                {
                    t = (Item*)malloc(sizeof(Item));
                    t->a = cnt;
                    t->b = times;
                    vector_push_back(&vector,t);
                }
                ++cnt;                
            }break;
            case 'p':
            {
                for(a = 0; (unsigned int)a < vector_size( &vector); ++a)
                {
                    printf("a=%5d,b=%5d\n",vector.item_space[a]->a,vector.item_space[a]->b);
                }
            }
        }

    }

    system("pause");
    return 0;
    
}