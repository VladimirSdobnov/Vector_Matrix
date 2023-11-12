#include "../TMatrix/matrix.h"
#include "../qtest/gtest.h"

TEST(TMatrix, can_create_matrix_with_positive_length) {
  ASSERT_NO_THROW(TMatrix<int> m(5));
}

TEST(TMatrix, cant_create_too_large_matrix) {
  ASSERT_ANY_THROW(TMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TMatrix, throws_when_create_matrix_with_negative_length) {
  ASSERT_ANY_THROW(TMatrix<int> m(-5));
}

TEST(TMatrix, can_create_copied_matrix) {
  TMatrix<int> m(5);

  ASSERT_NO_THROW(TMatrix<int> m1(m));
}

TEST(TMatrix, copied_matrix_is_equal_to_source_one) {
	TMatrix<int> m1(5);
	TMatrix<int> m2(m1);
	ASSERT_EQ(m1, m2);
}

TEST(TVector, copied_matrix_has_its_own_memory) {
	TMatrix<std::string> m(5);
	TMatrix<std::string> m2(m);
	EXPECT_NE(&m, &m2);
}

TEST(TMatrix, can_get_size) {
	TMatrix<int> m1(100);
	ASSERT_EQ(m1.size(), 100);
}

TEST(TMatrix, can_set_and_get_element) {
	TMatrix<int> m1(6);
	for (int i = 0; i < m1.size(); i++) {
		m1[i][i] = i;
	}
	for (int i = 0; i < m1.size(); i++) {
		ASSERT_EQ(m1[i][i], i);
	}
}

TEST(TMatrix, throws_when_set_element_with_negative_index) {
	TMatrix<int> m1(6);
	ASSERT_ANY_THROW(m1.at(-6).at(7));
}

TEST(TMatrix, throws_when_set_element_with_too_large_index) {
	TMatrix<int> m1(6);
	ASSERT_ANY_THROW(m1.at(30).at(7));
}

TEST(TMatrix, can_assign_matrix_to_itself) {
	TMatrix<int> m1(6);
	ASSERT_NO_THROW(m1 = m1);
}

TEST(TMatrix, can_assign_matrices_of_equal_size) {
	TMatrix<int> m1(6);
	TMatrix<int> m3(6);
	ASSERT_NO_THROW(m1 = m3);
}

TEST(TMatrix, can_assign_matrices_of_different_size) {
	TMatrix<int> m1(6);
	TMatrix<int> m3(10);
	ASSERT_NO_THROW(m1 = m3);
}

TEST(TMatrix, assign_operator_change_matrix_size) {
	TMatrix<int> m1(6);
	TMatrix<int> m3(10);
	m1 = m3;
	ASSERT_EQ(m1.size(), m3.size());
}

TEST(TMatrix, compare_equal_matrices_return_true) {
	TMatrix<int> m1(6);
	TMatrix<int> m3(6);
	m1 = m3;
	ASSERT_EQ(m1 == m3, true);
}

TEST(TMatrix, compare_matrix_with_itself_return_true) {
	TMatrix<int> m1(6);
	ASSERT_EQ(m1 == m1, true);
}

TEST(TMatrix, matrices_with_different_size_are_not_equal) {
	TMatrix<int> m1(6);
	TMatrix<int> m3(10);
	ASSERT_EQ(m1 == m3, false);
}

TEST(TMatrix, can_multiply_val) {
	TMatrix<int> m1(6);
	TMatrix<int> res(6);
	int val = 6;
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m1.size(); j++) {
			m1[i][j] = (i + 1) * (j + 1);
		}
	}
	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j < res.size(); j++) {
			res[i][j] = (i + 1) * (j + 1) * val;
		}
	}
	m1 = m1 * val;
	ASSERT_EQ(m1, res);
}

TEST(TMatrix, can_multiply_vector) {
	TMatrix<int> m1(3);
	TVector<int> v(3);
	TVector<int> res(3);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m1.size(); j++) {
			m1[i][j] = i + 1;
		}
	}
	for (int i = 0; i < v.size(); i++) {
		v[i] = i + 1;
		res[i] = (i + 1) * 6;
	}
	v = m1 * v;
	ASSERT_EQ(v, res);
}

