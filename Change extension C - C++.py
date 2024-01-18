import os
import glob

def search_files_by_extension (path, extension): #Searches all files contained in "path" and its subfolders with file extension "extension"
    t = os.listdir(path)
    i = 0
    while (i < len(t)):
        t[i] = path + os.sep + t[i]
        i = i + 1
    files = []
    dirs = []
    while (True):
        if (len(t) > 0) :
            if (os.path.isdir(t[0])):
                dirs = dirs + [t[0]]
                t = t[1:]
                continue
            elif (os.path.isfile(t[0])):
                files = files + [t[0]]
                t = t[1:]
                continue
            else :
                return [[], [], 1]
        if (len(t) != 0):
            return [[], [], 2]
        if (len(dirs) == 0):
            break;
        i = 0
        while (i < len(dirs)-1):
            t = t + [dirs[i]]
            i = i + 1
        t2 = os.listdir(dirs[i])
        i2 = 0
        while (i2 < len(t2)):
            t = t + [dirs[i] + os.sep + t2[i2]]
            i2 = i2 + 1
        dirs = []
    i = 0
    files2 = []
    while (i < len(files)):
        t = files[i]
        i2 = len(t) - 1
        while (i2 >= 0):
            if (t[i2] == '.' or t[i2] == os.sep):
                break
            i2 = i2 - 1
        if (i2 != -1):
            if (t[i2] != os.sep):
                if (t[i2+1:] == extension):
                    files2 = files2 + [t]
        i = i + 1
    return [files2, files, 0]

def change_extension (files, extension):
    i = 0
    files2 = []
    while (i < len(files)):
        t = files[i]
        i2 = len(t) - 1
        while (i2 >= 0):
            if (t[i2] == '.'):
                break
            i2 = i2 - 1
        if (i2 == -1):
            return [[], 1]
        os.rename(t, t[:i2+1]+extension)
        files2 = files2 + [t[:i2+1]+extension]
        i = i + 1
    return [files2, 0]

        

folder = os.getcwd()
error = 0
error2 = 0
extension_to_modify = ""
desired_extension = ""
print("This script searches for all .cpp (or .c) extension files contained in the " + folder + " folder and its subfolders and changes their extension to .c (or .cpp).")
print("What do you want to do? Enter 1 to change extensions from .cpp to .c or 2 to change from .c to .cpp.")
choice = input()
if (choice == "1"):
    extension_to_modify = "cpp"
    desired_extension = "c"
elif (choice == "2"):
    extension_to_modify = "c"
    desired_extension = "cpp"
if (choice == "1" or choice == "2"):
    [files, all, error] = search_files_by_extension(folder, extension_to_modify)
    if (error == 0):
        [files2, error2] = change_extension(files, desired_extension)
        if (error2 == 0):
            if (len(files) == 0):
                print("No files were renamed.")
            else:
                i = 0
                while (i < len(files)):
                    print("File " + files[i] + " renamed to " + files2[i] + ".")
                    i = i + 1
    if (error != 0):
        print("search_files_by_extension returned error " + str(error))
    elif (error2 != 0):
        print("change_extension returned error " + str(error2))
else:
    print("Choice not allowed.")
print("Press a key to exit.")
input()
