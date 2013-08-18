/*
 * test_vec_mat.c
 * Unit tests using Check framework for vec_mat.c
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
#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include <math.h>
#include "../../src/math/vec_mat.h"
#include "../../src/types.h"
#define EPSILON (0.000001f)

static boolean eq(ft a, ft b)
{
    return fabs(a - b) < EPSILON;
}

START_TEST (test_add_vec4)
{
  vec4 a = {1.0f,2.0f,3.0f,4.0f};
  vec4 b = {0.1f,0.2f,0.3f,0.4f};
  vec4 c;
  add_vec4(a,b,c);
  ck_assert(eq(c[0],1.1f) && eq(c[1],2.2f) && eq(c[2],3.3f) && eq(c[3],4.4f));
}
END_TEST

START_TEST (test_add_vec3)
{
  vec4 a = {1.0f,2.0f,3.0f};
  vec4 b = {0.1f,0.2f,0.3f};
  vec4 c;
  add_vec3(a,b,c);
  ck_assert(eq(c[0],1.1f) && eq(c[1],2.2f) && eq(c[2],3.3f));
}
END_TEST



START_TEST (test_mag_vec3)
{
  vec3 a = {1.0f,2.0f,3.0f};
  ft mag = 0.0f;
  mag_vec3(a,(&mag));

  vec3 b = {101.0f,202.0f,-303.0f};
  ft mag2 = 0.0f;
  mag_vec3(b,(&mag2));
    //range test since floats defy exact comparison
  ck_assert(eq(mag,3.741657387f)  && eq(mag2,377.907396064f));
}
END_TEST

START_TEST (test_scale_vec3)
{
    vec3 a={1.0f,2.0f,3.0f};
    ft factor = 3.0f;
    scale_vec3(a, factor);
    vec3 b = {101.0f,202.0f,303.0f};
    ft factor2=-0.5f;
    scale_vec3(b,factor2);
    ck_assert(eq(a[0],3.0f) && eq(a[1],6.0f) && eq(a[2],9.0f) && eq(b[0],-50.5f) && eq(b[1],-101.0f) && eq(b[2], -151.5f) );
}
END_TEST

START_TEST (test_dotprod_vec3)
{
    vec3 a={4.0f,8.0f,10.0f};
    vec3 b={9.0f,2.0f,7.0f};
    ft result = 0.0f;
    dotprod_vec3(a,b,&result);
    vec3 c={1.0f,1.0f,0.0f};
    vec3 d={0.0f,0.0f,1.0f};
    ft result2 = 1.0f;
    dotprod_vec3(c,d,&result2);
    vec3 e={4.0f,8.0f,10.0f};
    vec3 f={-9.0f,2.0f,7.0f};
    ft result3 = 0.0f;
    dotprod_vec3(e,f,&result3);
    ck_assert( eq(result,122.0f) && eq(result2,0.0f) && eq(result3,-122.0f) );
}
END_TEST

START_TEST (test_crossprod_vec3)
{
    vec3 a={3.0f,-3.0f,1.0f};
    vec3 b={4.0f,9.0f,2.0f};
    vec3 c={0.0f,0.0f,0.0f};
    crossprod_vec3(a,b,c);
    ck_assert( eq(c[0], -15.0f) && eq(c[1], -2.0f) && eq(c[2], 39.0f) );
}
END_TEST

START_TEST (test_normalize_vec3)
{
    vec3 a={5.0f,0.0f,0.0f};
    normalize_vec3(a);
    vec3 b={7.0f,7.0f,0.0f};
    normalize_vec3(b);
    vec3 c={3.0f,1.0f,2.0f};
    normalize_vec3(c);
    ck_assert( 
                eq(a[0], 1.0f) && eq(a[1], 0.0f) && eq(a[2], 0.0f) && 
               eq(b[0] , 0.707106781f) && eq(b[1] ,0.707106781f) && eq(b[2] , 0.0f) && 
                eq(c[0] , 0.801783726f) && eq(c[1], 0.267261242f) && eq(c[2] ,0.534522484f)
    );
}
END_TEST

START_TEST (test_copy_vec3)
{
    vec3 a={5.0f,4.0f,3.0f};
    vec3 b={0.0f,0.0f,0.0f};
    copy_vec3(a,b);
    ck_assert( b[0] == 5.0f && b[1] == 4.0f && b[2] == 3.0f  );
}
END_TEST


START_TEST (test_copy_vec4)
{
    vec4 a={5.0f,4.0f,3.0f,2.0f};
    vec4 b={0.0f,0.0f,0.0f,0.0f};
    copy_vec4(a,b);
    ck_assert( b[0] == 5.0f && b[1] == 4.0f && b[2] == 3.0f && b[3] == 2.0f  );
}
END_TEST

START_TEST (test_getidentity_mat4)
{
    mat4 b = {{0.0f,0.0f,0.0f,0.0f},
            {0.0f,0.0f,0.0f,0.0f},
            {0.0f,0.0f,0.0f,0.0f},
            {0.0f,0.0f,0.0f,0.0f}};
    getidentity_mat4(b);
     ck_assert( b[0][0] == 1.0f && b[0][1] == 0.0f && b[0][2] == 0.0f && b[0][3] == 0.0f &&
               b[1][0] == 0.0f && b[1][1] == 1.0f && b[1][2] == 0.0f && b[1][3] == 0.0f &&
                b[2][0] == 0.0f && b[2][1] == 0.0f && b[2][2] == 1.0f && b[2][3] == 0.0f &&
                b[3][0] == 0.0f && b[3][1] == 0.0f && b[3][2] == 0.0f && b[3][3] == 0.0f  );
}END_TEST


START_TEST (test_create_mat4)
{
    vec4 col0={1.0f,2.0f,3.0f,4.0f};
    vec4 col1={5.0f,6.0f,7.0f,8.0f};
    vec4 col2={9.0f,10.0f,11.0f,12.0f};
    vec4 col3={13.0f,14.0f,15.0f,16.0f};
    mat4 b = {{0.0f,0.0f,0.0f,0.0f},
            {0.0f,0.0f,0.0f,0.0f},
            {0.0f,0.0f,0.0f,0.0f},
            {0.0f,0.0f,0.0f,0.0f}};
    create_mat4(b, col0,  col1,  col2,  col3);
     ck_assert( b[0][0] == 1.0f && b[0][1] == 2.0f && b[0][2] == 3.0f && b[0][3] == 4.0f &&
               b[1][0] == 5.0f && b[1][1] == 6.0f && b[1][2] == 7.0f && b[1][3] == 8.0f &&
                b[2][0] == 9.0f && b[2][1] == 10.0f && b[2][2] == 11.0f && b[2][3] == 12.0f &&
                b[3][0] == 13.0f && b[3][1] == 14.0f && b[3][2] == 15.0f && b[3][3] == 16.0f  );
}END_TEST

START_TEST (test_add_mat4)
{
  mat4 a = {{1.0f,2.0f,3.0f,4.0f},
            {5.0f,6.0f,7.0f,8.0f},
            {9.0f,10.0f,11.0f,12.0f},
            {13.0f,14.0f,15.0f,16.0f}};
   mat4 b = {{0.1f,0.2f,0.3f,0.4f},
            {0.5f,0.6f,0.7f,0.8f},
            {0.9f,1.0f,1.1f,1.2f},
            {1.3f,1.4f,1.5f,1.6f}};
  mat4 answer = {{1.1f,2.2f,3.3f,4.4f},
                 {5.5f,6.6f,7.7f,8.8f},
                 {9.9f,11.0f,12.1f,13.2f},
                 {14.3f,15.4f,16.5f,17.6f}};
  mat4 c;
  add_mat4(a,b,c);
  int i=0;
  int j=0;
  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
        printf("%f \n",c[i][j]);
    }
  }
  boolean valid_mat_add= TRUE;
  for(i=0;i<4;i++)
  {
    for(j=0;j<4;j++)
    {
        
        valid_mat_add = answer[i][j]==c[i][j];
    }
  }
  ck_assert(valid_mat_add);
  
}
END_TEST



START_TEST (test_copy_mat4)
{
    mat4 a = {{1.0f,2.0f,3.0f,4.0f},
            {5.0f,6.0f,7.0f,8.0f},
            {9.0f,10.0f,11.0f,12.0f},
            {13.0f,14.0f,15.0f,16.0f}};
   mat4 b = {{0.0f,0.0f,0.0f,0.0f},
            {0.0f,0.0f,0.0f,0.0f},
            {0.0f,0.0f,0.0f,0.0f},
            {0.0f,0.0f,0.0f,0.0f}};
    copy_mat4(a,b);
    ck_assert( b[0][0] == 1.0f && b[0][1] == 2.0f && b[0][2] == 3.0f && b[0][3] == 4.0f &&
               b[1][0] == 5.0f && b[1][1] == 6.0f && b[1][2] == 7.0f && b[1][3] == 8.0f &&
                b[2][0] == 9.0f && b[2][1] == 10.0f && b[2][2] == 11.0f && b[2][3] == 12.0f &&
                b[3][0] == 13.0f && b[3][1] == 14.0f && b[3][2] == 15.0f && b[3][3] == 16.0f  );
}
END_TEST

START_TEST (test_mult_mat4)
{
/*
    
A    
    c0	c1	c2	c3
r0	1.0000000	2.5000000	3.0000000	6.0000000
r1	-5.0000000	7.3400000	-0.4000000	12.0000000
r2	87.0000000	65.0000000	3.2300000	100.0000000
r3	2.0000000	3.0000000	4.0000000	5.0000000
				
*B				
	c0	c1	c2	c3
r0	4.0000000	23.0000000	0.3000000	21.0000000
r1	9.0000000	4.0000000	5.0000000	0.3200000
r2	1.0000000	2.0000000	3.0000000	4.0000000
r3	5.0000000	6.0000000	7.0000000	8.0000000


=C				
	c0	c1	c2	c3
r0	59.5000000	75.0000000	63.8000000	81.8000000
r1	105.6600000	-14.4400000	118.0000000	-8.2512000
r2	1436.2300000	2867.4600000	1060.7900000	2660.7200000
r3	64.0000000	96.0000000	62.6000000	98.9600000
   
*/
    
    vec4 ac1={1.0,-5.0f,87.0f,2.0f};
    vec4 ac2={2.5f,7.34f,65.0f,3.0f};
    vec4 ac3={3.0f,-0.4f,3.23f,4.0f};
    vec4 ac4={6.0f,12.0f,100.0f,5.0f};
    
    mat4 a = {{0.0f,0.0f,0.0f,0.0f},
            {0.0f,0.0f,0.0f,0.0f},
            {0.0f,0.0f,0.0f,0.0f},
            {0.0f,0.0f,0.0f,0.0f}};
   create_mat4(a,ac1,ac2,ac3,ac4);
   vec4 bc1={4.0,9.0f,1.0f,5.0f};
    vec4 bc2={23.0f,4.0f,2.0f,6.0f};
    vec4 bc3={0.3f,5.0f,3.0f,7.0f};
    vec4 bc4={21.0f,0.32f,4.0f,8.0f};
          
   mat4 b = {{0.0f,0.0f,0.0f,0.0f},
            {0.0f,0.0f,0.0f,0.0f},
            {0.0f,0.0f,0.0f,0.0f},
            {0.0f,0.0f,0.0f,0.0f}};
    create_mat4(b,bc1,bc2,bc3,bc4);
    mat4 c;
    mult_mat4(a,b,c);
    ck_assert( 
                eq(c[0][0],59.5f) && eq(c[1][0],75.0f) && eq(c[2][0],63.8f) && eq(c[3][0], 81.8f) &&
               eq(c[0][1], 105.66f) && eq(c[1][1] ,-14.44f) && eq(c[2][1],118.0f) && eq(c[3][1], 8.2512f) &&
                eq(c[0][2], 1436.23f) && eq(c[1][2], 2867.46f) && eq(c[2][2], 1060.79f) && eq(c[3][2], 2660.72f) &&
                eq(c[0][3], 64.0f) && eq(c[1][3], 96.0f) && eq(c[2][3] , 62.6f) && eq(c[3][3], 98.96f)
            );
}
END_TEST


		

