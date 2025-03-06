# test
Submodule for unit testing in Sun Devil Rocketry firmware.

DEPENDENCIES:
- [Unity from ThrowTheSwitch](https://github.com/ThrowTheSwitch/Unity/tree/master). This should be included in the root directory of the repository that this submodule appears in. If not, you need to add the submodule.
- GNU GCov. This should be included in whatever gives you access to GCC. GDB is also highly recommended.
- A bash terminal of some kind. Git Bash is recommended on Windows, and most Linux terminals should do. The makefiles use bash commands during execution to achieve the desired terminal and file output.

GETTING STARTED:
- Remember to correctly clone the submodule into your firmware repo. It should look similar to how lib and mod do.
- If this is your first time writing or modifying a unit test for SDR, take a look at some others to get an example!
- If you need to create a new test, you have two options. 1: Find a pre-existing unit test that is close to what you want to do, and manually copy it over. 2: Use the "create_test.py" script in tools.
- When modifying a test, pay close attention to the coverage report and the results. If your test requires full statement coverage, you should see something like "This test suite expects full coverage (100%)." in the results file. If it is under 100% and requires statement coverage, use the coverage report to find the conditions that aren't reached.
- Tests will throw an error if they fail, regardless of whether they are running correctly. The best way to determine if your issue is a bug or a test fail is to check the results report.
