import unittest

import os, sys

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from containers_py import stack


class TestStack(unittest.TestCase):
    def test_one(self):
        s = stack()

        self.assertEqual(s.count, 0)
        self.assertEqual(s.front, None)
        self.assertTrue(s.is_empty)

    def test_two(self):
        s = stack()

        self.assertEqual(s.count, 0)
        self.assertEqual(s.front, None)
        self.assertEqual(s.is_empty, True)

        for i in range(0, 1000000):
            s.push(i)
            self.assertEqual(s.count, i + 1)

        self.assertEqual(s.count, 1000000)
        self.assertFalse(s.is_empty)

        for i in range(999999, -1, -1):
            self.assertEqual(s.pop(), i)

        self.assertEqual(s.count, 0)
        self.assertTrue(s.is_empty)

    def test_three(self):
        s = stack()

        self.assertEqual(s.count, 0)
        self.assertEqual(s.front, None)
        self.assertEqual(s.is_empty, True)

        s.push(15)
        s.push(10)

        self.assertEqual(s.front, 10)

        s.pop()

        self.assertEqual(s.front, 15)

        s.pop()

        self.assertEqual(s.front, None)

        del s

        s2 = stack()

        for i in range(0, 1000000):
            s2.push(i)
            self.assertEqual(s2.front, i)
            self.assertEqual(s2.count, i + 1)

        self.assertEqual(s2.count, 1000000)
        self.assertFalse(s2.is_empty)


if __name__ == "__main__":
    unittest.main()
