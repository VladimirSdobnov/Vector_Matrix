#include "../TMatrix/matrix.h"
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
