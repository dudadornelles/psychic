#!/usr/bin/python

import uuid
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


def write_c_file(testfile, testcases, setup, teardown, tmpdir, results_tmpdir):
    def format_testname(testname):
        return re.sub(r'[ ()]', '', testname)

    template = Template(open("%s/testfile.c.jinja" % _here()).read())
    testfile = path.abspath(testfile)

    results_file = path.join(results_tmpdir, str(uuid.uuid4()))
    content = template.render(testfile=testfile,
                              testcases=testcases, 
                              results_file=results_file,
                              setup=setup,
                              teardown=teardown,
                              format_testname=format_testname,
                              here=_here())

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


def testcases_in(test_filename, test_config):
    # TODO: use a code analyzer to do this
    stream = open(test_filename).read()
    test_pattern = "void\s*(test_.*?\(\))"
    setup_pattern = "void\s*(setup.*?\(\))"
    teardown_pattern = "void\s*(teardown.*?\(\))"
    testcases = [test_config[1] +"()"] if test_config[1] else re.findall(test_pattern, stream)
    return testcases, re.findall(setup_pattern, stream), re.findall(teardown_pattern, stream)


def all_testfiles_r(test_config):
    if test_config[0]:
        return [test_config[0]]
    all_files = []
    for path, subdirs, files in os.walk("."):
        for name in files:
            if name.startswith('test_') and name.endswith('.c'):
                all_files.append(os.path.join(path, name))
    return all_files


def parseargs():
    parser = argparse.ArgumentParser(description="Python-powered C Unit Testing - http://github.com/dudadornelles/psychic")
    parser.add_argument('test', help="testfile:testname; e.g. test/test_stuff.c:test_does_stuf", nargs="?")
    parser.add_argument('--cargs', help="CARGS to be passed to the compiler")
    parser.add_argument('-d', '--debug', action='store_true', help="Run in debug mode with gdb")
    args = parser.parse_args()
    return {
        'cargs': args.cargs or "",
        'debug': args.debug or False,
        'test': args.test and (args.test.split(":") + [None])[0:2] or (None, None)
    }


def print_error_messages(results_tmpdir):
    str_error_messages = "\n"
    for path, subdirs, files in os.walk(results_tmpdir):
        for name in files:
            str_error_messages += open(os.path.join(path, name)).read()
    print(str_error_messages)


def main():
    print("")
    args = parseargs()
    tmpdir = tempfile.mkdtemp()
    results_tmpdir = tempfile.mkdtemp()
    total_failures = 0
    total_tests = 0
    test_config = args["test"]

    for testfile in all_testfiles_r(test_config):
        testcases, setup, teardown = testcases_in(testfile, test_config)
        c_file = write_c_file(testfile=testfile, testcases=testcases, setup=setup, teardown=teardown, tmpdir=tmpdir, results_tmpdir=results_tmpdir)
        total_failures += compile_and_run(c_file, args, tmpdir)
        total_tests += len(testcases)

    print_error_messages(results_tmpdir)
    print("\nTests ran: %s, Failures: %s" % (total_tests, total_failures))

    sys.exit(total_failures)

if __name__ == "__main__":
    main()
