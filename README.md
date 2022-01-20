# Implementing a survival agent in a zombie game using GOAP

# What is GOAP?

Goal Oriented Action Planning is, as the name might suggest, a decision making system based on goals. It makes use of a graph + pathfinding system to find the best action to fulfill a set of goals.

# How does it work?

## WorldStates
First, we need to describe the world using "WorldStates". 
These are classes that have a predicate and an update function. They describe a single piece of information regarding the world (or agent).
For example, a state could be if the agent is currently inside a house or not (IsInHouseState).

Every frame the Update function gets called and this function needs to check if the state is true or false on this frame.

## Actions
Actions are classes that consists of these things:
### Preconditions
These are worldstates that must be fulfilled before the action can be taken.
For example, the PickupItem action cannot be done without fullfilling the Precondition IsNextToItem(true).
This list can be empty, which effectively means this action can always be done.

### Execute function
The code that gets executed when the action gets chosen.
For example, PickupItem action will grab the item and add it to the inventory.
This can be as complex or simple as need be.

### Effect
These are worldstates that are reasonable effects the action would have on the world.
Pickup item action would reasonably be able to fill up the inventory, triggering the IsInventoryFull(true) state.
However, these things are not linked in reality. If you execute the Pickup item action, it is not guaranteed that IsInventoryFull state becomes true. That is up to the worldstate update function to decide.

## Goals
Every frame, the agent will decide what action it wants to take. To do this it will look at its predefined set of goals. 
A goal is simply a worldstate that the agent wishes to achieve. This could be a state that is never achievable. (wanderlust is such an example)
A list of goals could look like this:
![Goals](https://user-images.githubusercontent.com/16197196/150377089-bc48e6f7-1c66-4c62-8480-96ef60d2d28b.png)

On the left you can see the current worldstate, and the list on the right is the predefined goals for the agent.
The agent will linearly choose a goal, so it will try to fulfill IsInPurgeZone(false) before it will try IsInventoryFull(true). Which makes sense, you're not going to look for a piece of food if you're about to be bombed.

In this diagram you can see that IsInPurgeZone is already false, so the goal has been achieved already. In that case, the agent just skips this goal alltogether and goes to the next one, which is IsInventoryFull(true)

This one is not fulfilled so we will attempt making a graph for it.

## Graphs
Everytime a goal is attempted, a graph is made. This graph will determine 2 things. Wether the goal is achievable right now and what action to take if it is.

### Building the graph
The graph consists of simple nodes and connections. It is made to satisfy a single goal.

#### Adding Nodes
It starts off by adding a "StartNode" and an "EndNode". 
Next, we add all the actions the agent has as nodes.
This leaves us with a graph full of nodes floating in space without any connections.

#### Adding Connections
We go through 3 steps to add connections.
First, we will loop over all actions and check if any of them have all of their preconditions met. If so, that action node gets connected to the startnode
Second, we will loop over all the actions and check if any of their effects are equal to a precondition of one of the other actions.
For example, MoveToPickup has the precondition of IsInHouse(true) and MoveIntoHouse has the effect of IsInHouse(true). So a connection is made from MoveIntoHouse to MoveToPickup

And lastly, we will loop over all the actions and check if any of their effects fulfills the goal we are making the graph for. If so, we add a connection between the action and the EndNode.
For example, the Pickup item action has the effect of IsInventoryFull(true) which is our current goal! So we connect Pickup item to the EndNode.


### Navigating the graph
This leaves us with something similar to this:
![1](https://user-images.githubusercontent.com/16197196/150381300-8956f6a2-0d58-4760-93cb-a886dffa4099.png)

Note that we currently do not have a path from the StartNode to the EndNode. This means that the goal is currently not possible, which would result in the goal being skipped.
However, to showcase how it works we will put the worldstate HouseInView on true and see what happens.
![2](https://user-images.githubusercontent.com/16197196/150381782-c8b4b60e-01f7-4847-87e6-52a4d63cf256.png)
We now have an uninterrupted path from the StartNode to the EndNode! This means our goal can be fullfilled and we can execute it! The agent will now get the first action of the path and execute it (for this frame). Remember that this will all be recalculated on the next frame.
On this frame, the agent will run the Execute function of the MoveIntoHouse action.

#### What happens if multiple paths are found?
So we have been executing the MoveIntoHouse function for a while now which presumably moves the agent into the house. Exactly this frame the worldstate ItemInView becomes true. This now means all preconditions for MoveToPickup have been fulfilled. This means the MoveToPickup is connected to the StartNode ontop of MoveIntoHouse being connected.
![3](https://user-images.githubusercontent.com/16197196/150383489-c6d3fd6e-bb54-4c43-8873-7f91870d4f47.png)
No worries however, as we will use pathfinding to find the shortest path in the graph.
We let our Dijkstra algorithm loose on the graph and task it to find the shortest path between StartNode and EndNode. This results in the MoveToPickup being the first action selected.

As we execute our MoveToPickup function we will eventually reach the item and fulfill the preconditions of the Pickup item action. Which will then be the shortest path.
![4](https://user-images.githubusercontent.com/16197196/150383866-4a686f53-1487-4bc0-83e7-df92de515885.png)

This results in the agent moving into a house, followed by moving towards an item to then eventually pick up an item.

# Strengths
- The flexability of coding in this system is very relieving. As before with FSM/BT structures it was a risk and a real headache to add an action or change one, the GOAP system allows you to simply add actions and worldstates on the fly.
- The code is split up into understandable pieces and is thus easier to read.
- All the actions are not interwoven, changing one action will not (or at least should not if you made it properly) affect the others.
- Very straightforward once the initial learning curve is overwon. 

# Weaknesses
- The extra calculations being done might be too much when dealing with a lot of agents.
- A bit of a learning curve before being able to work with it. You need to understand the structure before you are able to tinker with it.



# Regrets
As with any project, after finishing you can see the errors you made along the way and it's painfully obvious what you could have done better. This one is no different.

### Navigation and graph
I had originally planned to navigate the graph using A* but I ran into issues when implementing when I realised I needed a position for each node to be able to do this. I scrapped the idea of using A* and resorted to using Dijkstra instead as I thought I could not implement positions on this graph. After all, an action cannot have a position can it? After thinking about it more thoroughly I realised that I could have given the actions a 'virtual' position on the graph and used that for the A* pathfinding.

### Inventory management
I had issues with deleting an item without first adding it to my inventory so I resorted to a temporary solution.
The temporary solution involved adding any item I wanted to drop to the last slot of the inventory and then instantly discarding it.
As it turns out, in software development theres nothing more permanent than a temporary solution.
Fixing this would require me to rewrite 90% of the pickup item action. Which is perfectly do-able but alas, I am out of time.
