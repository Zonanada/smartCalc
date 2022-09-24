#include <check.h>

#include "../s21_smart_calc.h"

START_TEST(test_ponat_1) {
    char str[] = "2+2.2*54/3+5";
    char* result = ponat(str);
    char *right = "46.6";

    int code = strcmp(result, right);
    ck_assert_int_eq(code, 0);
    free(result);
} END_TEST

START_TEST(test_ponat_2) {
    char str[] = "sin(cos(2^3))";
    char *result = ponat(str);
    char *right = "-0.14498719803";

    int code = strcmp(result, right);
    ck_assert_int_eq(code, 0);
    free(result);
}

START_TEST(test_ponat_incorrect) {
    char str[] = "sin(cos(2^3)";
    char *result = ponat(str);
    char *right = "Incorrect input";

    int code = strcmp(result, right);
    ck_assert_int_eq(code, 0);
    free(result);
}

START_TEST(test_changeXOnDouble_1) {
    char str[] = "sin(cos(X - 2))";
    char* result = changeXOnDouble(str, 27.345);
    char *right = "sin(cos(27.34500000000 - 2))";
    int code = strcmp(result, right);
    ck_assert_int_eq(code, 0);
    free(result);
}

START_TEST(test_changeXOnDouble_2) {
    char str[] = "tan(1 - X)";
    char* result = changeXOnDouble(str, 8.888);
    char *right = "tan(1 - 8.88800000000)";
    int code = strcmp(result, right);
    ck_assert_int_eq(code, 0);
    free(result);
}

END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test_ponat_1);
  tcase_add_test(tc1_1, test_ponat_2);
  tcase_add_test(tc1_1, test_changeXOnDouble_1);
  tcase_add_test(tc1_1, test_changeXOnDouble_2);
  tcase_add_test(tc1_1, test_ponat_incorrect);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
