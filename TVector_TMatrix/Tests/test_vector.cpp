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
