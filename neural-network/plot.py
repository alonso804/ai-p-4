import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("errors.csv", header=None)

plt.plot(df.values)
plt.show()
