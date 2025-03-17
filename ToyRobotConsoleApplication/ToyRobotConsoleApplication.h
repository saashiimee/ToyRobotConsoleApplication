#pragma once

// ToyRobotConsoleApplication.h
#include <string>
#include <iostream>

// Table dimensions.
constexpr int TABLE_WIDTH = 5;
constexpr int TABLE_HEIGHT = 5;

// Directions are encoded in an enum.
enum class Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST,
    INVALID
};

// The Robot class encapsulates the robot's position and behavior.
class Robot {
public:
    Robot();

    // Places the robot at (newX, newY) facing the given direction.
    // Returns true if placement is successful (i.e. valid position and direction).
    bool place(int newX, int newY, Direction newFacing);

    // Moves the robot one unit forward if the move is valid.
    void move();

    // Rotates the robot 90 degrees to the left.
    void turnLeft();

    // Rotates the robot 90 degrees to the right.
    void turnRight();

    // Reports the current position and facing of the robot.
    void report() const;

    // Returns whether the robot has been placed on the table.
    bool isPlaced() const;

private:
    int x;
    int y;
    Direction facing;
    bool placed;

    // Checks if the given position is within table boundaries.
    bool isValidPosition(int x, int y) const {
        return (x >= 0 && x < TABLE_WIDTH && y >= 0 && y < TABLE_HEIGHT);
    }
};

class RobotUtilityFunctions {
public:
	// Converts a string to uppercase.
	static std::string toUpper(const std::string& str);

	// Converts a string to a Direction enum.
	static Direction stringToDirection(const std::string& dirStr);

	// Converts a Direction enum to its string representation.
	static std::string directionToString(Direction dir);

	// Parses the PLACE command.
	// Expected format: "PLACE X,Y,F"
	// On success, returns true and fills in x, y, and facing.
	static bool parsePlaceCommand(const std::string& command, int& x, int& y, Direction& facing);
};