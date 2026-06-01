#pragma once
#include <future>
#include <type_traits>
#include <queue>

class ThreadPool
{
public:
	explicit ThreadPool(size_t numThreads = std::thread::hardware_concurrency());
	~ThreadPool();
	template<class F>
	auto Enqueue(F&& f) -> std::future<typename std::invoke_result<F>::type>
	{
		using return_type = typename std::invoke_result<F>::type;

		auto task = std::make_shared<std::packaged_task<return_type()>>(std::forward<F>(f));
		std::future<return_type> res = task->get_future();

		{
			std::unique_lock<std::mutex> lock(queueMutex);
			if (stop) throw std::runtime_error("Enqueue on stopped ThreadPool");
			tasks.emplace([task]() { (*task)(); });
		}
		condition.notify_one();
		return res;
	}
private:
	void WorkerLoop();
	bool stop;
	std::queue<std::function<void()>> tasks;
	std::mutex queueMutex;
	std::condition_variable condition;
	std::vector<std::thread> workers;

};

