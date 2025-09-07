**Purpose:**

To find the most efficient methods of boarding order

**Plain English explanation:** 

I remember a video (https://youtu.be/oAHbLRjF0vo) from a long time ago that argued that the best way to load a plane was having everyone go in a pattern that had everyone be lined up by seat and row such that you would have each person be in an identical seat by offset by rows (a1 a3 a5 ...) and have them board back to front. I understood why this would obviously be more efficient than current methods, but the argument I haven't seen is why does the method insist on a spacing between rows (a1 a3 a5... vs a1 a2 a3...). I have thought about it forever and my best guess is that the spacing allows for line leaders to head to the back of the plane faster and allows for more time for all passengers to be moving. That being said, I want to prove this. So I will be making a quick sim to prove exactly that.

**Main Functionalities:**
1. simulate locomotion of passengers as they board a plane and find their seating *
2. allow for random noise in speed, baggage placement time and other found sources of noise as needed and increasing and decreasing this source of noise till we find their effect in the system
3. plot various values (like average time moving vs not moving and average velocity of passengers)
4. allow for different predetermined setup of individuals and create noise ontop of that to simulate passengers failing to organize correctly 


**Modules:**
1. Simulation init
   
    a. create list of passengers
   
        i.   given speed
        ii.  if carrying a baggage
        iii. speed of baggage placement
        iv.  seat placement - will be set to a dummy value first
        v.   person id - this will be a number
        vi.  stat tracking
                - 2 float arrays that are length of sim at max length, (shorten for memory needed)
                - track position at given times and if they moved at given times
   
    b. set up position map
   
        i. initially set this up as a fixed grid with positions based that are 1:1 with seat spacing, expand in future to smaller position lattice
    c. run down list of passengers
   
        i. based on the sim init parameters (ie what we are testing) run down the list and assign seat mappings as needed.
        ii. confirm list of people is correct length and as we go confirm that all seats desired are being filled
            - potential expansion later to add random missing seats
    d. init people lists with dummy people to be overwritten. list of people currently moving on the plane (because we will have far less people moving than positions on the plane at any given time it will make more sense to just run through who we know is on the plane)
   
        i. length of people list - could potentially cut this down for optimization
   
    e. init people list with dummy people to be overwritten. list of people who are sitting on the plane already (once they are sitting we don't want to worry about them)
   
3. Simulation Step

    a. If position 0 (with sufficient buffer later on) is empty assign top of people list not on plane (list mentioned in 1c and 1a) to position 0,0 (start of plane) and make first available pointer in moving persons list point to this person
   
    b. step people on moving persons lists
   
        i.   start with people at the front of the moving persons lists
        ii.  step is either movement at movement speed or placing bag
        iii. if movement would pass through someone else (insert colision logic, ie if v + p >= p of person ahead in list, stop)
        iv.  track in stat tracks 
    c. check if anyone is at their seat, if so move the first available pointer in seated persons list to the seated list, move their position in the moving persons lists to a dummy value.
   
        i. notably this doesnt check for if seat shuffling needs to occur, but for now I want to just compare my setup versus other setups, not such an issue as of right now.
    d. check if all pointers in the seated list are pointing to real value
   
        i. if so end sim

Notably this doesn't have the calculation tracking capability just yet. 
