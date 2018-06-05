import unittest

import os
import sys
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from containers import queue, stack


class TestQueue(unittest.TestCase):
    """
    Test class.
    Testing a queue.
    """
    def test_one(self):
        """
        Testing the creation of a queue.
        """
        q = queue()

        self.assertEqual(q.count, 0)
        self.assertEqual(q.empty, 1)

        del q

    def test_two(self):
        """
        Testing the insertion in the queue.
        """
        q = queue()

        self.assertEqual(q.count, 0)
        self.assertEqual(q.empty, 1)

        for i in range(0, 100):
            check = q.enqueue(i)
            self.assertTrue(check)

        self.assertEqual(q.count, 100)
        self.assertEqual(q.empty, 0)

        del q

    def test_three(self):
        """
        Testing the removing in the queue.
        """
        q = queue()

        self.assertEqual(q.count, 0)
        self.assertEqual(q.empty, 1)

        for i in range(0, 1000):
            check = q.enqueue(i)
            self.assertTrue(check)

        self.assertEqual(q.count, 1000)
        self.assertEqual(q.empty, 0)

        for i in range(0, 1000):
            val = q.dequeue()
            self.assertEqual(val, i)

        self.assertEqual(q.count, 0)
        self.assertEqual(q.empty, 1)

        del q

    def test_four(self):
        """
        Testing the front element from the queue.
        """
        q = queue()

        self.assertEqual(q.count, 0)
        self.assertEqual(q.empty, 1)

        for i in range(0, 1000):
            check = q.enqueue(i)
            self.assertTrue(check)

        for i in range(0, 1000):
            self.assertEqual(i, q.front())
            q.dequeue()

        del q

    def test_five(self):
        """
        Testing the back element from the queue.
        """
        q = queue()

        self.assertEqual(q.count, 0)
        self.assertEqual(q.empty, 1)

        for i in range(0, 1000):
            check = q.enqueue(i)
            self.assertTrue(check)

        for i in range(0, 1000):
            self.assertEqual(999, q.back())
            q.dequeue()

        del q

    def test_six(self):
        """
        Testing the empty queue.
        """
        q = queue()

        self.assertEqual(q.count, 0)
        self.assertEqual(q.empty, 1)

        self.assertEqual(q.dequeue(), None)

        q.enqueue(15)

        self.assertEqual(q.dequeue(), 15)
        self.assertEqual(q.dequeue(), None)

        del q


class TestStack(unittest.TestCase):
    """
    Test class.
    Testing a stack.
    """
    def test_one(self):
        """
        Testing the creation of a stack.
        """
        s = stack()

        self.assertEqual(s.count, 0)
        self.assertEqual(s.empty, 1)

        del s

    def test_two(self):
        """
        Testing the insertion in the stack
        """
        s = stack()

        self.assertEqual(s.count, 0)
        self.assertEqual(s.empty, 1)

        for i in range(0, 1000):
            check = s.push(i)
            self.assertTrue(check)

        self.assertEqual(s.count, 1000)
        self.assertEqual(s.empty, 0)

        del s

    def test_three(self):
        """
        Testing the removing in the stack.
        """
        s = stack()

        self.assertEqual(s.count, 0)
        self.assertEqual(s.empty, 1)

        for i in range(0, 1000):
            check = s.push(i)
            self.assertTrue(check)

        self.assertEqual(s.count, 1000)
        self.assertEqual(s.empty, 0)

        for i in range(999, -1, -1):
            val = s.pop()
            self.assertEqual(val, i)

        self.assertEqual(s.count, 0)
        self.assertEqual(s.empty, 1)

        del s

    def test_four(self):
        """
        Testing the front element from the stack.
        """
        s = stack()

        self.assertEqual(s.count, 0)
        self.assertEqual(s.empty, 1)

        for i in range(0, 1000):
            check = s.push(i)
            self.assertTrue(check)

        for i in range(999, -1, -1):
            self.assertEqual(i, s.front())
            s.pop()

        del s

    def test_six(self):
        """
        Testing the empty stack.
        """
        s = stack()

        self.assertEqual(s.count, 0)
        self.assertEqual(s.empty, 1)

        self.assertEqual(s.pop(), None)

        s.push(15)

        self.assertEqual(s.pop(), 15)
        self.assertEqual(s.pop(), None)

        del s


if __name__ == "__main__":
    unittest.main()
