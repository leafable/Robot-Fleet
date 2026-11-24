# Project Overview: 
    What does the application do?
The application creates a warehouse with random obstacles and a set number of robots. The robots are randomly assigned with initial preassigned tasks. The user is responsible for creating new tasks and they win when it reaches the task y to z.

# Team Members: 
    Each team member and their primary responsibilities.
- Aleksandr: Obstacle, ObstacleManager, System, Warehouse, TaskManager
- Brandon: Robot, RobotManager, TechDoc.md
- Charlie: Task


# Features: 
    Opening the program creates the warehouse with a set seed and designated obstacles, there is a set number of robots that are randomly placed, and three initial tasks.
- Create and assign tasks
- Advance the robots by one move
- Take a user input for the warehouse size and seed
- Randomly create obstacles based on the seed
- Automatically create a path for robot to pick up and drop off location
- Print out the warehouse to show positions of robots, tasks, and obstacles


# Class Design: 
    Major classes and responsibilities.
- Obstacle: Creates obstacles and holds the position and size of the obstacle on the map. There are getter functions to access the data.
- ObstacleManager: Holds all the data for all of the obstacles on the map along with getter functions. There are functions to check objects for overlap and a vector holds all the obstacles.
- Robot: Creates an object Robot that holds data like the robot name, position, path, battery level, and status. Has getters and setters for this data as well.
- RobotManager: Has an array of Robot objects. Contains the functionality for moving the robots and searching for the shortest path. 
- System: This class handles the main functionality of the program. It creates all of the managers so they can create the objects for the warehouse. It takes user input to carry out commands like adding tasks or moving the robots. It also prints out the warehouse for the user to view.
- Task: Creates a task that holds the pick up and drop off coordinates. It has getter functions and a function to check that the robot is able to take on a new task.
- TaskManager: Holds all of the tasks in a queue that uses FIFO to assign tasks to robots.


# Building: 
There is a CMakeList that includes all of the source and header files to create and exe for the program. There are no additional files that are needed outside of the code files themselves.

# Running: 
Once the exe is created, click on the .exe file to begin the program.

# Data Storage: 
Data is not stored for this program. Once the program closes the data is erased and opening it again with reset everything.

# Known Limitations: 
    Important limitations or unfinished functionality.
- As of right now, the program operates in a 20x20 warehouse. There the functionality to increase the warehouse size, number of obstacles, and robots. There are limits imposed so the user does not add too many obstacles or robots. The upper limit for the warehouse is 35x35.
- There is currently no collisions except with the obstacles. So robots can occupy the same space as a task or another robot. We may want to change this in future versions of the game.