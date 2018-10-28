#ifndef QUEUE_PERF_H
#define QUEUE_PERF_H

#include "queue.h"
#include "performance.h"
#include <cassert>

class QueuePerformance : public Performance {
public:
	explicit QueuePerformance()
	{}

public:
	enum ACTION {
		INSERTION,
		DELETION,
		CLEARING
	};
private:
	void insertions(const int& num)
	{
		Queue<int> queue;

		start_timer();
		for (int i = 0; i < num; i++) {
			queue.enqueue(i);
		}
		finish_timer();

		assert(queue.count() == static_cast<uint>(num));

		queue.~Queue();
	}

	void deletions(const int& num)
	{
		Queue<int> queue;

		for (int i = 0; i < num; i++) {
			queue.enqueue(i);
		}

		assert(queue.count() == static_cast<uint>(num));

		start_timer();
		while (queue.count()) {
			queue.dequeue();
		}
		finish_timer();

		queue.~Queue();
	}

	void clearing(const int& num)
	{
		Queue<int> queue;

		for (int i = 0; i < num; i++) {
			queue.enqueue(i);
		}

		assert(queue.count() == static_cast<uint>(num));

		start_timer();
		queue.clear();
		finish_timer();

		queue.~Queue();
	}

public:

	void run(const ACTION& action, const int& number)
	{
		reset();
		switch (action) {
		case ACTION::INSERTION:
			insertions(number);
			break;
		case ACTION::DELETION:
			deletions(number);
			break;
		case ACTION::CLEARING:
			clearing(number);
			break;
		}
	}
};


#endif /* QUEUE_PERF_H */

