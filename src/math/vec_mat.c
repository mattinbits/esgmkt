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

inline void add_vec(ft[] a, ft[] b, ft[] c, int size)
{
    int i =0;
    for(i=0;i<size;i++)
    {
      c[i]= a[i]+b[i]; 
    }
}


void mag_vec3(vec3 a, float* mag)
{
  mag_vec(a,mag,3);
}

void scale_vec3(vec3 a float factor)
{
   scale_vec(a,factor,3);
}

void mag_vec4(vec4 a, ft* mag)
{
   mag_vec(a,mag,4);
}

inline void mag_vec(ft[] a, ft* mag, size)
{
   (*mag)=0;
    int i=0;
   for(i=0;i<size;j++)
   {
     (*mag)+=a[i]*a[i];
   }
   (*mag)=sqrtf(*mag);	
}

void scale_vec4(vec4 a, ft factor)
{
   scale_vec(a,factor,4);
}

inline void scale_vec(ft[] a, ft factor, int size)
{
   for(i=0;i<size;j++)
   {
     a[i]=a[i]*factor;
   }
}

void dotprod_vec4(vec4 a, vec4 b, ft* result)
{
   dotprod_vec(a,b,result,4);
}

void dotprod_vec3(vec3 a, vec4 b, ft* result)
{
   dotprod_vec(a,b,result,3);
}

inline void dotprod_vec(ft[] a, vec4 b, ft* result, int size)
{
   (*result)=0;
   for(i=0;i<size;j++)
   {
     (*result)+=a[i]*b[i];
   }
}

void crossprod_vec3(vec3 a, vec3 b, vec3 c)
{
	
  c[0] =   ( (a[1] * b[2]) - (a[2] * b[1]) );
  c[1] = - ( (a[0] * b[2]) - (a[2] * b[0]) );
  c[2] =   ( (a[0] * b[1]) - (a[1] * b[0]) );
}

void normalize_vec3(vec3 a)
{
  ft magnitude;
  ft power = 2.0f;
  magnitude = sqrt( pow(v1[0], power) +
               pow(v1[1], power) +
               pow(v1[2], power)
             );
  a[0]=a[0]/magnitude;
  a[1]=a[1]/magnitude;
  a[2]=a[2]/magnitude;
}

void copy_vec3(vec3 a, vec3 b)
{
  copy_vec(a,b,3);
}

void copy_vec4(vec4 a, vec4 b)
{
	  copy_vec(a,b,4);
}

inline void copy_vec(ft[] a, ft[] b, int size)
{
   int i=0;
   for(i=0;i<size;i++)
   {
	b[i]=a[i];
   }
}

/*
    Matrix functions

*/
void add_mat4(mat4 a, mat4 b, mat4 c)
{
     int i=0;
     int j=0;
    for(i=0;i<4;i++)
    {
      for(j=0;j<4;j++)
      {
        c[i][j]= a[i][j]+b[i][j]; 
      }
    }  
}

void mult_mat4(mat4 a, mat4 b, mat4 c)
{
    mult_mat(a,b,c,4);
}

void mult_mat(ft[][] a, ft[][] b, ft[][] c, int size)
{
    int i=0;
    int j=0;
    int k=0;
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            c[i][j]=0.0f;
            for(k=0;k<size;k++)
            {
                c[i][j]+=a[i][k]*b[k][j];
            }
        }    
    }
}

void mult_vec4mat4(vec4 a, mat4 b, vec4 c)
{
    mult_vecmat(a,b,c,4);
}

void mult_vecmat(ft[] a, ft[][] b, ft[] c, int size)
{
    int i=0;
    int j=0;
    int k=0;
    for(i=0;i<size;i++)
    {
        c[i]=0.0f;       
        for(j=0;j<size;j++)
        {
            c[i]+=a[j]*b[i][j];
        }    
    }
}


void copy_mat4(mat4 a, mat4 b)
{
    copy_mat(a,b,4);
}

inline void copy_mat(mat4 a, mat4 b, int size)
{
    int i=0;
    int j=0;
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            b[i][j]=a[i][j];
        }
}


