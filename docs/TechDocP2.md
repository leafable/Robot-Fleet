# Technical Documentation 

**Architecture**: The system class carries out the main functionality of the program. There are certain classes meant to create objects like Obstacle, Robot, and Task. Then there are classes that manager these objects in ObstacleManager, RobotManager, and TaskManager. Warehouse creates and manages the arrays that compose the final printed warehouse.
Object relationships: 
- RobotManager is dependent on Robot to create the robot objects that it stores.
- ObstacleManager is dependent on Obstacle to create the obstacles and store them in the manager for the warehouse.
- TaskManager is dependent on Task to create the tasks and store them in the manager so it can be used by the robot and the warehouse.
- System is dependent on RobotManager, ObstacleManager, TaskManager, and Warehouse to initialize the game.

**Design Decisions**: We wanted to design the program in a way that maximized the potential to upscale or increase functionality at a later stage. This meant having a way to increase the warehouse size or the number of robots and tasks. There were some issues with trying to figure out the best way to combine the obstacles, robots, and tasks to create one cohesive Warehouse and the solution was to have three different arrays and combine them all when the warehouse needed to be printed to the console.

**Persistence Strategy**: There is no persistence of the data. When the program is closed the game is reset. If we wanted to implement a persistence strategy, we could store the information like the warehouse size, the seed used, the robot data, and the tasks. It would likely be easiest to store the information in three separate files: warehousedata.txt, robotdata.txt, and taskdata.txt. 


**Development approach**: We tried to keep the data class and the management class with the same people. This would allow each member to have an in-depth understanding of the their own class so they can collaborate with others to properly integrate their code to get one working program. 


**Composition**: Composition is used in the way that we classes for the data and for the managers. So each manager has a class of object that they create and  has a Student, eventSystem has an event, and RegistrationManager has a registration. This allows us to keep the data separate from the class that organizes and edits the data. It is 


**Technical challenges**:
One of the issues was placing the robots and making sure that there was a path from the orgin, to the pickup, and to the drop off location. Then there was an issue with getting the warehouse to match everything from the obstacles, robots, and tasks. The biggest issue is when the whole project comes together to get all the parts working cohesively and debugging errors that are found once the program is actually functional.


**Future Projects**: Things that we wanted to consider for future projects or updates included being able to scale up the program. This could mean increasing the warehouse size, number of robots, or the types of tasks that you can assign. We wanted to create options for new functionality like if there were enemies at higher levels of the game or maybe objects that you could collect that would give you a boost of speed, battery, or protection from enemy robots. For enemy robots, this would be based on the robot class that already exists. We would also think about implementing collisions to create a more realistic scenario. 