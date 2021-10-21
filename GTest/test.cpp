#include "pch.h"
#include "../myvector.h"

struct VectorFixture : public testing::Test
{
	const size_t elementCounter{ 5 };
	MyVector<int>* vector = new MyVector<int>;

	void SetUp() override {
		for (size_t i = 0; i < elementCounter; ++i) {
			vector->push_back(i);
		}
	}

	void TearDown() override {

	}
};

TEST_F(VectorFixture, push_back) {
	//Arrange

	//Act

	//Assert
	EXPECT_EQ(vector->size(), elementCounter);
}

TEST_F(VectorFixture, pop_back) {
	//Arrange

	//Act
	for (size_t i = 0; i < elementCounter; ++i) {
		vector->pop_back();
	}

	//Assert
	EXPECT_EQ(vector->size(), 0);
}

TEST_F(VectorFixture, reserve) {
	//Arrange
	const size_t reserveSize{ 10 };

	//Act
	vector->reserve(reserveSize);

	//Assert
	EXPECT_EQ(vector->capacity(), reserveSize);
	EXPECT_EQ(vector->size(), elementCounter);
}

TEST_F(VectorFixture, resize) {
	//Arrange
	const size_t newSize{ 10 };

	//Act
	vector->resize(newSize);

	//Assert
	EXPECT_EQ(vector->size(), newSize);
}

TEST_F(VectorFixture, insert) {
	//Arrange
	const size_t index{ 2 };
	int newElement{ -1 };

	//Act
	vector->insert(index, newElement);

	//Assert
	EXPECT_EQ(vector->at(index), newElement);
	EXPECT_EQ(vector->size(), elementCounter + 1);
}

TEST_F(VectorFixture, erase) {
	//Arrange
	const size_t index{ 1 };

	//Act
	vector->erase(index);

	//Assert
	EXPECT_EQ(vector->size(), elementCounter - 1);
}

TEST_F(VectorFixture, clear) {
	//Arrange

	//Act
	vector->clear();

	//Assert
	EXPECT_EQ(vector->size(), 0);
	EXPECT_TRUE(vector->empty());
}

TEST_F(VectorFixture, front) {
	//Arrange

	//Act

	//Assert
	EXPECT_EQ(vector->front(), 0);
}

TEST_F(VectorFixture, back) {
	//Arrange

	//Act

	//Assert
	EXPECT_EQ(vector->back(), elementCounter - 1);
}