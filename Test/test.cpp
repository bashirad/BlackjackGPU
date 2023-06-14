#include "pch.h"

/*#include "../include/gtest/gtest.h"
#include "../Current_CUDA_BCG/include/Card.h"
#include "../Current_CUDA_BCG/include/GA.h"
#include "../Current_CUDA_BCG/include/Game.h"
#include "../Current_CUDA_BCG/include/Hand.h"
#include "../Current_CUDA_BCG/include/Helpers.h"
#include "../Current_CUDA_BCG/include/Kpax.h"
#include "../Current_CUDA_BCG/include/Player.h"
#include "../Current_CUDA_BCG/include/Population.h"
#include "../Current_CUDA_BCG/include/Strategy.h"
#include "../Current_CUDA_BCG/include/Utils.h"*/

//#include "tests\CrossFunction\Basic.cpp"
#include "tests/testAdd.cpp"

//extern int _cdecl add(int a, int b);

TEST(TestCaseName, GoogleTest) {
  EXPECT_EQ(1, 1);
  //EXPECT_TRUE(true);
}

TEST(TestCaseName, Addition) {
  EXPECT_EQ(9, add(4,5));
  //EXPECT_TRUE(true);
}

TEST(, ) {
	printf("Test Passed");
}

/*
TEST(TestCaseName, Basic) {
  EXPECT_EQ(true, Basic());
  EXPECT_TRUE(true);
}*/