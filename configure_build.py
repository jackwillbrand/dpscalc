import os
import subprocess
import argparse

# Add command-line arguments
parser = argparse.ArgumentParser()
group = parser.add_mutually_exclusive_group(required=False)
group.add_argument("-silent", action="store_true", help="Discard output")
group.add_argument("-log", type=str, default="configure_build.log", nargs='?', help="Log output to file, default to 'configure_build.log'")
parser.add_argument("-clean", action="store_true", help="Clean build directory without building")
args = parser.parse_args()

# Reset and navigate to build directory
if os.path.exists("build"):
    os.rmdir("build")
os.mkdir("build")
os.chdir("build")

# Check cmd-line arguments for output direction
if args.silent:
    stdout = subprocess.DEVNULL
    stderr = subprocess.DEVNULL
elif args.log:
    stdout = open(args.log, 'w')
    stderr = subprocess.STDOUT
else:
    stdout = None
    stderr = None

# Generate and execute makefiles
subprocess.run(["cmake", "-G", "MinGW Makefiles", ".."], stdout=stdout, stderr=stderr)
subprocess.run(["mingw32-make", "all"], stdout=stdout, stderr=stderr)

if args.log:
    stdout.close()