START_TEST (test_mult_mat4vec4)
{
   
/*
    	c0	c1	c2	c3
r0	1.0000000	2.5000000	3.0000000	6.0000000
r1	-5.0000000	7.3400000	-0.4000000	12.0000000
r2	87.0000000	65.0000000	3.2300000	100.0000000
r3	2.0000000	3.0000000	4.0000000	5.0000000
				
				
	c0			
	1			
	2			
	3			
	4			
	
	
	c0			
	39.00000
    56.48000
    626.69000
    40.00000

*/
    
    vec4 ac1={1.0,-5.0f,87.0f,2.0f};
    vec4 ac2={2.5f,7.34f,65.0f,3.0f};
    vec4 ac3={3.0f,-0.4f,3.23f,4.0f};
    vec4 ac4={6.0f,12.0f,100.0f,5.0f};
    
    mat4 a = {{0.0f,0.0f,0.0f,0.0f},
            {0.0f,0.0f,0.0f,0.0f},
            {0.0f,0.0f,0.0f,0.0f},
            {0.0f,0.0f,0.0f,0.0f}};
   create_mat4(a,ac1,ac2,ac3,ac4);
    vec4 b = {1.0f,2.0f,3.0f,4.0f};
    vec4 c = {0.0f,0.0f,0.0f,0.0f};    
    mult_mat4vec4(a,b,c);
    ck_assert( eq(c[0], 39.0f) && eq(c[1], 56.48f) && eq(c[2], 626.69f) && eq(c[3], 40.0f)  );
}
END_TEST



