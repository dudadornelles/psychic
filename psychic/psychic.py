#!/usr/bin/python

import re
import string
import tempfile
import os
from glob import glob

def write_c_file(*args, **kwargs):
    template = string.Template(
"""
#include "ectest.c"
$includes
int main(int argc, char* argv[]) {
$testcases
}
""")
    includes = "\n".join(["#include \"%s\"" % os.path.abspath(include) for include in kwargs['includes']])
    testcases = ";\n".join(kwargs['testcases']) + ";"
    tmpdir = kwargs['tmpdir']
    content = template.substitute(includes=includes, testcases=testcases)

    testfile_path = os.path.join(tmpdir, "testfile.c")
    testfile = open(testfile_path, "w")
    testfile.write(content)
    testfile.close()

    return testfile_path


def compile_and_run(c_file_path, tmpdir):
    testfile_object_path = os.path.join(tmpdir, "testfile.o")
    os.system("gcc %s -o %s -I." % (c_file_path, testfile_object_path))
    os.system(testfile_object_path)
    

def extract_testcases(test_filename):
    stream = open(test_filename).read()
    pattern = "void (test_.*?\(\)) {"
    return re.findall(pattern, stream)


def main():
    tmpdir = tempfile.mkdtemp()
    testfiles = glob("test_*.c")
    testcases = []

    for test_file in testfiles:
        testcases.extend(extract_testcases(test_file))
        
    c_file = write_c_file(includes=testfiles, testcases=testcases, tmpdir=tmpdir)
    compile_and_run(c_file, tmpdir)


if __name__ == "__main__": 
    main()
