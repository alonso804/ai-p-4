import pandas as pd
import numpy as np
from sklearn.decomposition import PCA
from sklearn.preprocessing import MinMaxScaler


def reduction(data, components):
    pca = PCA(n_components=components)
    principalComponents = pca.fit_transform(data)
    df = pd.DataFrame(data=principalComponents)
    df.to_csv("reducted.csv", index=False)


def normalize(data):
    scaler = MinMaxScaler()
    normalizeData = scaler.fit_transform(data)

    return normalizeData


def preprocessing(dataset, outputfile, shuffle=False):
    df = pd.read_csv(dataset)
    df = df.dropna()
    df.iloc[:, 1:] = normalize(df.iloc[:, 1:])

    if shuffle == True:
        # np.random.seed(0)
        df = df.sample(frac=1)

    df.to_csv(outputfile, index=False)


def main():
    preprocessing("../data/sign_mnist_train.csv",
                  "../data/train_normalize.csv", True)
    preprocessing("../data/sign_mnist_test.csv", "../data/test_normalize.csv")


if __name__ == "__main__":
    main()
