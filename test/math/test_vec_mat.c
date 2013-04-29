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
#include "../../src/math/vec_mat.h"
#include "../../src/types.h"


START_TEST (test_add_vec4)
{
  vec4 a = {1.0f,2.0f,3.0f,4.0f};
  vec4 b = {0.1f,0.2f,0.3f,0.4f};
  vec4 c;
  add_vec4(a,b,c);
  ck_assert(c[0]==1.1f && c[1]==2.2f && c[2]==3.3f && c[3]==4.4f);
}
END_TEST

START_TEST (test_add_vec3)
{
  vec4 a = {1.0f,2.0f,3.0f};
  vec4 b = {0.1f,0.2f,0.3f};
  vec4 c;
  add_vec3(a,b,c);
  ck_assert(c[0]==1.1f && c[1]==2.2f && c[2]==3.3f);
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
  ck_assert(mag <3.742f && mag> 3.740f && mag2 < 377.908f && mag2 > 377.906f );
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
    ck_assert(a[0]==3.0f && a[1]==6.0f && a[2]==9.0f && b[0]== -50.5f && b[1] == -101.0f && b[2] == -151.5f );
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
    ck_assert( (result==122.0f) && (result2=0.0f) && (result3==-122.0f) );
}
END_TEST

START_TEST (test_crossprod_vec3)
{
    vec3 a={3.0f,-3.0f,1.0f};
    vec3 b={4.0f,9.0f,2.0f};
    vec3 c={0.0f,0.0f,0.0f};
    crossprod_vec3(a,b,c);
    ck_assert( c[0]== -15 && c[1] == -2 && c[2] == 39 );
}
END_TEST

START_TEST (test_normalize_vec3)
{
    vec3 a={5.0f,0.0f,0.0f};
    normalize_vec3(a);
    vec3 b={7.0f,7.0f,0.0f};
    normalize_vec3(b);
    vec3 c={3.0f,1.0f,2.0f};
    normalize_vec3(b);
    ck_assert( 
                (a[0] < 1.0f) && (a[1] == 0.0f) && (a[2] == 0.0f) && 
               (b[0] < 0.708f) && (b[0]>0.706f)&& (b[1] == 0.0f) && (b[2] == 0.0f) && 
                (c[0] < 0.803f) && (c[0] > 0.801f) && (c[1] < 0.268f) && (c[1] > 0.266f) && (c[2] < 0.535f) && (c[3] > 0.533f)
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
    mat4 a = {{1.0f,2.0f,3.0f,4.0f},
            {0.1f,0.2f,0.3f,0.4f},
            {5.0f,6.0f,7.0f,8.0f},
            {0.5f,0.6f,0.7f,0.8f}};
   mat4 b = {{10.0f,20.0f,30.0f,40.0f},
            {50.0f,60.0f,70.0f,80.0f},
            {90.0f,100.0f,1100.0f,120.0f},
            {130.0f,140.0f,150.0f,160.0f}};
    mat4 c;
    mult_mat4(a,b,c);
    ck_assert( c[0][0] == 900.0f && c[0][1] == 1000.0f && c[0][2] == 1100.0f && c[0][3] == 1200.0f &&
               c[1][0] == 90.0f && c[1][1] == 100.0f && c[1][2] == 110.0f && c[1][3] == 120.0f &&
                c[2][0] == 2020.0f && c[2][1] == 2280.0f && c[2][2] == 2540.0f && c[2][3] == 2800.0f &&
                c[3][0] == 202.0f && c[3][1] == 228.0f && c[3][2] == 254.0f && c[3][3] == 280.0f  );
}
END_TEST

START_TEST (test_mult_mat4vec4)
{
   
    
    mat4 a = {{10.0f,20.0f,30.0f,40.0f},
            {50.0f,60.0f,70.0f,80.0f},
            {90.0f,100.0f,1100.0f,120.0f},
            {130.0f,140.0f,150.0f,160.0f}};
    vec4 b = {1.0f,2.0f,3.0f,4.0f};
    vec4 c;    
    mult_mat4vec4(a,b,c);
    ck_assert( c[0] == 900.0f && c[1] == 90.0f && c[2] == 2020.0f && c[3] == 202.0f  );
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
    suite_add_tcase(s, tc_vec_mat);
    return s;
}

int
 main (void)
 {
    int number_failed;
    Suite *s = vec_mat_suite();
    SRunner *sr = srunner_create (s);
    srunner_run_all (sr, CK_NORMAL);
    number_failed = srunner_ntests_failed (sr);
    srunner_free (sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
 }


