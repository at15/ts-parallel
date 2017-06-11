#!/usr/bin/env python

import multiprocessing
import subprocess


def main():
    backends = ["serial", "boost", "thrust"]
    operations = ["sort", "reduce"]
    types = ["int", "float", "double"]
    # nums = [10, 50, 100, 300, 500, 1000, 2000, 3000, 5000]
    nums = [10, 50]
    for backend in backends:
        binary = "./bench_" + backend
        # print(binary)
        for op in operations:
            for num in nums:
                for tp in types:
                    cmd = binary + " --op " + op + \
                        " --num " + str(num) + " --type " + tp
                    print(cmd)
                    result = subprocess.run(
                        [binary, "--op", op, "--num", str(num), "--type", tp], stdout=subprocess.PIPE)
                    # TODO: check return code
    print("all done, checkout the csv files")


if __name__ == "__main__":
    main()
