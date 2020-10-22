Test Reasoning

shuffleTileBagTest.cpp

    This test file checks if calling the shuffle method on the tilebag would properly mix up the tile placements. A tile bag object is instantiated, and is
    filled with tiles with an ascending pattern, repeated for 100 tiles. The tester is prompted to input a seed. The seed is then passed through the shuffle
    function and the tiles of the tile bag is printed out from beginning to end.

refillTileBagTest.cpp

    This test file tests the refillTileBag function of the box lid implementation. It instantiates a box lid and a tile bag, fills the box lid with tiles,
    then calls the refillTileBag function, passing the tile bag into it. It then outputs the contents of the box lid and tile bag to show that the function
    succeeded.

BSTSortingTest.cpp

    This test file tests to see if the bst is successful in sorting newly inserted nodes. A tile of each colour has been passed through the add function of 
    the BSTFactory object, which passes them through the insert function. The insertion of each colour was done not in order of their enum values. When the 
    BSTFactory object calls its print function, it prints out all node's tiles's colour from the bst, starting from the far left and ending on the far right side
    of the tree. The test succeeds if the tiles were printed in ascending order of their colour enum values.