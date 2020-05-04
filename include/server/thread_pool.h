#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include <mutex>
#include <queue>
#include <future>
#include <thread>
#include <functional>
#include <shared_mutex>
#include <condition_variable>

class ThreadPool {
public:
	ThreadPool(size_t maxcnt = 20);
	~ThreadPool();

	template <typename _Functor, typename... _ArgTypes>
	auto getTask(_Functor&& f, _ArgTypes&& ...args) -> std::future<typename std::result_of<_Functor(_ArgTypes...)>::type>;

private:
	std::queue < std::function<void()> > tasks;
	std::vector<std::thread> workers;
	std::mutex q_mtx;
	std::mutex stop_mtx;
	std::condition_variable condition;
	static void exec_task(void*);
	bool stop;
};

ThreadPool::ThreadPool(size_t maxcnt) {
	stop = false;
	for (size_t i = 0; i < maxcnt; ++i) {
		workers.emplace_back(std::thread(exec_task, (void*)this));
	}
}

ThreadPool::~ThreadPool() {
	{
		std::unique_lock<std::mutex> lock(stop_mtx);
		stop = true;
	}
	condition.notify_all();
	for (std::thread &th : workers) {
		th.join();
	}
}

void ThreadPool::exec_task(void* param) {
	ThreadPool* th = (ThreadPool*)param;
	std::function<void()> task;
	while (1) {
		{
			std::unique_lock<std::mutex> lock(th->q_mtx);
			th->condition.wait(lock, [th]() -> bool {
				std::unique_lock<std::mutex> lock(th->stop_mtx);
				return !(th->tasks.empty()) || th->stop;
			});  // block if process is not stopped AND task queue is empty (waiting for task)
			{
				std::unique_lock<std::mutex> lock(th->stop_mtx);
				if (th->stop && th->tasks.empty()) {
					break;  // exit loop if object is process is stopped AND task queue is empty 
				}
			}
			task = std::move(th->tasks.front());
			th->tasks.pop();
		}
		task();
	}
}

template <typename _Functor, typename... _ArgTypes>
auto ThreadPool::getTask(_Functor&& f, _ArgTypes&& ...args) -> std::future<typename std::result_of<_Functor(_ArgTypes...)>::type> {
	{
		std::unique_lock<std::mutex> lock(stop_mtx);
		if (stop) {
			std::runtime_error("still accepting tasks when process is stopped");
		}
	}
	using return_type = typename std::result_of<_Functor(_ArgTypes...)>::type;
	auto task = std::make_shared<std::packaged_task<return_type()>>(
		std::bind(std::forward<_Functor>(f), std::forward<_ArgTypes>(args) ...));
	std::future<return_type> res = task->get_future();
	{
		std::unique_lock<std::mutex> lock(q_mtx);
		tasks.emplace([task]() {(*task)(); });
	}
	condition.notify_one();
	return res;
}

#endif