TEST(TMatrix, can_multiply_vector_different_size) {
	TMatrix<int> m1(3);
	TVector<int> v(6);
	TVector<int> res(3);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m1.size(); j++) {
			m1[i][j] = i + 1;
		}
		res[i] = (i + 1) * 6;
	}
	for (int i = 0; i < v.size(); i++) {
		v[i] = i + 1;
	}
	v = m1 * v;
	ASSERT_EQ(v, res);
}

TEST(TMatrix, can_add_matrices_with_equal_size) {
	TMatrix<int> m1(6);
	TMatrix<int> m2(6);
	TMatrix<int> res(6);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m1.size(); j++) {
			m1[i][j] = (i + 1) * (j + 1);
		}
	}
	for (int i = 0; i < m2.size(); i++) {
		for (int j = 0; j < m2.size(); j++) {
			m2[i][j] = (i + 1) * (j + 1) + 10;
		}
	}
	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j < res.size(); j++) {
			res[i][j] = (i + 1) * (j + 1) + (i + 1) * (j + 1) + 10;
		}
	}
	m1 = m1 + m2;
	ASSERT_EQ(m1, res);
}

TEST(TMatrix, can_subtract_matrices_with_equal_size) {
	TMatrix<int> m1(6);
	TMatrix<int> m2(6);
	TMatrix<int> res(6);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m1.size(); j++) {
			m1[i][j] = (i + 1) * (j + 1);
		}
	}
	for (int i = 0; i < m2.size(); i++) {
		for (int j = 0; j < m2.size(); j++) {
			m2[i][j] = (i + 1) * (j + 1) + 10;
		}
	}
	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j < res.size(); j++) {
			res[i][j] = (i + 1) * (j + 1) - (i + 1) * (j + 1) - 10;
		}
	}
	m1 = m1 - m2;
	ASSERT_EQ(m1, res);
}

TEST(TMatrix, cant_add_matrices_with_dif_size) {
	TMatrix<int> m1(6);
	TMatrix<int> m2(7);
	TMatrix<int> res(6);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m1.size(); j++) {
			m1[i][j] = (i + 1) * (j + 1);
		}
	}
	for (int i = 0; i < m2.size(); i++) {
		for (int j = 0; j < m2.size(); j++) {
			m2[i][j] = (i + 1) * (j + 1) + 10;
		}
	}
	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j < res.size(); j++) {
			res[i][j] = (i + 1) * (j + 1) + (i + 1) * (j + 1) + 10;
		}
	}
	ASSERT_ANY_THROW(m1 = m1 + m2);
}

TEST(TMatrix, cant_subtract_matrices_with_dif_size) {
	TMatrix<int> m1(6);
	TMatrix<int> m2(7);
	TMatrix<int> res(6);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m1.size(); j++) {
			m1[i][j] = (i + 1) * (j + 1);
		}
	}
	for (int i = 0; i < m2.size(); i++) {
		for (int j = 0; j < m2.size(); j++) {
			m2[i][j] = (i + 1) * (j + 1) + 10;
		}
	}
	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j < res.size(); j++) {
			res[i][j] = (i + 1) * (j + 1) - (i + 1) * (j + 1) - 10;
		}
	}
	ASSERT_ANY_THROW(m1 = m1 - m2);
}

TEST(TMatrix, cant_muliply_matrices_with_dif_size) {
	TMatrix<int> m1(6);
	TMatrix<int> m2(7);
	TMatrix<int> res(6);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m1.size(); j++) {
			m1[i][j] = (i + 1) * (j + 1);
		}
	}
	for (int i = 0; i < m2.size(); i++) {
		for (int j = 0; j < m2.size(); j++) {
			m2[i][j] = (i + 1) * (j + 1) + 10;
		}
	}
	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j < res.size(); j++) {
			res[i][j] = (i + 1) * (j + 1) - (i + 1) * (j + 1) - 10;
		}
	}
	ASSERT_ANY_THROW(m1 = m1 - m2);
}

TEST(TMatrix, can_multiply_matrices_with_equal_size) {
	TMatrix<int> m1(3);
	TMatrix<int> m2(3);
	TMatrix<int> res(3);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j < m1.size(); j++) {
			m1[i][j] = (i + 1);
		}
	}
	for (int i = 0; i < m2.size(); i++) {
		for (int j = 0; j < m2.size(); j++) {
			m2[i][j] = (j + 1);
		}
	}
	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j < res.size(); j++) {
			res[i][j] = 3 * (i + 1) * (j + 1);
		}
	}
	m1 = m1 * m2;
	ASSERT_EQ(m1, res);
}

