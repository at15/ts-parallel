#!/usr/bin/env python3

import json
import numpy as np
import pandas as pd
import csv


def main():
    # load the json
    f = open("at15.json", "r")
    s = f.read()
    data = json.loads(s)
    # days, range, user
    # print(data["user"])
    # print(data["range"])
    # print(data["days"][0])
    num_days = len(data["days"])
    print(num_days)

    # for key, value in one_day.items():
    #     print(key)
    #     print(value)
    one_day = data["days"][num_days - 1]
    # print(json.dumps(one_day))
    # for key in one_day:
    #     print(key)

    # TODO: change the data into pandas data frame

    dates = pd.date_range('20130101', periods=6)
    df = pd.DataFrame(np.random.randn(6, 4), index=dates, columns=list('ABCD'))
    print(df.head())

    days = []
    projects = []
    names = []
    times = []
    for day in data["days"]:
        # 2016 is empty
        # print(day["date"], day["grand_total"]["total_seconds"])

        # assert number of entities is same as entities scattered in projects
        # n = 0
        # for project in day["projects"]:
        #     n = n + len(project["entities"])
        # print(len(day["entities"]), n)

        # around 20 days that use dual file system
        # if len(day["operating_systems"]) > 1:
        #     print(day["date"])

        # build the arrays
        for project in day["projects"]:
            for entity in project["entities"]:
                days.append(day["date"])
                projects.append(project["name"])
                names.append(entity["name"])
                times.append(entity["total_seconds"])
    print(len(projects))

    print("dump to csv");
    with open('at15.csv', 'w') as csvfile:
        fieldnames = ['date', 'project', 'name', 'time']
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames)
        writer.writeheader
        for i in range(len(days)):
            writer.writerow({
                'date': days[i],
                'project': projects[i],
                'name': names[i],
                'time': times[i]
            })
    print("dump finished");        
    # print(dates[:20])

    # http://pandas.pydata.org/pandas-docs/stable/10 min.html  #
    # object-creation
    df2 = pd.DataFrame({
        "date": pd.Series(days),
        "project": pd.Categorical(projects),
        "name": pd.Series(names),
        "time": np.array(times),
    })

    print(df2.head())
    print(df2.describe())
    # print(df2.sort_values(by='time', ascending=False))


if __name__ == "__main__":
    main()
