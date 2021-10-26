import os
import sys
import subprocess
from typing import List, Dict

class CppFile:
    def __changed__(self) -> bool:
        return False

class Header(CppFile):
    def __init__(self, location : str, file_name : str) -> None:
        self.path = location + "/" + file_name
        self.location : str = location
        self.file_name : str = file_name 

        self.__checked_change__ : bool = False

        
    def changed(self) -> bool:
        if self.__checked_change__:
            return self.__has_changed__
        self.__checked_change__ = True

        modified = os.path.getmtime(self.path)
        if self.file_name in previous_modifieds:
            previous_modified = previous_modifieds[self.file_name]
            previous_modifieds[self.file_name] = modified
        
            if modified > previous_modified:
                self.__has_changed__ = True
                return True

        previous_modifieds[self.file_name] = modified

        with open(self.path, "r") as file:
            for line in file:
                if line.startswith("#include"):
                    if line.count('"') > 1:
                        dependency = line.split('"')[1]
                        if dependency in hdr_files and hdr_files[dependency].changed():
                            self.__has_changed__ = True
                            return True
        
        self.__has_changed__ = False
        return False
                    

class Source(CppFile):
    def __init__(self, location : str, file_name : str) -> None:
        self.path = location + "/" + file_name
        self.location : str = location
        self.file_name : str = file_name
        self.compiled = tmp_folder + "/" + self.file_name[:-4] + ".o"
    
        self.__checked_change__ : bool = False


    def changed(self) -> bool:
        if self.__checked_change__:
            return self.__has_changed__
        self.__checked_change__ = True

        if not os.path.exists(self.compiled):
            self.__has_changed__ : bool = True
            return True
        
    
        modified = os.path.getmtime(self.path)
        previous_modified = os.path.getmtime(self.compiled)
        self.__has_changed__ : bool = modified > previous_modified

        if self.__has_changed__:
            return True


        with open(self.path, "r") as file:
            for line in file:
                if line.startswith("#include"):
                    if line.count('"') > 1:
                        dependency = line.split('"')[1]
                        if dependency in hdr_files and hdr_files[dependency].changed():
                            self.__has_changed__ : bool = True
                            return True
        
        return False


# Get arguments
src_folder : str = sys.argv[1]
tmp_folder : str = sys.argv[2]
output_file : str = sys.argv[3]
compile_type : str = sys.argv[4]
args : List[str] = sys.argv[5:]

# Read the dates header_dates
previous_modifieds : Dict[str, float] = {}
if os.path.exists(tmp_folder + "/last_header_dates.txt"):
    with open(tmp_folder + "/last_header_dates.txt", "r") as header_dates:
        for line in header_dates:
            try:
                file_name, previous_modify = line.split(" ")
                previous_modifieds[file_name] = float(previous_modify)

            except ValueError:
                print("Error somewhere in last_header_dates.txt >> " + line)
else:
    print("header_dates doesn't exist, creating one.")
    open(tmp_folder + "/last_header_dates.txt", "x").close()

hdr_files : Dict[str, Header] = {}
src_files : Dict[str, Source] = {}

# Get all .cpp / .h and their last modified
include_folders = set()
for path, sub_folders, sub_files in os.walk(src_folder):

    has_hdr : bool = False

    for file in sub_files:
        if file.endswith(".cpp"):
            src_files[file] = Source(path, file)

        elif file.endswith(".h"):
            hdr_files[file] = Header(path, file)
            has_hdr = True

    # Add folder for Including when compiling if it contains a header
    if has_hdr:
        include_folders.add("-I" + path)

# Prepare command
gpp_command = ["/usr/bin/g++"] + args
gpp_command.extend(include_folders)

# Seperately compile all source files which were changed
compilers : List[subprocess.Popen] = []
for src_file in src_files.values():
    if src_file.changed():
        print("Compiling", src_file.file_name)
        compilers.append( subprocess.Popen(gpp_command + ["-c", src_file.path, "-o", src_file.compiled]) )


# Update dates in header_dates
with open(tmp_folder + "/last_header_dates.txt", "w") as header_dates:
    for modified, age in previous_modifieds.items():
        header_dates.write(modified + " " + str(age) + "\n")


# If any file was changed or there is no output file, link everything
if compilers or not os.path.exists(output_file):
    
    # Check if any of the seperate compilers Errored
    exit_error = 0
    for compiler in compilers:
        compiler.wait()
        
        if compiler.returncode:
            exit_error = compiler.returncode
    
    if exit_error:
        sys.exit(exit_error)

    # Link all .o files
    print("Linking")
    linker = subprocess.Popen(["/usr/bin/g++"] + 
                              [source.compiled for source in src_files.values()] + 
                              args)
    linker.wait()

    if linker.returncode:
        sys.exit(1)
