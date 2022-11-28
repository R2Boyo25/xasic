from os.path import exists, splitext, getmtime, basename
from os import system
import os

generator = {
    ".y": "bison",
    ".l": "flex"
}

header = {
    ".y": False,
    ".l": False
}


def genFile(filename: str) -> None:
    extension = splitext(filename)[1]
    cppfile = splitext(filename)[0] + ".cpp"
    hppfile = splitext(filename)[0] + ".hpp"
    modtime = getmtime(filename)

    if exists(cppfile):
        if getmtime(cppfile) >= modtime:
            return

    if exists(hppfile):
        if getmtime(hppfile) >= modtime:
            return
    
    command = " ".join([generator[extension], "--header="+hppfile, "-o"+cppfile, filename])
    if header[extension]:
        command = " ".join([generator[extension], "--header="+hppfile, filename])

    if not system(command):
        print("Successfully generated", cppfile)
    else:
        exit(1)
        

def cmake(directory: str, srcdir: str) -> None:
    cwd = os.getcwd()
    os.chdir(directory)

    if not os.system("cmake " + srcdir):
        print("Successfully run cmake for", directory)
    else:
        exit(1)
    
    os.chdir(cwd)

genFile("source/bison/parse.y")
genFile("source/flex/lex.l")