//UpTrianglMatrix tests

TEST(UpTrianglTMatrix, can_create_UpTrianglTMatrix_with_positive_length) {
	ASSERT_NO_THROW(UpTrianglTMatrix<int> m(5));
}

TEST(UpTrianglTMatrix, cant_create_too_large_UpTrianglTMatrix) {
	ASSERT_ANY_THROW(UpTrianglTMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(UpTrianglTMatrix, throws_when_create_UpTrianglTMatrix_with_negative_length) {
	ASSERT_ANY_THROW(UpTrianglTMatrix<int> m(-5));
}

TEST(UpTrianglTMatrix, can_create_copied_UpTrianglTMatrix) {
	UpTrianglTMatrix<int> m(5);

	ASSERT_NO_THROW(UpTrianglTMatrix<int> m1(m));
}

TEST(UpTrianglTMatrix, copied_UpTrianglTMatrix_is_equal_to_source_one) {
	UpTrianglTMatrix<int> m1(5);
	UpTrianglTMatrix<int> m2(m1);
	ASSERT_EQ(m1, m2);
}

TEST(UpTrianglTMatrix, copied_UpTrianglTMatrix_has_its_own_memory) {
	UpTrianglTMatrix<std::string> m(5);
	UpTrianglTMatrix<std::string> m2(m);
	EXPECT_NE(&m, &m2);
}

TEST(UpTrianglTMatrix, can_get_size) {
	UpTrianglTMatrix<int> m1(100);
	ASSERT_EQ(m1.size(), 100);
}

TEST(UpTrianglTMatrix, can_cout) {
	UpTrianglTMatrix<int> m1(7);
	ASSERT_NO_THROW(std::cout << m1);
}

TEST(UpTrianglTMatrix, can_set_and_get_element) {
	UpTrianglTMatrix<int> m1(7);
	for (int i = 0; i < m1.size(); i++) {
		m1[i][m1.size() - 1 - i] = i;
	}
	for (int i = 0; i < m1.size(); i++) {
		ASSERT_EQ(m1[i][m1.size() - 1 - i], i);
	}
}

TEST(UpTrianglTMatrix, throws_when_set_element_with_negative_index) {
	UpTrianglTMatrix<int> m1(6);
	ASSERT_ANY_THROW(m1.at(-6).at(7));
}

TEST(UpTrianglTMatrix, throws_when_set_element_with_too_large_index) {
	UpTrianglTMatrix<int> m1(6);
	ASSERT_ANY_THROW(m1.at(30).at(7));
}

TEST(UpTrianglTMatrix, can_assign_matrix_to_itself) {
	UpTrianglTMatrix<int> m1(6);
	ASSERT_NO_THROW(m1 = m1);
}

TEST(UpTrianglTMatrix, can_assign_matrices_of_equal_size) {
	UpTrianglTMatrix<int> m1(6);
	UpTrianglTMatrix<int> m3(6);
	ASSERT_NO_THROW(m1 = m3);
}

TEST(UpTrianglTMatrix, can_assign_matrices_of_different_size) {
	UpTrianglTMatrix<int> m1(6);
	UpTrianglTMatrix<int> m3(10);
	ASSERT_NO_THROW(m1 = m3);
}

TEST(UpTrianglTMatrix, assign_operator_change_matrix_size) {
	UpTrianglTMatrix<int> m1(6);
	UpTrianglTMatrix<int> m3(10);
	m1 = m3;
	ASSERT_EQ(m1.size(), m3.size());
}

TEST(UpTrianglTMatrix, compare_equal_matrices_return_true) {
	UpTrianglTMatrix<int> m1(6);
	UpTrianglTMatrix<int> m3(6);
	m1 = m3;
	ASSERT_EQ(m1 == m3, true);
}

TEST(UpTrianglTMatrix, compare_matrix_with_itself_return_true) {
	UpTrianglTMatrix<int> m1(6);
	ASSERT_EQ(m1 == m1, true);
}

TEST(UpTrianglTMatrix, matrices_with_different_size_are_not_equal) {
	UpTrianglTMatrix<int> m1(6);
	UpTrianglTMatrix<int> m3(10);
	ASSERT_EQ(m1 == m3, false);
}

TEST(UpTrianglTMatrix, can_multiply_val) {
	UpTrianglTMatrix<int> m1(6);
	UpTrianglTMatrix<int> res(6);
	int val = 6;
	for (int i = 0; i < m1.size(); i++) {
		for (int j = i; j < m1.size(); j++) {
			if (i == j) { m1[i][j] = 2; }
			else { m1[i][j] = 0; }
		}
	}
	for (int i = 0; i < m1.size(); i++) {
		for (int j = i; j < m1.size(); j++) {
			if (i == j) { res[i][j] = m1[i][j] * val; }
			else { res[i][j] = 0; }
		}
	}
	m1 = m1 * val;
	ASSERT_EQ(m1, res);
}

TEST(UpTrianglTMatrix, can_multiply_vector) {
	UpTrianglTMatrix<int> m1(3);
	TVector<int> v(3);
	TVector<int> res(3);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = i; j < m1.size(); j++) {
			m1[i][j] = i + 1;
		}
	}
	for (int i = 0; i < v.size(); i++) {
		v[i] = i + 1;
	}
	for (int i = 0; i < res.size(); i++) {
		res[i] = m1[i] * v;
	}
	v = m1 * v;
	ASSERT_EQ(v, res);
}

