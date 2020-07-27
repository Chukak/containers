import unittest

import os, sys

sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from containers_py import queue


class TestQueue(unittest.TestCase):
    def test_one(self):
        q = queue()

        self.assertEqual(q.count, 0)
        self.assertEqual(q.front, None)
        self.assertEqual(q.back, None)
        self.assertTrue(q.is_empty)

    def test_two(self):
        q = queue()

        self.assertEqual(q.count, 0)
        self.assertEqual(q.front, None)
        self.assertEqual(q.back, None)
        self.assertTrue(q.is_empty)

        for i in range(0, 1000000):
            q.enqueue(i)
            self.assertEqual(q.count, i + 1)

        self.assertEqual(q.count, 1000000)
        self.assertEqual(q.front, 0)
        self.assertEqual(q.back, 999999)
        self.assertFalse(q.is_empty)

        for i in range(0, 1000000):
            self.assertEqual(q.dequeue(), i)

        self.assertEqual(q.count, 0)
        self.assertEqual(q.front, None)
        self.assertEqual(q.back, None)
        self.assertTrue(q.is_empty)

    def test_three(self):
        q = queue()

        self.assertEqual(q.count, 0)
        self.assertEqual(q.front, None)
        self.assertEqual(q.back, None)
        self.assertTrue(q.is_empty)

        for i in range(0, 1000000):
            q.enqueue(i)
            self.assertEqual(q.count, i + 1)
            self.assertEqual(q.front, 0)
            self.assertEqual(q.back, i)

        for i in range(0, 999999):
            self.assertEqual(q.front, i)
            self.assertEqual(q.dequeue(), i)
            self.assertEqual(q.back, 999999)

        self.assertEqual(q.front, 999999)
        self.assertEqual(q.dequeue(), 999999)
        self.assertEqual(q.front, None)
        self.assertEqual(q.back, None)

        self.assertEqual(q.count, 0)
        self.assertEqual(q.front, None)
        self.assertEqual(q.back, None)
        self.assertTrue(q.is_empty)

    def test_four(self):
        q = queue()

        self.assertEqual(q.count, 0)
        self.assertEqual(q.front, None)
        self.assertEqual(q.back, None)
        self.assertTrue(q.is_empty)

        for i in range(0, 1000000):
            q.enqueue(i)
            self.assertEqual(q.count, i + 1)

        self.assertEqual(q.count, 1000000)
        self.assertEqual(q.front, 0)
        self.assertEqual(q.back, 999999)
        self.assertFalse(q.is_empty)

        q.clear()

        self.assertEqual(q.count, 0)
        self.assertEqual(q.front, None)
        self.assertEqual(q.back, None)
        self.assertTrue(q.is_empty)


if __name__ == "__main__":
    unittest.main()
