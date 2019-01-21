# Minesweeper
Minesweeper Game written in C++

# How to Play
You are presented with a board of squares. Some squares contain mines (bombs), others don't. 
Players are prompted for a row and a column to reveal. If the tile that the player chooses is a bomb, they lose. If they manage to reveal all the squares that aren't bombs, they win.

# Rules
* If the tile is not a bomb but is adjacent to at least one, then the tile will show the number of bombs that the tile is adjacent to.
* If the tile is not a bomb and is NOT adjacent to at least one:
     * Not only does the tile become visible, but all 8 surrounding tiles are made visible following the previously mentioned rule.  
* As each tile becomes exposed, it is considered whether if it is adjacent to a bomb or not.
* If it is then the count of bombs it is adjacent to is shown.
* If it is not adjacent to one, it is made visible and the game continues in the same way. This can result in a large number of tiles to become visible with a single tile selection!

**Example:**