TEST(UpTrianglTMatrix, can_multiply_vector_different_size) {
	UpTrianglTMatrix<int> m1(3);
	TVector<int> v(6);
	TVector<int> res(3);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = i; j < m1.size(); j++) {
			m1[i][j] = i + 1;
		}
	}
	for (int i = 0; i < v.size(); i++) {
		v[i] = i + 1;
	}
	for (int i = 0; i < res.size(); i++) {
		res[i] = m1[i] * v;
	}
	v = m1 * v;
	ASSERT_EQ(v, res);
}

TEST(UpTrianglTMatrix, can_add_matrices_with_equal_size) {
	UpTrianglTMatrix<int> m1(6);
	UpTrianglTMatrix<int> m2(6);
	UpTrianglTMatrix<int> res(6);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = i; j < m1.size(); j++) {
			m1[i][j] = (i + 1) * (j + 1);
		}
	}
	for (int i = 0; i < m2.size(); i++) {
		for (int j = i; j < m2.size(); j++) {
			m2[i][j] = (i + 1) * (j + 1) + 10;
		}
	}
	for (int i = 0; i < res.size(); i++) {
		for (int j = i; j < res.size(); j++) {
			res[i][j] = (i + 1) * (j + 1) + (i + 1) * (j + 1) + 10;
		}
	}
	m1 = m1 + m2;
	ASSERT_EQ(m1, res);
}

TEST(UpTrianglTMatrix, can_subtract_matrices_with_equal_size) {
	UpTrianglTMatrix<int> m1(6);
	UpTrianglTMatrix<int> m2(6);
	UpTrianglTMatrix<int> res(6);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = i; j < m1.size(); j++) {
			m1[i][j] = (i + 1) * (j + 1);
		}
	}
	for (int i = 0; i < m2.size(); i++) {
		for (int j = i; j < m2.size(); j++) {
			m2[i][j] = (i + 1) * (j + 1) + 10;
		}
	}
	for (int i = 0; i < res.size(); i++) {
		for (int j = i; j < res.size(); j++) {
			res[i][j] = (i + 1) * (j + 1) - (i + 1) * (j + 1) - 10;
		}
	}
	m1 = m1 - m2;
	ASSERT_EQ(m1, res);
}

TEST(UpTrianglTMatrix, cant_add_matrices_with_dif_size) {
	UpTrianglTMatrix<int> m1(6);
	UpTrianglTMatrix<int> m2(7);
	UpTrianglTMatrix<int> res(6);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = i; j < m1.size(); j++) {
			m1[i][j] = (i + 1) * (j + 1);
		}
	}
	for (int i = 0; i < m2.size(); i++) {
		for (int j = i; j < m2.size(); j++) {
			m2[i][j] = (i + 1) * (j + 1) + 10;
		}
	}
	for (int i = 0; i < res.size(); i++) {
		for (int j = i; j < res.size(); j++) {
			res[i][j] = (i + 1) * (j + 1) + (i + 1) * (j + 1) + 10;
		}
	}
	ASSERT_ANY_THROW(m1 = m1 + m2);
}

