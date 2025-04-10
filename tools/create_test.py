import os

# FUNCTIONS

def generate_makefile( testName, testDir ):
    makefilePath = testDir + "/Makefile"
    try:
        with open( makefilePath, 'w' ) as makefile:
            makefile.write("################################################################\n")
            makefile.write("#\n")
            makefile.write(f"# {testName} unit tests (based on gcc)\n")
            makefile.write("#\n")
            makefile.write("################################################################\n\n")
            makefile.write("################################################################\n")
            makefile.write("# target\n")
            makefile.write("################################################################\n")
            makefile.write(f"TEST = {testName}\n")
            makefile.write(f"TARGET = {testName}.out\n")
            templatePath = os.getcwd() + "/tools/templates/TemplateMakefile"
            with open(templatePath, 'r') as template:
                for line in template:
                    makefile.write(line)
    
    except Exception as e:
        print(f"EXCEPTION: {e}")
        exit(1)

    print("Makefile generated.")

def generate_main( testname, testDir ):
    mainPath = testDir + "/test_blank.c"
    try:
        with open( mainPath, 'w' ) as file:
            templatePath = os.getcwd() + "/tools/templates/test_src_template.c"
            with open( templatePath, 'r' ) as template:
                for line in template:
                    file.write(line)
    
    except Exception as e:
        print(f"EXCEPTION: {e}")
        exit(1)

    print(f"test_{testname}.c generated.")

def generate_empty_cases( testname, testDir ):
    cases = testDir + "cases/"
    inputs = cases + "blank_inputs.txt"
    expected = cases + "blank_expected.txt"

    if not os.path.exists(os.path.dirname(cases)):
        try:
            os.makedirs(os.path.dirname(cases))
        except OSError as exc:
            print("A fatal error has occurred creating the directories. Exiting.")
            exit(1)

    try:
        with open( inputs, 'w' ) as file:
            file.write("1,\n2,\n3")
        with open( expected, 'w' ) as file:
            file.write("2,\n3,\n4")

    except Exception as e:
        print(f"EXCEPTION: {e}")
        exit(1)

    print(f"Blank cases generated.")

def generate_mocks( testname, testDir ):
    cases = testDir + "mock/"
    header = cases + "main.h"
    src = cases + "MOCK_hal.c"

    if not os.path.exists(os.path.dirname(cases)):
        try:
            os.makedirs(os.path.dirname(cases))
        except OSError as exc:
            print("A fatal error has occurred creating the directories. Exiting.")
            exit(1)

    try:
        with open( header, 'w' ) as file:
            templatePath = os.getcwd() + "/tools/templates/main.h"
            with open( templatePath, 'r' ) as template:
                for line in template:
                    file.write(line)
        with open( src, 'w' ) as file:
            templatePath = os.getcwd() + "/tools/templates/MOCK_hal.c"
            with open( templatePath, 'r' ) as template:
                for line in template:
                    file.write(line)

    except Exception as e:
        print(f"EXCEPTION: {e}")
        exit(1)

    print(f"Mock files generated.")

# MAIN

os.chdir("../")
testdir = os.getcwd()
print("Sun Devil Rocketry: Unit Test Generation Tool")
print("Created March 2025, Updated ------\n")

testPath = input("Enter the path to your test (e.g. app/canard/): ")
# Do some error handling
if not testPath[-1] == '/':
    print("The path must end with a slash!")
    exit(1)
testName = input("Enter the name of your test (e.g. flash): ")
# Do some error handling
if testName[-1] == '/':
    print("The test name cannot end with a slash!")
    exit(1)

newtest = testdir + '/' + testPath + testName + '/'

if not os.path.exists(os.path.dirname(newtest)):
    try:
        os.makedirs(os.path.dirname(newtest))
    except OSError as exc:
        print("A fatal error has occurred creating the directories. Exiting.")
        exit(1)

print("Directories created.")

generate_makefile( testName, newtest )
generate_main( testName, newtest )
generate_empty_cases( testName, newtest )
generate_mocks( testName, newtest )