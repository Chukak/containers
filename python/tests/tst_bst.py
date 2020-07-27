import unittest

import os, sys

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from containers_py import bst
import random

class TestBST(unittest.TestCase):
    def test_one(self):
        tree = bst()

        self.assertEqual(tree.count, 0)
        self.assertTrue(tree.is_empty)
        try:
            self.assertEqual(tree.min(), None)
        except Exception as e:
            self.assertIsInstance(e, RuntimeError)
        try:
            self.assertEqual(tree.max(), None)
        except Exception as e:
            self.assertIsInstance(e, RuntimeError)
        try:
            self.assertEqual(tree.root, None)
        except Exception as e:
            self.assertIsInstance(e, RuntimeError)

    def test_two(self):
        tree = bst()

        self.assertEqual(tree.count, 0)
        self.assertTrue(tree.is_empty)

        cnt = 0
        all_elements = []
        for i in random.sample(range(0, 100000000), 100000):
            cnt += 1
            all_elements.append(i)
            tree.insert(i)
            self.assertEqual(tree.count, cnt)

        self.assertEqual(tree.count, 100000)
        self.assertFalse(tree.is_empty)

        for f in all_elements:
            self.assertTrue(tree.find(f))

        for f in random.sample(range(0, -100000, -1), 1000):
            self.assertFalse(tree.find(f))

        for e in all_elements:
            cnt -= 1
            tree.remove(e)
            self.assertEqual(tree.count, cnt)

        self.assertEqual(tree.count, 0)
        self.assertTrue(tree.is_empty)

    def test_three(self):
        tree = bst()

        self.assertEqual(tree.count, 0)
        self.assertTrue(tree.is_empty)

        elements = [
            1, 67, -34, 1290, -934, 0, 12, 34,
            24, -56, -123, 678, 23
        ]

        for e in elements:
            tree.insert(e)

        self.assertEqual(tree.count, 13)
        self.assertFalse(tree.is_empty)
        self.assertEqual(tree.min(), -934)
        self.assertEqual(tree.max(), 1290)
        self.assertEqual(tree.root, 1)

        tree.remove(1)

        self.assertEqual(tree.count, 12)
        self.assertFalse(tree.is_empty)
        self.assertEqual(tree.min(), -934)
        self.assertEqual(tree.max(), 1290)
        self.assertEqual(tree.root, 0)

        tree.remove(-934)
        tree.remove(1290)
        tree.remove(0)

        self.assertEqual(tree.count, 9)
        self.assertFalse(tree.is_empty)
        self.assertEqual(tree.min(), -123)
        self.assertEqual(tree.max(), 678)
        self.assertEqual(tree.root, -34)


if __name__ == "__main__":
    unittest.main()