TEST(UpTrianglTMatrix, cant_subtract_matrices_with_dif_size) {
	UpTrianglTMatrix<int> m1(6);
	UpTrianglTMatrix<int> m2(7);
	UpTrianglTMatrix<int> res(6);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = i; j < m1.size(); j++) {
			m1[i][j] = (i + 1) * (j + 1);
		}
	}
	for (int i = 0; i < m2.size(); i++) {
		for (int j = i; j < m2.size(); j++) {
			m2[i][j] = (i + 1) * (j + 1) + 10;
		}
	}
	for (int i = 0; i < res.size(); i++) {
		for (int j = i; j < res.size(); j++) {
			res[i][j] = (i + 1) * (j + 1) - (i + 1) * (j + 1) - 10;
		}
	}
	ASSERT_ANY_THROW(m1 = m1 - m2);
}

TEST(UpTrianglTMatrix, cant_muliply_matrices_with_dif_size) {
	UpTrianglTMatrix<int> m1(6);
	UpTrianglTMatrix<int> m2(7);
	UpTrianglTMatrix<int> res(6);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = i; j < m1.size(); j++) {
			m1[i][j] = (i + 1) * (j + 1);
		}
	}
	for (int i = 0; i < m2.size(); i++) {
		for (int j = i; j < m2.size(); j++) {
			m2[i][j] = (i + 1) * (j + 1) + 10;
		}
	}
	for (int i = 0; i < res.size(); i++) {
		for (int j = i; j < res.size(); j++) {
			res[i][j] = (i + 1) * (j + 1) - (i + 1) * (j + 1) - 10;
		}
	}
	ASSERT_ANY_THROW(m1 = m1 - m2);
}

TEST(UpTrianglTMatrix, can_multiply_matrices_with_equal_size) {
	UpTrianglTMatrix<int> m1(3);
	UpTrianglTMatrix<int> m2(3);
	UpTrianglTMatrix<int> res(3);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = i; j < m1.size(); j++) {
			m1[i][j] = (i + 1);
		}
	}
	for (int i = 0; i < m2.size(); i++) {
		for (int j = i; j < m2.size(); j++) {
			m2[i][j] = (j + 1);
		}
	}
	res[0][0] = 1;
	res[0][1] = 4;
	res[0][2] = 9;
	res[1][1] = 4;
	res[1][2] = 12;
	res[2][2] = 9;
	m1 = m1 * m2;
	ASSERT_EQ(m1, res);
}


//DownTrianglMatrix tests

TEST(DownTrianglTMatrix, can_create_DownTrianglTMatrix_with_positive_length) {
	ASSERT_NO_THROW(DownTrianglTMatrix<int> m(5));
}