Suite * vec_mat_suite (void)
{
  Suite *s = suite_create ("Vec_Mat");

  /* Core test case */
    TCase *tc_vec_mat = tcase_create ("vec_mat");
    tcase_add_test (tc_vec_mat, test_add_vec4);
    tcase_add_test (tc_vec_mat, test_add_vec3);
    tcase_add_test (tc_vec_mat, test_mag_vec3);
    tcase_add_test (tc_vec_mat, test_scale_vec3);
    tcase_add_test (tc_vec_mat, test_dotprod_vec3);
    tcase_add_test (tc_vec_mat, test_crossprod_vec3);
    tcase_add_test (tc_vec_mat, test_normalize_vec3);
    tcase_add_test (tc_vec_mat, test_copy_vec3);
    tcase_add_test (tc_vec_mat, test_copy_vec4);
    tcase_add_test (tc_vec_mat, test_add_mat4);
    tcase_add_test (tc_vec_mat, test_copy_mat4);
    tcase_add_test (tc_vec_mat, test_mult_mat4);
    tcase_add_test (tc_vec_mat, test_mult_mat4vec4);
    tcase_add_test (tc_vec_mat,test_getidentity_mat4);
    tcase_add_test (tc_vec_mat,test_create_mat4);
    suite_add_tcase(s, tc_vec_mat);
    return s;
}

int main (void)
 {
    int number_failed;
    Suite *s = vec_mat_suite();
    SRunner *sr = srunner_create (s);
    srunner_run_all (sr, CK_NORMAL);
    number_failed = srunner_ntests_failed (sr);
    srunner_free (sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
 }


