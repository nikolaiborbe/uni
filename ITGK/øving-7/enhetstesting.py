#import functions you want to test
import unittest

class Tests(unittest.TestCase):

    def test_print_status(self):
        """
        Function should only work with the correct paramters.

        Parameters:
            - players: list[unknown]
            - curr_player: item in player
        """
        self.assertEqual(print_status([]), "Empty array")
        with self.assertRaises(TypeError):
            print_status(1)
        with self.assertRaises(TypeError):
            print_status(-1)
        with self.assertRaises(TypeError):
            print_status("a")
        with self.assertRaises(TypeError):
            print_status(True)

    def test_roll_dice(self):
        self.assertIsNone(roll_dice(-1))
        self.assertIsNone(roll_dice(1e250))
        self.assertIsNone(roll_dice("a"))
        self.assertIsNone(roll_dice(True))

    # I have no idea what this function does 
    def test_check_singles(self):
        self.assertIsNone(check_singles(-1))
        self.assertIsNone(check_singles(1e250))
        self.assertIsNone(check_singles("a"))
        self.assertIsNone(check_singles(True))



if __name__ == "__main__":
    unittest.main()
