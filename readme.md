# test
Submodule for unit testing in Sun Devil Rocketry firmware.

EXTERNAL DEPENDENCIES:
- GNU C Compiler (GCC). If you're used to our embedded environment, it's a different version of GCC for testing, you need to build for your own hardware.
- GNU GCov. This should be included in whatever gives you access to GCC. We use this to generate the coverage reports that tell developers how often a given statement or branch is hit. GDB is also highly recommended.
- GCovr (simply do pip install gcovr, then add it to your PATH. Alternatively, if you're on linux, you can use your preferred package manager).
- A bash terminal of some kind. Git Bash is recommended on Windows, and most Linux terminals should do. The makefiles use bash commands during execution to achieve the desired terminal and file output.

GETTING STARTED:
- Remember to correctly clone the submodule into your firmware repo. It should look similar to how lib and mod do.
- If this is your first time writing or modifying a unit test for SDR, take a look at some others to get an example!
- If you need to create a new test, ~~THE TOOL DOESN'T EXIST YET. Try copying an existing test or ask me (@etsells) for help.
- When modifying a test, pay close attention to the coverage report and the results. APPA and mod should be achieving full statement coverage (100% lines).
- Formal runs cannot be kicked off manually, but you can make sure it's working correctly by testing locally (make test).
