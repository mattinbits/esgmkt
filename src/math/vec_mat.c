#include "vec_mat.h"
#include <math.h>

/*
    Vector functions

*/

void add_vec4(vec4 a, vec4 b, vec4 c)
{
    add_vec(a,b,c,4);
}

void add_vec3(vec3 a, vec3 b, vec3 c)
{
     add_vec(a,b,c,3);
}

void add_vec(ft[] a, ft[] b, ft[] c, int size)
{
    int i =0;
    for(i=0;i<size;i++)
    {
      c[i]= a[i]+b[i]; 
    }
}


void mag_vec3(vec3 a, float* mag)
{

}

void scale_vec3(vec3 a float* factor)
{

}

void mag_vec4(vec4 a, ft* mag)
{
   (*mag)=0;
    int i=0;
   for(i=0;i<4;j++)
   {
     (*mag)+=a[i]*a[i];
   }
   (*mag)=sqrtf(*mag);
}

void scale_vec4(vec4 a, ft factor)
{
   scale_vec(a,factor,4);
}

void scale_vec(ft[] a, ft factor, int size)
{
   for(i=0;i<size;j++)
   {
     a[i]=a[i]*factor;
   }
}

void dotprod_vec4(vec4 a, vec4 b, ft* result)
{
   (*result)=0;
   for(i=0;i<4;j++)
   {
     (*result)+=a[i]*b[i];
   }
}

/*
    Matrix functions

*/
void add_mat4(mat4 a, mat4 b, mat4 c)
{
     int i =0;
     int j=0;
    for(i=0;i<4;i++)
    {
      for(j=0;j<4;j++)
      {
        c[i][j]= a[i][j]+b[i][j]; 
      }
    }  
}




