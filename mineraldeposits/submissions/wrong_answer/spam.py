#! /usr/bin/env python3
# @EXPECTED_GRADES@ WA WA WA WA WA WA WA
import random

for _ in range(100000):
    print(
        random.choice(
            [
                "Egg and bacon",
                "Egg, sausage, and bacon",
                "Egg and Spam",
                "Egg, bacon, and Spam",
                "Egg, bacon, sausage, and Spam",
                "Spam, bacon, sausage, and Spam",
                "Spam, egg, Spam, Spam, bacon, and Spam",
                "Spam, Spam, Spam, egg, and Spam",
                "Spam, sausage, Spam, Spam, Spam, bacon, Spam, tomato, and Spam",
                "Spam, Spam, Spam, Spam, Spam, Spam, baked beans, Spam, Spam, Spam, and Spam",
                "Lobster Thermidor aux crevettes with a Mornay sauce, garnished with truffle pâté, brandy, and a fried egg on top, and Spam",
            ]
        )
    )
