# Toy Robot Console Application

## Overview
This project is created in accordance to the Toy Robot Code Challenge provided by SS&C Technologies Inc.
The PDF file containing the challenge is included in the repository.

Toy Robot Console Application is a console application that simulates a toy robot moving on a 5x5 square tabletop. 
The robot can be placed on the table, moved, rotated left or right, and report its current position and facing direction.

## Setup

### Prerequisites
*** This is a specific setup I am using for this development in Windows. You can use any other setup as well.
- Visual Studio 2022
- C++14 compatible compiler
- Command-line shell (e.g., Command Prompt, PowerShell)

### Building the Application
1. Open the solution file `ToyRobotConsoleApplication.sln` in Visual Studio.
2. Build the solution by selecting `Build > Build Solution` or pressing `Ctrl+Shift+B`.
- The executable file is already included with the github repository so you can skip building solution (step 2) if needed.

## Running the Application
1. Open a terminal or use the Visual Studio integrated terminal.
- If you are using Visual Studio, you can run the application by selecting `Debug > Start Without Debugging` or pressing `Ctrl+F5`.
- If you are using a terminal, navigate to the directory containing the compiled executable and run it by calling the ToyRobotConsoleApplication.exe file 
- You can also run the application by providing a file containing commands as input. See the [Usage](#usage) section for more information.
2. Navigate to the directory containing the compiled executable.
3. Run the application by executing the following command:

## Usage
The application reads commands from standard input. You can enter commands directly or provide a file containing commands. The available commands are:

- `PLACE X,Y,F`: Places the robot on the table at coordinates (X, Y) facing direction F (NORTH, EAST, SOUTH, or WEST).
- `MOVE`: Moves the robot one unit forward in the direction it is currently facing.
- `LEFT`: Rotates the robot 90 degrees to the left.
- `RIGHT`: Rotates the robot 90 degrees to the right.
- `REPORT`: Outputs the current position and facing direction of the robot.

### Example

### Running Commands by inputting in command line
Input:
- `PLACE 0,0,NORTH`
- `MOVE`
- `MOVE`
- `REPORT`

Output: `0,2,NORTH`

### Running Commands from a File
To run commands from a file, provide the file path as input:
1. Create a text file containing the commands you want to run. e.g., `commands.txt`. 
For your convenience, I have included a sample text file name "InputToyRobotCommands.txt" as an example.
2. Make sure you are in the directory containing the text file. Run the application by executing the following command:

```
$ ./ToyRobotConsoleApplication.exe (This will start the console app on an empty line)
$ ./InputToyRobotCommands.txt (Input the path of the file. This is the sample text file.)
```

- To exit the application, press `Ctrl+C`.

## Testing
The application includes unit tests using the Microsoft C++ Unit Test Framework. To run the tests:
1. Open the Test Explorer in Visual Studio (`Test > Test Explorer`).
2. Run all tests by clicking `Run All`.

- If errors occur during testing such as "linker error: unresolved external symbol", you can try the following:"
- Right-click on the Unit test project `ToyRobotUnitTest` in Solution Explorer and select `Properties`.
- Go to `Configuration Properties > Linker > Input`.
- Edit the `Additional Dependencies` field and add the following libraries: `$(SolutionDir)ToyRobotConsoleApplication\$(IntDir)*.obj`.
- Click `OK` to save the changes and rebuild the solution.
- *** If you are still facing issues, uncomment the commented `#include` line in the `ToyRobotUnitTest.cpp` file and try running again.
- *** If you are still facing issues, please let me know.

## License
This project is licensed under the MIT License.

## Future Work
- Cross-platform support for Linux and macOS.
- Modify the application to support a larger tabletop size.
- Implement additional commands or features, such as the ability to resize the tabletop or add obstacles.
- Improve the error handling and input validation.
- Implement a graphical user interface (GUI) for the application.