TEST(DownTrianglTMatrix, cant_create_too_large_DownTrianglTMatrix) {
	ASSERT_ANY_THROW(DownTrianglTMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(DownTrianglTMatrix, throws_when_create_DownTrianglTMatrix_with_negative_length) {
	ASSERT_ANY_THROW(DownTrianglTMatrix<int> m(-5));
}

TEST(DownTrianglTMatrix, can_create_copied_DownTrianglTMatrix) {
	DownTrianglTMatrix<int> m(5);

	ASSERT_NO_THROW(DownTrianglTMatrix<int> m1(m));
}

TEST(DownTrianglTMatrix, copied_DownTrianglTMatrix_is_equal_to_source_one) {
	DownTrianglTMatrix<int> m1(5);
	DownTrianglTMatrix<int> m2(m1);
	ASSERT_EQ(m1, m2);
}

TEST(DownTrianglTMatrix, copied_DownTrianglTMatrix_has_its_own_memory) {
	DownTrianglTMatrix<std::string> m(5);
	DownTrianglTMatrix<std::string> m2(m);
	EXPECT_NE(&m, &m2);
}

TEST(DownTrianglTMatrix, can_get_size) {
	DownTrianglTMatrix<int> m1(100);
	ASSERT_EQ(m1.size(), 100);
}

TEST(DownTrianglTMatrix, can_cout) {
	DownTrianglTMatrix<int> m1(7);
	ASSERT_NO_THROW(std::cout << m1);
}

TEST(DownTrianglTMatrix, can_set_and_get_element) {
	DownTrianglTMatrix<int> m1(7);
	for (int i = 0; i < m1.size(); i++) {
		m1[i][i] = i;
	}
	for (int i = 0; i < m1.size(); i++) {
		ASSERT_EQ(m1[i][i], i);
	}
}

TEST(DownTrianglTMatrix, throws_when_set_element_with_negative_index) {
	DownTrianglTMatrix<int> m1(6);
	ASSERT_ANY_THROW(m1.at(-6).at(7));
}

TEST(DownTrianglTMatrix, throws_when_set_element_with_too_large_index) {
	DownTrianglTMatrix<int> m1(6);
	ASSERT_ANY_THROW(m1.at(30).at(7));
}

TEST(DownTrianglTMatrix, can_assign_matrix_to_itself) {
	DownTrianglTMatrix<int> m1(6);
	ASSERT_NO_THROW(m1 = m1);
}

TEST(DownTrianglTMatrix, can_assign_matrices_of_equal_size) {
	DownTrianglTMatrix<int> m1(6);
	DownTrianglTMatrix<int> m3(6);
	ASSERT_NO_THROW(m1 = m3);
}

TEST(DownTrianglTMatrix, can_assign_matrices_of_different_size) {
	DownTrianglTMatrix<int> m1(6);
	DownTrianglTMatrix<int> m3(10);
	ASSERT_NO_THROW(m1 = m3);
}

TEST(DownTrianglTMatrix, assign_operator_change_matrix_size) {
	DownTrianglTMatrix<int> m1(6);
	DownTrianglTMatrix<int> m3(10);
	m1 = m3;
	ASSERT_EQ(m1.size(), m3.size());
}

TEST(DownTrianglTMatrix, compare_equal_matrices_return_true) {
	DownTrianglTMatrix<int> m1(6);
	DownTrianglTMatrix<int> m3(6);
	m1 = m3;
	ASSERT_EQ(m1 == m3, true);
}

TEST(DownTrianglTMatrix, compare_matrix_with_itself_return_true) {
	DownTrianglTMatrix<int> m1(6);
	ASSERT_EQ(m1 == m1, true);
}

TEST(DownTrianglTMatrix, matrices_with_different_size_are_not_equal) {
	DownTrianglTMatrix<int> m1(6);
	DownTrianglTMatrix<int> m3(10);
	ASSERT_EQ(m1 == m3, false);
}

TEST(DownTrianglTMatrix, can_multiply_val) {
	DownTrianglTMatrix<int> m1(6);
	DownTrianglTMatrix<int> res(6);
	int val = 6;
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j <= i; j++) {
			if (i == j) { m1[i][j] = 2; }
			else { m1[i][j] = 0; }
		}
	}
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j <= i; j++) {
			if (i == j) { res[i][j] = m1[i][j] * val; }
			else { res[i][j] = 0; }
		}
	}
	m1 = m1 * val;
	ASSERT_EQ(m1, res);
}

TEST(DownTrianglTMatrix, can_multiply_vector) {
	DownTrianglTMatrix<int> m1(3);
	TVector<int> v(3);
	TVector<int> res(3);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j <= i; j++) {
			m1[i][j] = i + 1;
		}
	}
	for (int i = 0; i < v.size(); i++) {
		v[i] = i + 1;
	}
	for (int i = 0; i < res.size(); i++) {
		res[i] = m1[i] * v;
	}
	v = m1 * v;
	ASSERT_EQ(v, res);
}

TEST(DownTrianglTMatrix, can_multiply_vector_different_size) {
	DownTrianglTMatrix<int> m1(3);
	TVector<int> v(6);
	TVector<int> res(3);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j <= i; j++) {
			m1[i][j] = i + 1;
		}
	}
	for (int i = 0; i < v.size(); i++) {
		v[i] = i + 1;
	}
	for (int i = 0; i < res.size(); i++) {
		res[i] = m1[i] * v;
	}
	v = m1 * v;
	ASSERT_EQ(v, res);
}

