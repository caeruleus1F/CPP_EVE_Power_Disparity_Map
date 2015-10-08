# CPP_EVE_Power_Disparity_Map

Dependencies: SFML 2.3.2 (2.3.1 also works)

Sample images:

http://imgur.com/ESz4rLc

http://imgur.com/YqkbCpC

EVE Online is a space-themed MMORPG. Within EVE, players can pilot over 200 ships and almost all of these ships can fit a number of combinations of hundreds of modules to choose from. Among these are weapons systems, each with their own unique characteristics.

The idea behind this program is that it's not enough to attack your opponent when you are at your strongest, or when your opponent is at his weakest, because at each of those points your ability to project power may be similar to your opponent's. This can lead to an outcome where you lose, or you win - but it may not be a decisive win. The best strategy is to engage your opponent when you are strongest relative to their weakest. This way when you are victorious, both your offensive and defensive capacity are higher than they otherwise would be, allowing you to engage your next opponent in better shape. 

Probably the most useful feature of the program is that it allows the user to visually determine the range and maximum transversal/velocity that allows them to defeat their opponent in a clear, decisive victory.

--- A LITTLE MORE IN DEPTH ---

What this program does is determine power disparity as a function of range and transversal/velocity, given two ships' weapons systems. Power disparity is defined as one ship's DPS at a given range and transversal/velocity minus the other ship's DPS. That disparity value is then stored onto a 2D grid, the location of which corresponding with the range and transversal/velocity. Each value on the grid is then converted to a color. The color and intensity is determined by whether the disparity is in your favor, or the target ships', and by how much. The greater the disparity in your favor, the darker green the color - the greater the disparity in the opponent ships', the darker red the color. Areas where the disparity is even or close to even, the closer the color is to white. White can also mean that neither ship can do any damage at that range.

Special zones are marked within the heatmap called "crushing victory zones." These zones signify combinations of range and velocity where one ship has a power disparity that is at or above 95% of its peak for that particular engagement. For "your" ship, these zones appear gold within green; for the opponent's ship, the zone appears dark green within red. Ideally you want to be within your gold zone.

X-axis on the heatmap signifies transversal velocity values from 0 to 1,000 meters per second when working with turret-based weapons systems, and velocity values from 0 to 1,000 when working with missile-based weapons systems. Y-axis value on the heatmap signify range values of 0 to 100,000 meters. Increment markings on the X-axis occur at intervals of 250 meters per second. Increment markings on the Y-axis occur at intervals of 20,000 meters.

While the program is active, pressing F1 generates a .jpg image with a name determined by your and the opposing ship, (eg. "Vexor vs. Autocannon Maller.jpg"). Pressing Esc closes the program.
