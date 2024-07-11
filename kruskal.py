#!/usr/bin/env python3

# python3 -mvenv pyenv
# . ./pyenv/bin/activate
# pip3 install seaborn pandas matplotlib
# ./kruskal.py

import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
import pandas as pd

data = pd.read_csv("kruskal.csv")


print(data.describe())
print(data.head())

# Erstellen des ersten Plots
plt.figure(figsize=(12, 6))
sns.set(style="whitegrid")

plt.xscale('log')
plt.yscale('log')

sns.lineplot(data, x='n', y='accesses', marker='o', linestyle='-', hue='unionfind', errorbar='sd')


plt.xlabel("Knotenanzahl n")
plt.ylabel("durchschnittliche Elternarray-Zugriffe pro Kante")
plt.title('Elternarray-Zugriffe pro Kante für verschiedene UnionFind-Varianten')
plt.legend(title='UnionFind Variante')
plt.tight_layout()


plt.savefig("kruskal.pdf")
plt.close()

# Erstellen des zweiten Plots
data = data.loc[data['unionfind'].isin(['pc','rank'])]
data['div_by_mlogn'] = data['accesses'] / (np.log2(data['n']) * data['m'])

plt.figure(figsize=(12, 6))
sns.set(style="whitegrid")

plt.xscale('log')

sns.lineplot(data, x='n', y='div_by_mlogn', marker='*', linestyle='--', hue='unionfind', errorbar='sd')


plt.xlabel("Knotenanzahl n")
plt.ylabel(r"durchschnittliche Elternarray-Zugriffe pro Kante, \\n normalisiert mit $m\cdot \log(n)$")
plt.title('Elternarray-Zugriffe pro Kante für verschiedene UnionFind-Varianten')
plt.legend(title='UnionFind Variante')
plt.tight_layout()


plt.savefig("kruskal_comparison.pdf")
plt.close()