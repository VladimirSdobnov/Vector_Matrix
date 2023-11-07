#include "../TVector/TVector.h"
#include "../qtest/gtest.h"

TEST(TVector, can_create_vector_with_positive_length) {
  ASSERT_NO_THROW(TVector<int> v(5));
}

TEST(TVector, cant_create_too_large_vector) {
  ASSERT_ANY_THROW(TVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TVector, can_get_size) {
  TVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TVector, can_set_and_get_element) {
  TVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TVector, throws_when_create_vector_with_negative_length) {
	ASSERT_ANY_THROW(TVector<int> v(-5));
}

TEST(TVector, can_create_copied_vector) {
	std::string mass_str[5] = {"asd", "asda", "qwert", "rtyui", "qwertyu"};
	TVector<std::string> v(mass_str, 5);
	ASSERT_NO_THROW(TVector<std::string> v2(v));
}

TEST(TVector, copied_vector_is_equal_to_source_one) {
	std::string mass_str[5] = { "asd", "asda", "qwert", "rtyui", "qwertyu" };
	TVector<std::string> v(mass_str, 5);
	TVector<std::string> v2(v);
	EXPECT_EQ(v, v2);
}

TEST(TVector, copied_vector_has_its_own_memory) {
	std::string mass_str[5] = { "asd", "asda", "qwert", "rtyui", "qwertyu" };
	TVector<std::string> v(mass_str, 5);
	TVector<std::string> v2(v);
	EXPECT_NE(&v, &v2);
}

TEST(TVector, throws_when_set_element_with_negative_index) {
	float mass_str[5] = { 4.5, 6.8 , 4.9, 45.8 };
	TVector<float> v(mass_str, 6);
	ASSERT_ANY_THROW(float f = v.at(-5));
}

TEST(TVector, throws_when_set_element_with_too_large_index) {
	unsigned int mass_str[5] = { 4, 6 , 4, 45 };
	TVector<unsigned int> v(mass_str, 6);
	ASSERT_ANY_THROW(unsigned int f = v.at(96));
}

TEST(TVector, can_assign_vector_to_itself) {
	unsigned int mass_str[5] = { 4, 6 , 4, 45 };
	TVector<unsigned int> v(mass_str, 6);
	ASSERT_NO_THROW(v = v);
}

TEST(TVector, can_assign_vectors_of_equal_size) {
	unsigned int mass_str[5] = { 4, 6 , 4, 45, 5 };
	unsigned int mass_str2[5] = { 4, 8 , 9, 10, 8 };
	TVector<unsigned int> v(mass_str, 6);
	TVector<unsigned int> v2(mass_str2, 6);
	ASSERT_NO_THROW(v = v2);
	EXPECT_EQ(v = v2, v2);
}

TEST(TVector, can_assign_vectors_of_different_size) {
	unsigned int mass_str[5] = { 4, 6 , 4, 45, 5 };
	unsigned int mass_str2[13] = { 4, 8 , 9, 10, 8, 1, 2, 3, 4, 5, 6, 7, 45 };
	TVector<unsigned int> v(mass_str, 5);
	TVector<unsigned int> v2(mass_str2, 13);
	ASSERT_NO_THROW(v = v2);
	EXPECT_EQ(v = v2, v2);
}

TEST(TVector, assign_operator_change_vector_size) {
	unsigned int mass_str[5] = { 4, 6 , 4, 45, 5 };
	unsigned int mass_str2[13] = { 4, 8 , 9, 10, 8, 1, 2, 3, 4, 5, 6, 7, 45 };
	TVector<unsigned int> v(mass_str, 5);
	TVector<unsigned int> v2(mass_str2, 13);
	v = v2;
	EXPECT_EQ(v.size(), 13);
}

TEST(TVector, compare_equal_vectors_return_true) {
	unsigned int mass_str[5] = { 4, 6 , 4, 45, 5 };
	unsigned int mass_str2[5] = { 4, 6 , 4, 45, 5 };
	TVector<unsigned int> v(mass_str, 5);
	TVector<unsigned int> v2(mass_str2, 5);
	EXPECT_EQ(v == v2, 1);
}

TEST(TVector, compare_vector_with_itself_return_true) {
	unsigned int mass_str[5] = { 4, 6 , 4, 45, 5 };
	TVector<unsigned int> v(mass_str, 5);
	EXPECT_EQ(v == v, 1);
}

TEST(TVector, vectors_with_different_size_are_not_equal) {
	unsigned int mass_str[5] = { 4, 6 , 4, 45, 5 };
	unsigned int mass_str2[13] = { 4, 8 , 9, 10, 8, 1, 2, 3, 4, 5, 6, 7, 45 };
	TVector<unsigned int> v(mass_str, 5);
	TVector<unsigned int> v2(mass_str2, 13);
	EXPECT_NE(v, v2);
}

TEST(TVector, can_add_scalar_to_vector) {
	unsigned int mass_str[5] = { 4, 6 , 4, 45, 5 };
	unsigned int a = 8;
	unsigned int mass_str2[5] = { 12, 14 , 12, 53, 13 };
	TVector<unsigned int> v(mass_str, 5);
	TVector<unsigned int> v2(mass_str2, 5);
	v = v + a;
	EXPECT_EQ(v, v2);
}

TEST(TVector, can_subtract_scalar_from_vector) {
	int mass_str[5] = { 4, 6 , 4, 45, 5 };
	int a = 8;
	int mass_str2[5] = { -4, -2 , -4, 37, -3 };
	TVector<int> v(mass_str, 5);
	TVector<int> v2(mass_str2, 5);
	v = v - a;
	EXPECT_EQ(v, v2);
}

TEST(TVector, can_multiply_scalar_by_vector) {
	int mass_str[5] = { 4, 6 , 4, 45, 5 };
	int a = 8;
	int mass_str2[5] = { 32, 48 , 32, 360, 40 };
	TVector<int> v(mass_str, 5);
	TVector<int> v2(mass_str2, 5);
	v = v * a;
	EXPECT_EQ(v, v2);
}

TEST(TVector, can_add_vectors_with_equal_size) {
	unsigned int mass_str[5] = { 4, 6 , 4, 45, 5 };
	unsigned int mass_str2[5] = { 12, 14 , 12, 53, 13 };
	unsigned int mass_str3[5] = { 16, 20 , 16, 98, 18 };
	TVector<unsigned int> v(mass_str, 5);
	TVector<unsigned int> v2(mass_str2, 5);
	TVector<unsigned int> v3(mass_str3, 5);
	v = v + v2;
	EXPECT_EQ(v, v3);
}

TEST(TVector, cant_add_vectors_with_not_equal_size) {
	unsigned int mass_str[5] = { 4, 6 , 4, 45, 5 };
	unsigned int mass_str2[8] = { 12, 14 , 12, 53, 13, 14, 15, 16 };
	TVector<unsigned int> v(mass_str, 5);
	TVector<unsigned int> v2(mass_str2, 8);
	ASSERT_ANY_THROW(v + v2);
}

TEST(TVector, can_subtract_vectors_with_equal_size) {
	unsigned int mass_str[5] = { 4, 6 , 4, 45, 5 };
	unsigned int mass_str2[5] = { 12, 14 , 12, 53, 13 };
	unsigned int mass_str3[5] = { 8, 8 , 8, 8, 8 };
	TVector<unsigned int> v(mass_str, 5);
	TVector<unsigned int> v2(mass_str2, 5);
	TVector<unsigned int> v3(mass_str3, 5);
	v = v2 - v;
	EXPECT_EQ(v, v3);
}

TEST(TVector, cant_subtract_vectors_with_not_equal_size) {
	unsigned int mass_str[5] = { 4, 6 , 4, 45, 5 };
	unsigned int mass_str2[8] = { 12, 14 , 12, 53, 13, 14, 15, 16 };
	TVector<unsigned int> v(mass_str, 5);
	TVector<unsigned int> v2(mass_str2, 8);
	ASSERT_ANY_THROW(v - v2);
}

TEST(TVector, can_multiply_vectors_with_equal_size) {
	int mass_str[5] = { 4, 6, 4, 45, 5 };
	int a;
	int b = 4 * 2 + 6 * 3 + 4 * 4 + 45 + 10;
	int mass_str2[5] = { 2, 3, 4, 1, 2 };
	TVector<int> v(mass_str, 5);
	TVector<int> v2(mass_str2, 5);
	a = v * v2;
	EXPECT_EQ(a, b);
}

TEST(TVector, cant_multiply_vectors_with_not_equal_size) {
	unsigned int mass_str[5] = { 4, 6 , 4, 45, 5 };
	unsigned int mass_str2[8] = { 12, 14 , 12, 53, 13, 14, 15, 16 };
	TVector<unsigned int> v(mass_str, 5);
	TVector<unsigned int> v2(mass_str2, 8);
	ASSERT_ANY_THROW(v * v2);
}

TEST(TVector, can_iterator) {
	unsigned int mass_str[5] = { 4, 6 , 4, 45, 5 };
	TVector<unsigned int> v(mass_str, 5);
	for (TVector<unsigned int>::iterator i = v.begin(); i != v.end(); ++i) {
		std::cout << *i << " ";
	}
}
