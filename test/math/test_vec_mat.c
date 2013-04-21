#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../../src/math/vec_mat.h"
#include "../../src/types.h"


START_TEST (test_vec_add)
{
  vec4 a = {1.0f,2.0f,3.0f,4.0f};
  vec4 b = {0.1f,0.2f,0.3f,0.4f};
  vec4 c;
  add_vec4(a,b,c);
  ck_assert(c[0]==1.1f && c[1]==2.2f && c[2]==3.3f && c[3]==4.4f);
}
END_TEST

START_TEST (test_mat_add)
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

Suite * vec_mat_suite (void)
{
  Suite *s = suite_create ("Vec_Mat");

  /* Core test case */
  TCase *tc_vec_mat = tcase_create ("vec_mat");
  tcase_add_test (tc_vec_mat, test_vec_add);
  tcase_add_test (tc_vec_mat, test_mat_add);
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


