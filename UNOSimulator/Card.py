
"""
        Card.py

    This file represents a singular card in an UNO deck. Each instantiation of this object
    will consist of a color and value.

    Allowable colors are RED, BLUE, GREEN, YELLOW, WILD, and WILD4+

        - the first four colors are self-explanatory
        - WILD pertains to a standard wild card
        - WILD4+ pertains to a draw 4 wild card
"""

    ########################
    # Class Implementation #
    ########################

class Card():

    # Constructor for this class; initializes the color and value of this card
    # color = the color of this card
    # value = the value of this card
        # May be None in the case of WILD or WILD4+
        def __init__(self, color, value):
            self.color = color
            self.value = value