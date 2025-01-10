#include <unity.h>
#include "Pose.hpp"

void setUp(void) 
{
    Pose currentPose(0, 0, 0);
    Pose targetPose(0, 3, 0);
}

void tearDown(void) 
{
    // clean stuff up here
}

void test_calculate_distance(void) 
{
    Pose currentPose(0, 0, 0);
    Pose targetPose(0, 3, 0);
    float expected = sqrt((0 - 0) * (0 - 0) + (0 - 3) * (0 - 3));
    float actual = currentPose.distanceTo(targetPose);

    TEST_ASSERT_EQUAL(expected, actual);
}


int main( int argc, char **argv) 
{
    UNITY_BEGIN();
    RUN_TEST(test_calculate_distance);
    UNITY_END();

    return 0;
}
