#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <serveraccess.h>

using namespace testing;

TEST(MainTest, MainTestSet)
{
//    ServerAccess(QString{});
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}
