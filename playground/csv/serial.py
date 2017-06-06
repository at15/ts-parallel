import time
import pandas as pd


def main():
    start_time = time.time()
    # take 0.49767 s
    df = pd.read_csv("prices-split-adjusted.csv")
    elapsed_time = time.time() - start_time
    print(elapsed_time)
    print(df.head())
    # https://stackoverflow.com/questions/15943769/how-do-i-get-the-row-count-of-a-pandas-dataframe
    print(df.index)


if __name__ == "__main__":
    main()
