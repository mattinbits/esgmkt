/*
 * vec_mat.c
 * Implementation for library of vector and matrix maths functions
 *
 * This file is part of esgmkt (OpenGL ES 2.0 Game Kit), 
 * Copyright Matthew Livesey 2013 (matt.computes@gmail.com)
 * 
 * This work is distributed under the BSD licence, a copy of which is
 * distributed with this work.
 * 
 * esgmkt is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#include "vec_mat.h"
#include <math.h>

/*
    Vector functions

*/

    /* Function prototypes for functions not declared in header */

void add_vec(ft a[], ft b[], ft c[], int size);
void mag_vec(ft a[], ft* mag,int size);
void scale_vec(ft a[], ft factor, int size);
void dotprod_vec(ft a [], vec4 b, ft* result, int size);
void crossprod_vec3(vec3 a, vec3 b, vec3 c);
void copy_vec(ft a [], ft b[], int size);

    /*Function implementations*/

void add_vec4(vec4 a, vec4 b, vec4 c)
{
    add_vec(a,b,c,4);
}

void add_vec3(vec3 a, vec3 b, vec3 c)
{
     add_vec(a,b,c,3);
}

inline void add_vec(ft a[], ft b[], ft c[], int size)
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

void scale_vec3(vec3 a, ft factor)
{
   scale_vec(a,factor,3);
}

void mag_vec4(vec4 a, ft* mag)
{
   mag_vec(a,mag,4);
}

inline void mag_vec(ft a[], ft* mag, int size)
{
   (*mag)=0;
    int i=0;
   for(i=0;i<size;i++)
   {
     (*mag)+=a[i]*a[i];
   }
   (*mag)=sqrtf(*mag);	
}

void scale_vec4(vec4 a, ft factor)
{
   scale_vec(a,factor,4);
}

inline void scale_vec(ft a[], ft factor, int size)
{
    int i=0;   
    for(i=0;i<size;i++)
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

inline void dotprod_vec(ft a [], vec4 b, ft* result, int size)
{
   (*result)=0;
    int i = 0;
   for(i=0;i<size;i++)
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
  magnitude = sqrt( pow(a[0], power) +
               pow(a[1], power) +
               pow(a[2], power)
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

inline void copy_vec(ft a [], ft b[], int size)
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




    /* Function prototypes for functions not declared in header */
void mult_mat(ft *a, ft *b, ft *c, int size);
void mult_matvec(ft *a, ft b[], ft c[], int size);
void copy_mat(ft* a, ft* b, int size);

    /*Function implementations*/
    
void getidentity_mat4(/*return*/mat4 a)
{
     mat4 b = {{1.0f,0.0f,0.0f,0.0f},
            {0.0f,1.0f,0.0f,0.0f},
            {0.0f,0.0f,1.0f,0.0f},
            {0.0f,0.0f,0.0f,1.0f}};
     memcpy(b,a,16*sizeof(ft));       
}
    
void create_mat4(mat4 a,vec4 col0, vec4 col1, vec4 col2, vec4 col3)
{
    memcpy(a[0],col0,4*sizeof(ft));
    memcpy(a[1],col1,4*sizeof(ft));
    memcpy(a[2],col2,4*sizeof(ft));
    memcpy(a[3],col3,4*sizeof(ft));
}

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


inline void mult_mat(ft *a, ft *b, ft *c, int size)
{
    int i=0;
    int j=0;
    int k=0;
    /*i is row index*/
    for(i=0;i<size;i++)
    {
        /*j is column index*/
        for(j=0;j<size;j++)
        {
  
            *(c+i+size*j)=0.0f;
            for(k=0;k<size;k++)
            {
                /*Remember, it's column major!
                    So in 'a' we work along the row
                    and in 'b' we work along the column
                 */
                *(c+i+size*j)+=*(a+k+j*size) * *(b+k*size+i);
            }
        }    
    }
}

void mult_mat4vec4(mat4 a, vec4 b, vec4 c)
{
    mult_matvec(a,b,c,4);
}

void mult_matvec(ft *a, ft b[], ft c[], int size)
{
    int i=0;
    int j=0;
    
    for(i=0;i<size;i++)
    {
        c[i]=0.0f;       
        for(j=0;j<size;j++)
        {
            c[i]  +=  *(a+i*size+j) * b[j];
        }    
    }
}


void copy_mat4(mat4 a, mat4 b)
{
    copy_mat(a,b,4);
}

inline void copy_mat(ft *a, ft *b, int size)
{
    int i=0;
    int j=0;
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
        {
            *(b+i*size+j)=*(a+i*size+j);
        }
    }
}


