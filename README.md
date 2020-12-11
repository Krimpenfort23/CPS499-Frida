# CPS499-Frida
Computer Security Course Final Project -- This topic involves using a JavaScript framework called Frida to do in-line reference monitoring on lower-level code (at the assembly and C level). The JS framework will be used in a Python script.

Trello board: https://trello.com/b/z9FXXdpJ/final-project

# Project Proposal
## 0. CPS499-Frida | Evan Krimpenfort and Anna Duricy ##
## 1. Summary of Background ##
  This final project is a case study of an injection framework called Frida. Their website https://frida.re has explicit documentation on use cases and documents on their APIs. We are going to be examining AOP inside of in-line reference monitors, similarly to the Shopping Cart Problem seen in Lab I and Assignment I. Since Frida is more focused on the the lower-level works, we will be writing a program in C that has vulnerabilities similar to ShoppingCart.java. Then, like Assignment I, we will fix the program with Frida. 
## 2. Project objectives ##
This program will be graded on a few things. 
- Was Frida easier to use than AspectJ? 
- Does it have the same capabilities as AspectJ? 
- Does it work well as a reference monitor? 
And... 
- Are there things that Frida can do better?
## 3. Expected contributions and the relevance to the course topics ##
  Our contributions to the course will be in regards to be *IRMs, AOP, Data Races,* and *Protection in Software*. 
## 4. Your group plan: how your group members contribute to the project, the work plan. ##
Anna and Evan will work together through each of these sections. The work plan will be as such:
- **A.** Recreate a program like *ShoppingCart.java*.
  - **A.1** Lay out the data race vulnerability while creating the program.
- **B.** Create the Python script that will run the Frida script.
- **C.** Design the Frida script and see if it can completely fix the problems that ShoppingCart.java had (Assignment I).
  - **C.1** If Frida *can't*, we will both go back and make any necessary changes to the code so that Frida **can** fix the code.
  - **C.2** If Frida *can*, then we will show how it completely fixed the program.
- **D.** Write the final report on our solution.
## 5. Timeline: Particular intermediate tasks and timeframe to complete the task. The time starts from proposal approval to the final report deadline. ##
- Task A should take 3 weeks.
- Task B should take 1 week.
- Task C should take 2-3 weeks (depending on Frida's capabilities).
- Task D should take 1 week.

## 6. A How To
**In order to properly run this code, you should have an environment that can support compilation of python3.9, gcc, and frida-tools. I had no problems doing this on a Mac machine. Linux should probably do fine too.**
1. The first thing to do is download this repository by doing a `git clone`.
2. In order to properly run this code, you should first download frida-tools. You can do this by doing `pip3 install frida-tools`. This will allow you to properly run the python script with the `import frida` line and all of the JS API used in the script. If you happen to find any issues regarding this, you can go to https://frida.re/docs/installation/.
3. Once that's finished, you should open up three terminals. 
  - Your first terminal should run the ShoppingCart executable. You can do this by running `./ShoppingCart <port#>` and the *port #* can be any short. We chose 8888. 
  - The next terminal will run the python script containing Frida. You can do this by running `python3 ShoppingCart.py` and you'll know it works when you see the next line that looks like `Preping for Attachment...`
  - And finally, the last terminal will TCP connect into the Server file that is ShoppingCart. We did this by doing `telnet localhost <port#>`. Make sure that the *port #* that you chose in the first terminal is the same as this one. Again, we chose 8888.
4. Once all of that is complete, you can follow the directions on the client terminal to purchase your goodies from the ShoppingCart. You'll notice that if you buy things correctly with sufficent funds, the frida script shouldn't do much but log what is all being hooked. However, if you try and buy something with insufficent funds, you'll see that the .py script does not allow this and you will have failed to purchase the item. 
5. And lastly, if you want to set a specific value for your balance, you can edit the `wallet.txt` file. The first line will always be the balance used in the ShoppingCart executable.
