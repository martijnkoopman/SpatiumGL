#include <gtest/gtest.h>

#include <spatiumgl/AsyncTask.hpp>

class CountTask : public spgl::AsyncTask<int>
{
public:
  CountTask()
  {}

  virtual ~CountTask() override = default;

private:
  void run() override
  {
    spgl::RunningGaurd gaurd(running());

    bool toCancel = false;
    for (int i = 0; i <= 100 && toCancel == false; i += 10) {

      // Wait 50 ms
      std::this_thread::sleep_for (std::chrono::milliseconds(50));

      // Notify about progress
      setProgressPercentage(i);

      if (i > 50) {
        setProgressMessage("Hello world");
      }

      toCancel = shouldCancel();
    }

    if (toCancel) {
      // Cancelled by user, empty result
      setResult(nullptr);
    } else {
      // Expose result
      setResult(std::make_shared<int>(888));
    }
  }
};

TEST(AsyncTask, finished)
{
  CountTask countTask;

  // Start task
  countTask.start();

  // Wait for 250 ms
  std::this_thread::sleep_for (std::chrono::milliseconds(250));

  // Get and check is running
  EXPECT_EQ(countTask.isRunning(), true);

  // Get and check progress
  const int progressPercentage = countTask.progress().percentage();
  EXPECT_TRUE(progressPercentage > 0);

  // Wait for 500 ms
  std::this_thread::sleep_for (std::chrono::milliseconds(300));

  // Get and check is running
  EXPECT_EQ(countTask.isRunning(), true);

  // Get and check progress
  EXPECT_TRUE(countTask.progress().percentage() > progressPercentage);

  EXPECT_EQ(countTask.progress().message(), "Hello world");

  // Wait for 500 ms
  std::this_thread::sleep_for (std::chrono::milliseconds(500));

  // Get and check is running
  EXPECT_EQ(countTask.isRunning(), false);

  // ALWAYS join!
  countTask.join();

  // Get and check result
  std::shared_ptr<int> result = countTask.result();
  EXPECT_EQ(*result, 888);
}

TEST(AsyncTask, cancel)
{
  CountTask countTask;

  // Start task
  countTask.start();

  // Wait for 500 ms
  std::this_thread::sleep_for(std::chrono::milliseconds(400));

  // Cancel task
  countTask.cancel();

  // Wait for 60 ms
  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  // Get and check is running
  EXPECT_EQ(countTask.isRunning(), false);

  // ALWAYS join!
  countTask.join();

  // Get and check result
  EXPECT_EQ(countTask.result(), nullptr);
}
