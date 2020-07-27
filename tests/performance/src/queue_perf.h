#ifndef QUEUE_PERF_H
#define QUEUE_PERF_H

#include "queue.h"
#include "performance.h"
#include <vector>

class QueuePerformance
    : public Perfomance
    , public perf_clock::Timer
    , public print::Output
{
  public:
    enum ACTION
    {
        INSERT,
        DELETE,
        CLEAR
    };

  private:
    std::vector<ACTION> actions{};
    int number{1000};

  public:
    QueuePerformance() = default;
    inline void set_number(int n) noexcept { number = n; }
    template<typename... Args>
    inline void add_actions(Args&&... acts) noexcept
    {
        (actions.push_back(std::forward<Args>(acts)), ...);
    }

    void run() final
    {
        reset_timer();
        for(auto act : actions) {
            switch(act) {
            case ACTION::INSERT:
                insert(number);
                break;
            case ACTION::DELETE:
                remove(number);
                break;
            case ACTION::CLEAR:
                clear(number);
                break;
            }
	}
    }

  private:
    void print_name() final { std::cout << "Queue:\n" << std::endl; }
    void print_ms() final { std::cout << cast_to<perf_clock::ms>() << " milliseconds.\n" << std::endl; }

  private:
    void insert(int num)
    {
        print_line_separator();
        print_name();
        std::cout << "Insert " << num << " values. Perfomance: ";
        Queue<int> queue;

	start_timer();
	for(int i = 0; i < num; i++) {
	    queue.enqueue(i);
	}
	finish_timer();

	if(queue.count() != static_cast<unsigned int>(num)) {
	    std::cout << "Error: Queue.count() != " << num << std::endl;
	    print_line_separator();
	    return;
	}

	print_ms();
	print_line_separator();
    }

    void remove(int num)
    {
        print_line_separator();
        print_name();
        std::cout << "Delete " << num << " values. Wait for inserting values ...";
        Queue<int> queue;

	for(int i = 0; i < num; i++) {
	    queue.enqueue(i);
	}

	if(queue.count() != static_cast<unsigned int>(num)) {
	    std::cout << "Error: Queue.count() != " << num << std::endl;
	    print_line_separator();
	    return;
	}
	std::cout << "done.\nPerfomance: ";

	start_timer();
	while(queue.count()) {
	    queue.dequeue();
	}
	finish_timer();
	print_ms();
	print_line_separator();
    }

    void clear(int num)
    {
        print_line_separator();
        print_name();
        std::cout << "Clear " << num << " values. Wait for inserting values ...";
        Queue<int> queue;

	for(int i = 0; i < num; i++) {
	    queue.enqueue(i);
	}

	if(queue.count() != static_cast<unsigned int>(num)) {
	    std::cout << "Error: Queue.count() != " << num << std::endl;
	    print_line_separator();
	    return;
	}
	std::cout << "done.\nPerfomance: ";

	start_timer();
	queue.clear();
	finish_timer();
	print_ms();
	print_line_separator();
    }
};

#endif /* QUEUE_PERF_H */
