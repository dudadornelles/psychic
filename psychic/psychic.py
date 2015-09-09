#!/usr/bin/python

import re
import argparse
import string
import tempfile
import subprocess
import sys
import os
from jinja2 import Template

from os import path
from glob import glob


def _here():
    return path.abspath(path.dirname(__file__))


def write_c_file(includes, testcases, tmpdir):
    template = Template(open("%s/testfile.c.jinja" % _here()).read())
    includes = map(path.abspath, includes)
    content = template.render(includes=includes,
                              testcases=testcases, here=_here())

    testfile_path = path.join(tmpdir, "testfile.c")
    testfile = open(testfile_path, "w")
    testfile.write(content)
    testfile.close()

    return testfile_path


def compile_and_run(c_file_path, args, tmpdir):
    testfile_object_path = path.join(tmpdir, "testfile.o")
    psychic_c_dep = path.join(_here(), "csource", "psychic.c")
    cargs, debug = args['cargs'], args['debug']
    gcc_line = "gcc %s %s -o %s %s" % (psychic_c_dep, c_file_path, testfile_object_path, cargs)

    if (debug):
        subprocess.call(gcc_line + " -g", shell=True)
        subprocess.call("gdb %s" % testfile_object_path, shell=True)
    else:
        subprocess.call(gcc_line, shell=True)
        number_of_errors = int(subprocess.call(testfile_object_path))
    return number_of_errors


def testcases_in(test_filename):
    # TODO: use a code analyzer to do this
    stream = open(test_filename).read()
    pattern = "void\s*(test_.*?\(\))"
    return re.findall(pattern, stream)


def all_testfiles_r():
    all_files = []
    for path, subdirs, files in os.walk("."):
        for name in files:
            if name.startswith('test_') and name.endswith('.c'):
                all_files.append(os.path.join(path, name))
    return all_files


def parseargs():
    parser = argparse.ArgumentParser(description="Python-powered C Unit Testing - http://github.com/dudadornelles/psychic")
    parser.add_argument('--cargs', help="CARGS to be passed to the compiler")
    parser.add_argument('-d', '--debug', action='store_true', help="Run in debug mode with gdb")
    args = parser.parse_args()
    return {
        'cargs': args.cargs or "",
        'debug': args.debug or False
    }


def main():
    print "\n"
    args = parseargs()
    tmpdir = tempfile.mkdtemp()
    total_failures = 0
    total_tests = 0

    for testfile in all_testfiles_r():
        testcases = testcases_in(testfile)
        c_file = write_c_file(includes=[testfile], testcases=testcases, tmpdir=tmpdir)
        total_failures += compile_and_run(c_file, args, tmpdir)
        total_tests += len(testcases)

    print "\n\nTests ran: %s, Failures: %s" % (total_tests, total_failures)

    sys.exit(total_failures)

if __name__ == "__main__":
    main()
