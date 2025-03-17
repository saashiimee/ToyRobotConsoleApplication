#include "pch.h"
#include "CppUnitTest.h"
#include "../ToyRobotConsoleApplication/ToyRobotConsoleApplication.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ToyRobotUnitTest
{
	TEST_CLASS(ToyRobotUnitTest)
	{
	public:
		TEST_METHOD(TestPlaceValid)
		{
			Robot robot;
			Assert::IsTrue(robot.place(0, 0, Direction::NORTH));
			Assert::IsTrue(robot.isPlaced());
		}

		TEST_METHOD(TestPlaceInvalid)
		{
			Robot robot;
			Assert::IsFalse(robot.place(5, 5, Direction::NORTH));
			Assert::IsFalse(robot.isPlaced());
		}

        TEST_METHOD(TestMoveValid)
        {
            Robot robot;
            robot.place(0, 0, Direction::NORTH);
            robot.move();
            std::ostringstream oss;
            std::streambuf* p_cout_streambuf = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());
            robot.report();
            std::cout.rdbuf(p_cout_streambuf);
            Assert::AreEqual(std::string("0,1,NORTH\n"), oss.str());
        }

        TEST_METHOD(TestMoveInvalid)
        {
            Robot robot;
            robot.place(0, 4, Direction::NORTH);
            robot.move();
            std::ostringstream oss;
            std::streambuf* p_cout_streambuf = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());
            robot.report();
            std::cout.rdbuf(p_cout_streambuf);
            Assert::AreEqual(std::string("0,4,NORTH\n"), oss.str());
        }

        TEST_METHOD(TestTurnLeft)
        {
            Robot robot;
            robot.place(0, 0, Direction::NORTH);
            robot.turnLeft();
            std::ostringstream oss;
            std::streambuf* p_cout_streambuf = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());
            robot.report();
            std::cout.rdbuf(p_cout_streambuf);
            Assert::AreEqual(std::string("0,0,WEST\n"), oss.str());
        }

        TEST_METHOD(TestTurnRight)
        {
            Robot robot;
            robot.place(0, 0, Direction::NORTH);
            robot.turnRight();
            std::ostringstream oss;
            std::streambuf* p_cout_streambuf = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());
            robot.report();
            std::cout.rdbuf(p_cout_streambuf);
            Assert::AreEqual(std::string("0,0,EAST\n"), oss.str());
        }

        TEST_METHOD(TestReport)
        {
            Robot robot;
            robot.place(1, 2, Direction::EAST);
            std::ostringstream oss;
            std::streambuf* p_cout_streambuf = std::cout.rdbuf();
            std::cout.rdbuf(oss.rdbuf());
            robot.report();
            std::cout.rdbuf(p_cout_streambuf);
            Assert::AreEqual(std::string("1,2,EAST\n"), oss.str());
        }

        TEST_METHOD(TestIsPlaced)
        {
            Robot robot;
            Assert::IsFalse(robot.isPlaced());
            robot.place(0, 0, Direction::NORTH);
            Assert::IsTrue(robot.isPlaced());
        }
	};
}
