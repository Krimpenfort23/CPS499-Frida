# CPS499-Frida
Computer Security Course Final Project -- This topic involves using a javascript framework called Frida to do In-line Reference Monitoring on Lower-level code (at the Assembly and C level). The JS framework will be used in a python script.

# Project Proposal
## 0. CPS499-Frida | Evan Krimpenfort and Anna Durcey ##
## 1. Summary of Background ##
  This final project is a case study of an injection framework called Frida. Their website https://frida.re has explicit documentation on use cases and documents on their API's. Since one of the topics in this class was going over AOP inside of In-Line Refrence Monitors, we are going to be doing something similar to the Shopping Cart Problem like seen in Lab I and Assignment I. Since Frida is more focused on the the lower-level works, we will be writing a program in C that has  vulnerabilities similar to ShoppingCart.java. Then, like assignment I, we will fix the program with Frida. 
## 2. Project objectives ##
This program will be graded on a few things. 
- Was Frida easier to use than AspectJ? 
- Does it have the same capabilities as AspectJ? 
- Does it good job at being a reference monitor? 
And... 
- Are there things that Frida can do better?
## 3. Expected contributions and the relevance to the course topics ##
  Our contributions to the course will be in regards to be *IRM's, AOP, Data Races,* and *Protection in Software*. 
## 4. Your group plan: how your group members contribute to the project, the work plan. ##
Anna and Evan will work together through each of these sections. The work plan will be as such.
- **A.** Recreate a program like *ShoppingCart.java*.
  - **A.1** layout the data race vulnerability while creating the program.
- **B.** Create the python script that will run the Frida script.
- **C.** Design the Frida Script and see if it can completely fix the problems that ShoppingCart.java had (assignment I).
  - **C.1** If Frida *can't*, we will both go back and make any necessary changes to the code so that Frida **can** fix the code.
  - **C.2** If Frida *can*, then we will show how it completely fixed the program.
- **D.** Write the final report on our solution.
## 5. Timeline: Particular intermediate tasks and timeframe to complete the task. The time starts from proposal approval to the final report deadline. ##
- Task A should take 3 weeks.
- Task B should take 1 week.
- Task C should take 2-3 weeks (depending on Frida's capabilities).
- Task D should take 1 week.
