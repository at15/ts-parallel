import json


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
    print(json.dumps(one_day))
    # for key in one_day:
    #     print(key)


if __name__ == "__main__":
    main()
