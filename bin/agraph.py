#!/usr/bin/env python3
import glob
import re
import csv
import matplotlib.pyplot as plt


def main():
    data = {}
    operations = ["sort", "reduce"]
    types = ["int", "float", "double"]
    for op in operations:
        for tp in types:
            # i.e. sort int
            data[op + "_" + tp] = {}
            results = glob.glob("*_" + op + "_*_" + tp + ".csv")
            for result in results:
                backend, num = re.match(
                    "(.*)_" + op + "_(.*)_" + tp + ".csv", result).groups()
                # data[op + "_" + tp]
                if backend not in data[op + "_" + tp]:
                    data[op + "_" + tp][backend] = {}
                num = int(num)
                print(backend, num)
                data[op + "_" + tp][backend][num] = {}
                with open(result) as f:
                    # NOTE: it will detect the header of CSV and change it to
                    # key
                    reader = csv.DictReader(f)
                    for row in reader:
                        data[op + "_" + tp][backend][num][row["stage"]] = row["duration"]
                        # print(row)
                        # print(results)
    print(data)
    # now let's draw the graph
    plot_data = {}
    for op, backends in data.items():
        print(op)
        plot_data[op] = []
        for backend, results in backends.items():
            pdata = {"name": backend, "x": [], "y": []}
            print(backend)
            # [(10, {'init': '2771', 'generate': '7667', 'copy': '112781784', 'run': '825079', 'delete': '67504'}), (50, {'init': '1045', 'generate': '8579', 'copy': '110102907', 'run': '1389482', 'delete': '68685'})]
            sorted_results = sorted(results.items())
            for result in sorted_results:
                num, stages = result
                print(num)
                if "run" not in stages:
                    print("didn't find run!", op, backend, num)
                    continue
                pdata["x"].append(num)
                pdata["y"].append(stages["run"])
            plot_data[op].append(pdata)
    print(plot_data)
    i = 1
    for op, pdatas in plot_data.items():
        plt.figure(i)
        i += 1
        for pdata in pdatas:
            plt.plot(pdata["x"], pdata["y"], label=pdata["name"])
        plt.title(op)
        plt.xlabel("Vector length")
        # TODO: ylabel is not shown, and the color changes in different figure
        # NOTE: we are using microseconds, because nano seconds got negative value
        plt.ylabel("Time (us)")
        plt.legend(loc='upper right', shadow=True, fontsize='x-small')
    plt.show()


if __name__ == "__main__":
    main()
