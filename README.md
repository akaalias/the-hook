# The Hook

![alt tag](http://cdn1.tnwcdn.com/wp-content/blogs.dir/1/files/2014/01/the_hook.png)

## User-Driven Design Spec

Feature: Starting the game
     Scenario: Inactive State
     Given a player plugs in the device in power
     Then the reset led should be flashing

Feature: Activating the game
     Scenario: Activate Game
     Given the game is in inactive state
     Given a player clicks the activate button
     Then the active led should be on
     Then the reset led should be off

Feature: Playing the game
     Scenario: Play the game
     Given the game is in active state
     Given a player clicks the play button
     Then the active led should be off
     Then the game leds should flash
     Then the game led should land on either red or green
     Then the reset led should be on after 5 seconds
