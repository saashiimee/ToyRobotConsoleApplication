// ToyRobotConsoleApplication.cpp : This file contains the 'main' function. Program execution begins and ends there.//

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include "./ToyRobotConsoleApplication.h"

Robot::Robot() : placed(false), x(0), y(0), facing(Direction::INVALID) {}

// Place robot on table if coordinates are valid.
bool Robot::place(int newX, int newY, Direction newFacing) {
	if (isValidPosition(newX, newY) && newFacing != Direction::INVALID) {
		x = newX;
		y = newY;
		facing = newFacing;
		placed = true;
		return true;
	}
	return false;
}

// Move robot one unit forward if valid.
void Robot::move() {
	if (!placed) return;
	int newX = x;
	int newY = y;
	switch (facing) {
	    case Direction::NORTH: newY++; break;
	    case Direction::EAST:  newX++; break;
	    case Direction::SOUTH: newY--; break;
	    case Direction::WEST:  newX--; break;
	    default: break;
	}
	if (isValidPosition(newX, newY)) {
		x = newX;
		y = newY;
	}
}

// Rotate robot 90 degrees to the left.
void Robot::turnLeft() {
	if (!placed) return;
	switch (facing) {
	    case Direction::NORTH: facing = Direction::WEST; break;
	    case Direction::WEST:  facing = Direction::SOUTH; break;
	    case Direction::SOUTH: facing = Direction::EAST; break;
	    case Direction::EAST:  facing = Direction::NORTH; break;
	    default: break;
	}
}

// Rotate robot 90 degrees to the right.
void Robot::turnRight() {
	if (!placed) return;
	switch (facing) {
	    case Direction::NORTH: facing = Direction::EAST; break;
	    case Direction::EAST:  facing = Direction::SOUTH; break;
	    case Direction::SOUTH: facing = Direction::WEST; break;
	    case Direction::WEST:  facing = Direction::NORTH; break;
	    default: break;
	}
}

// Report the current position and facing.
void Robot::report() const {
	if (placed) {
		std::cout << x << "," << y << "," << RobotUtilityFunctions::directionToString(facing) << std::endl;
	}
}

// Check if robot has been placed.
bool Robot::isPlaced() const {
	return placed;
}

// Helper function to convert string to uppercase.
std::string RobotUtilityFunctions::toUpper(const std::string& str) {
    std::string upper = str;
    std::transform(upper.begin(), upper.end(), upper.begin(),
        [](unsigned char c) { return std::toupper(c); });
    return upper;
}

// Convert string to Direction enum.
Direction RobotUtilityFunctions::stringToDirection(const std::string& dirStr) {
    std::string dir = RobotUtilityFunctions::toUpper(dirStr);
    if (dir == "NORTH") return Direction::NORTH;
    if (dir == "EAST")  return Direction::EAST;
    if (dir == "SOUTH") return Direction::SOUTH;
    if (dir == "WEST")  return Direction::WEST;
    return Direction::INVALID;
}

// Convert Direction enum to string.
std::string RobotUtilityFunctions::directionToString(Direction dir) {
    switch (dir) {
        case Direction::NORTH: return "NORTH";
        case Direction::EAST:  return "EAST";
        case Direction::SOUTH: return "SOUTH";
        case Direction::WEST:  return "WEST";
        default: return "INVALID";
    }
}

// Parses the PLACE command and returns whether parsing was successful.
bool RobotUtilityFunctions::parsePlaceCommand(const std::string& command, int& x, int& y, Direction& facing) {
    // Expected format: PLACE X,Y,F
    std::string cmd = command;
    // Remove the "PLACE " prefix.
    if (cmd.substr(0, 5) != "PLACE")
        return false;

    std::string args = cmd.substr(6); // skip "PLACE ", Only take the arguments
    std::replace(args.begin(), args.end(), ',', ' ');
    std::istringstream iss(args);

    if (!(iss >> x >> y))
        return false;

    std::string dirStr;

    if (!(iss >> dirStr))
        return false;

    facing = stringToDirection(dirStr);
    return true;
}

static inline bool is_input_file_exists(const std::string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

static void process_command_line(Robot& robot, const std::string& read_line) {
    std::string line = RobotUtilityFunctions::toUpper(read_line);
    if (line.find("PLACE") == 0) {
        int x, y;
        Direction d;
        if (RobotUtilityFunctions::parsePlaceCommand(line, x, y, d)) {
            if (!robot.place(x, y, d)) {
                // Invalid PLACE command (e.g., out-of-bound).
                std::cerr << "Invalid PLACE command. Position out of bounds or invalid direction." << std::endl;
            }
        }
        else {
            std::cerr << "Error parsing PLACE command." << std::endl;
        }
    }
    else if (line == "MOVE") {
        if (robot.isPlaced()) {
            robot.move();
        }
    }
    else if (line == "LEFT") {
        if (robot.isPlaced()) {
            robot.turnLeft();
        }
    }
    else if (line == "RIGHT") {
        if (robot.isPlaced()) {
            robot.turnRight();
        }
    }
    else if (line == "REPORT") {
        if (robot.isPlaced()) {
            robot.report();
        }
    }
	else if (line.empty()) {
		// Ignore empty lines.
    }
    else {
        std::cerr << "Unrecognized command: " << line << std::endl;
    }
    return;
}

int main() {
    Robot robot;
    std::string line;

    // Command loop: read from standard input.
    while (std::getline(std::cin, line)) {
		if (is_input_file_exists(line)) {
			std::ifstream input_file;
            input_file.open(line, std::ifstream::in);
            
            if (input_file.fail()) {
				std::cerr << "Error opening file: " << line << std::endl;
                input_file.close();
                break;
            }

            std::string line_from_file;
			while (std::getline(input_file, line_from_file)) {
                try
				{
					process_command_line(robot, line_from_file);
				}
				catch (const std::exception& e)
				{
					std::cerr << "Error processing command: " << e.what() << std::endl;
                    input_file.close();
                    break;
				}
			}
            input_file.close();
		}
        else {
            process_command_line(robot, line);
        }
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu