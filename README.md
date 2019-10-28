<h1>Overview</h1>
The objective of this project is to explore the effectiveness of using genetic algorithms to train neural networks without the need for large data sets. The simulation consists of a 2D board populated with creature entities that are each controlled by their own neural network and food entities that give off a scent that the creatures detect. I use a genetic algorithm and a variety of training scenarios to train the neural networks to seek out food based on the scents that they take as input. The simulation is designed to ease the creation of custom scenarios. This, combined with altering parameters of the ranking system that the genetic algorithm uses, allows for targeting different behaviors for the creatures. For example, they can be trained to avoid walls, reduce energy expenditure, attempt to beat other creatures to food, etc. 

<h1>Demonstration</h1>
<figure>
  <img src="https://github.com/herstky/Replicator/raw/master/untrained_neural_network_sim.gif" height="350" width="300">
  <figcaption>Untrained neural networks in a simulation scenario that randomly spawns food and creatures</figcaption>
</figure>
<br>
<br>
<br>
<figure>
  <img src="https://github.com/herstky/Replicator/raw/master/trained_neural_network_sim.gif" height="350" width="300">
  <figcaption>Trained neural networks in the simulation scenario</figcaption>
</figure>
<br>
<br>
<br>
The training scenario shown below spawns creatures in a circle around a food entity in the center. Creatures are spawned in groups that are evenly distributed around the circle. Every member of a group receives an exact copy of the same neural network and creatures are colored based on their group. The algorithm ranks each neural network based on how its group performed and crosses over the weights of the overall top performing neural network with the top performer of the current generation. The newly generated neural network is then mutated randomly for each group in the next generation. 
<br>
<br>
<br>
<figure>
  <img src="https://github.com/herstky/Replicator/raw/master/untrained_neural_network.gif" height="350" width="300">
  <figcaption>The first generation of untrained networks</figcaption>
</figure>
<br>
<br>
<br>
<figure>
  <img src="https://github.com/herstky/Replicator/raw/master/animation_toggle.gif" height="350" width="300">
  <figcaption>The animation can be turned off to speed up the training process</figcaption>
</figure>
<br>
<br>
<br>
<figure>
  <img src="https://github.com/herstky/Replicator/raw/master/trained_neural_network.gif" height="350" width="300">
  <figcaption>The neural networks after 1000 generations of training</figcaption>
</figure>