TEST(DownTrianglTMatrix, can_add_matrices_with_equal_size) {
	DownTrianglTMatrix<int> m1(6);
	DownTrianglTMatrix<int> m2(6);
	DownTrianglTMatrix<int> res(6);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j <= i; j++) {
			m1[i][j] = (i + 1) * (j + 1);
		}
	}
	for (int i = 0; i < m2.size(); i++) {
		for (int j = 0; j <= i; j++) {
			m2[i][j] = (i + 1) * (j + 1) + 10;
		}
	}
	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j <= i; j++) {
			res[i][j] = (i + 1) * (j + 1) + (i + 1) * (j + 1) + 10;
		}
	}
	m1 = m1 + m2;
	ASSERT_EQ(m1, res);
}

TEST(DownTrianglTMatrix, can_subtract_matrices_with_equal_size) {
	DownTrianglTMatrix<int> m1(6);
	DownTrianglTMatrix<int> m2(6);
	DownTrianglTMatrix<int> res(6);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j <= i; j++) {
			m1[i][j] = (i + 1) * (j + 1);
		}
	}
	for (int i = 0; i < m2.size(); i++) {
		for (int j = 0; j <= i; j++) {
			m2[i][j] = (i + 1) * (j + 1) + 10;
		}
	}
	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j <= i; j++) {
			res[i][j] = (i + 1) * (j + 1) - (i + 1) * (j + 1) - 10;
		}
	}
	m1 = m1 - m2;
	ASSERT_EQ(m1, res);
}

TEST(DownTrianglTMatrix, cant_add_matrices_with_dif_size) {
	DownTrianglTMatrix<int> m1(6);
	DownTrianglTMatrix<int> m2(7);
	DownTrianglTMatrix<int> res(6);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j <= i; j++) {
			m1[i][j] = (i + 1) * (j + 1);
		}
	}
	for (int i = 0; i < m2.size(); i++) {
		for (int j = 0; j <= i; j++) {
			m2[i][j] = (i + 1) * (j + 1) + 10;
		}
	}
	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j <= i; j++) {
			res[i][j] = (i + 1) * (j + 1) + (i + 1) * (j + 1) + 10;
		}
	}
	ASSERT_ANY_THROW(m1 = m1 + m2);
}

TEST(DownTrianglTMatrix, cant_subtract_matrices_with_dif_size) {
	DownTrianglTMatrix<int> m1(6);
	DownTrianglTMatrix<int> m2(7);
	DownTrianglTMatrix<int> res(6);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j <= i; j++) {
			m1[i][j] = (i + 1) * (j + 1);
		}
	}
	for (int i = 0; i < m2.size(); i++) {
		for (int j = 0; j <= i; j++) {
			m2[i][j] = (i + 1) * (j + 1) + 10;
		}
	}
	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j <= i; j++) {
			res[i][j] = (i + 1) * (j + 1) - (i + 1) * (j + 1) - 10;
		}
	}
	ASSERT_ANY_THROW(m1 = m1 - m2);
}

TEST(DownTrianglTMatrix, cant_muliply_matrices_with_dif_size) {
	DownTrianglTMatrix<int> m1(6);
	DownTrianglTMatrix<int> m2(7);
	DownTrianglTMatrix<int> res(6);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j <= i; j++) {
			m1[i][j] = (i + 1) * (j + 1);
		}
	}
	for (int i = 0; i < m2.size(); i++) {
		for (int j = 0; j <= i; j++) {
			m2[i][j] = (i + 1) * (j + 1) + 10;
		}
	}
	for (int i = 0; i < res.size(); i++) {
		for (int j = 0; j <= i; j++) {
			res[i][j] = (i + 1) * (j + 1) - (i + 1) * (j + 1) - 10;
		}
	}
	ASSERT_ANY_THROW(m1 = m1 - m2);
}

TEST(DownTrianglTMatrix, can_multiply_matrices_with_equal_size) {
	DownTrianglTMatrix<int> m1(3);
	DownTrianglTMatrix<int> m2(3);
	DownTrianglTMatrix<int> res(3);
	for (int i = 0; i < m1.size(); i++) {
		for (int j = 0; j <= i; j++) {
			m1[i][j] = (j + 1);
		}
	}
	for (int i = 0; i < m2.size(); i++) {
		for (int j = 0; j <= i; j++) {
			m2[i][j] = i + 1;
		}
	}
	res[0][0] = 1;
	res[1][0] = 5;
	res[1][1] = 4;
	res[2][0] = 14;
	res[2][1] = 13;
	res[2][2] = 9;
	m1 = m1 * m2;
	ASSERT_EQ(m1, res);
}