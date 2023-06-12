import sys
import toml
import os
import subprocess
import shlex

assert len(sys.argv) > 1

executable = sys.argv[1]
test_file = sys.argv[2]

with open(test_file, "r") as f:
    test = toml.load(f)

    xas_file = ".".join([*test_file.split(".")[:-1], "xas"])

    out = subprocess.check_output(
        [
            executable,
            xas_file,
            *shlex.split(test.get("args", "")),
        ]
    ).decode()

    if out != test.get("out", ""):
        print(
            f"{xas_file} failed test:\nExpected Output\n\"\"\"\n{test.get('out', '')}\n\"\"\"\nActual Output\n\"\"\"\n{out}\n\"\"\""
        )
        sys.exit(1)

    print(f"{xas_file} passed test")
