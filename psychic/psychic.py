#!/usr/bin/python

import re
import string
import tempfile
import subprocess
import os
from jinja2 import Template

from os import path
from glob import glob

def _here():
    return path.abspath(path.dirname(__file__))

def write_c_file(*args, **kwargs):
    template = Template(open("%s/testfile.c.jinja" % _here()).read())
    includes = map(path.abspath, kwargs['includes'])
    testcases = kwargs['testcases']
    tmpdir = kwargs['tmpdir']
    content = template.render(includes=includes, testcases=testcases, here=_here())

    testfile_path = path.join(tmpdir, "testfile.c")
    testfile = open(testfile_path, "w")
    testfile.write(content)
    testfile.close()

    return testfile_path


def compile_and_run(c_file_path, tmpdir):
    testfile_object_path = path.join(tmpdir, "testfile.o")
    psychic_c_dep = path.join(_here(), "csource", "psychic.c")

    # TODO: add user lib to compile path
    subprocess.call(["gcc", psychic_c_dep, c_file_path, "-o", testfile_object_path, "-I."])
    subprocess.call(testfile_object_path)
    

def extract_testcases(test_filename):
    # TODO: use a code analyzer to do this
    stream = open(test_filename).read()
    pattern = "void (test_.*?\(\)) {"
    return re.findall(pattern, stream)


def all_testfiles_r():
    all_files = []
    for path, subdirs, files in os.walk("."):
        for name in files:
            if name.startswith('test_') and name.endswith('.c'):
                all_files.append(os.path.join(path, name))
    return all_files

def main():
    tmpdir = tempfile.mkdtemp()

    testfiles = all_testfiles_r()
    testcases = []

    for test_file in testfiles:
        testcases.extend(extract_testcases(test_file))
        
    c_file = write_c_file(includes=testfiles, testcases=testcases, tmpdir=tmpdir)
    compile_and_run(c_file, tmpdir)


if __name__ == "__main__": 
    main()
