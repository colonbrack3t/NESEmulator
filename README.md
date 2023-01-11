# NESEmulator
(Almost) Entire emulation of a NES game console. 

RAM AI

I decided to spend a day trying something I guessed wouldnt work, but wanted to test anyway.. 

The concept: Mario includes most of the game details in global variables (fixed addressees in RAM). Using matrix multiplication, a Weight matrix of 2048 x 8 could learn to convert the 2048B of RAM into 8b of controller inputs, and play the game. To "learn", I am using a genetic algorithm approach by running multiple individuals and mating the strongest to create the next generation.

The results: Mario has learned to move forward and jump, but not much more than that. Probably far too many attributes, and due to the relatively inefficient implementation of the NES I can only run ~10 NESs at the same time, limiting my population size considerably. Also, the levels are not loaded into RAM so avoiding holes/jumping over obstacles is unlikely to happen effectively. 
