<h1> Nadia Nadeem - Zombie Mayhem </h1>
<h3> An endless 2D zombie shooting game. Kill all zombies in your way. </h3>

<p> Zombie mayhem is set in a dark dystopian world where the main character 'Madison' is fighting of waves of zombies, she is the only survivor left on Earth! Over time the number of zombies in each wave increase as well as the zombies health increase as the rounds progress. The game is from a top-down view of the world. </p>

<p> The user will be able to move Madision using the keyboard keys and the spacebar will be used to shoot the gun that Madison will be holding.</p>

<p> My unique mechanics will be that, Madison will be able to collect health power-ups as well as a bomb power-up that will destroy all zombies on the screen. The more zombies killed the higher the score attained, there will be a leaderboard as part of the game that will save the top 10 scores every achieved on that specific download of the game. I also aim to have the background and the aesthetic look of the zombies change once the player reaches specific round milestones.</p>

<a href="https://ansimuz.itch.io/warped-city"> Enemy and background assets linked here.</a>

![Image of Background Asset](https://img.itch.zone/aW1hZ2UvMTU2ODM5LzcyMDE0MS5wbmc=/347x500/HxAUgI.png)
<p>Figure 1: Background assets I am using for Zombie Mayhem. </p>

![Image of Player Asset](https://opengameart.org/sites/default/files/styles/medium/public/survivor-idle_shotgun_0.png)
<p>Figure 2: Player asset I will be using for Zombie Mayhem. </p>

![Image of Zombie Asset](https://img.itch.zone/aW1hZ2UvNzMzNDIwLzQwODQyNDkucG5n/347x500/c7Yu2Y.png)
<p>Figure 3: Zombie asset I plan on using for Zombie Mayhem. - No longer being used. </p>

<img src="profiler.PNG">
<p> Figure 4: Image of the Performance Profiler of the code. </p>


<h3> Dev Log </h3>
<p> 6/01/2021 - I decided to keep the robots as the enemies I like the look of them more. Carried out a performance test on the game. The game is more CPU intensive than GPU intensive, this is probably due to the pathfinding algorithm, as more enemies are instantiated into the world there are more spikes in cpu usage during runtime. </p>

<img src="performance.PNG">
<p> Figure 7: Latest performance test of the program. </p>

<p> 5/01/2021 - Background audio and sound effects have been implmente. The unique mechanics have now also been implmeneted so there is a health and a bomb pickup (these are explained in the description above. There is a memory leak in the program somewhere so I am currently trying to find the cause of that. I free all surfaces once created so I am unsure of where the memory leak is currently. Found the fix to the memory leak it was the text renderer showing the score.</p>

<img src="memoryleak.PNG">
<p> Figure 5: Screenshot of memory leak before fix implemented. </p>

<img src="memoryleakfix.PNG">
<p> Figure 6: Screenshot of memory leak after fix implemented. </p>

<p> 3/01/2021 - Pathfinding algorithm is done and works with the enemies movement. This is done via a Breadth First Search algorithm where a path is created this is done in the update function for each zombie to get the next move the zombies should go in. </p>

<p> 15/12/2020 - Collision detection between the player and the tilemap has been implemented. Next I would like to implement the health of the player becoming damaged when hit by an enemy. </p>

<p> 09/12/2020 - Player movement implemented along with the player's image being flipped and rotated according to the user's input. The direction the bullets are shot are also affect by the player's movement now. </p>

<p> 17/11/2020 - The enemies of the game have been created as well as a shooting mechanic with working collisions. In addition to this when a bullet collides with an enemy there is a UI overlay showing a score that it increase by 1 every time an enemy is shot. I have found the assets for the zombies but they are part of a sprite sheet, my next task is working on animations for the game, the zombies shall hopefully be implemented then. </p>

<p> 13/11/2020 - Tile map has been implemented as well as the character being created also. I have decided to make a top down game instead of a side-view game as it will be straightforward to implmenet shooting and pathfind mechanics. Assets for top-down games were slightly easier to find when looking for zombies assets that matched the aesthetic of Zombie Mayhem. </p>

<p> 28/10/2020 - Basic game loop created as well as the creation of a screen and the README document. Assets for the game have been found.</p>

