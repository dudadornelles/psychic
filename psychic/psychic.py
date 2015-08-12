#!/usr/bin/python

import re
import argparse
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


def compile_and_run(c_file_path, cargs, tmpdir):
    testfile_object_path = path.join(tmpdir, "testfile.o")
    psychic_c_dep = path.join(_here(), "csource", "psychic.c")

    subprocess.call("gcc %s %s -o %s -I. %s" % (psychic_c_dep, c_file_path, testfile_object_path, cargs), shell=True)
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


def parseargs():
    parser = argparse.ArgumentParser()
    parser.add_argument('--cargs')
    args = parser.parse_args()
    return args.cargs or ""
    

def all_testcases(testfiles):
    testcases = []
    for test_file in testfiles:
        testcases.extend(extract_testcases(test_file))
    return testcases
     

def main():
    cargs = parseargs()
    tmpdir = tempfile.mkdtemp()
    testfiles = all_testfiles_r()
    testcases = all_testcases(testfiles)
        
    c_file = write_c_file(includes=testfiles, testcases=testcases, tmpdir=tmpdir)
    compile_and_run(c_file, cargs, tmpdir)


if __name__ == "__main__": 
    main()
