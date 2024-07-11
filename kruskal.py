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
# Gruppieren der Daten nach Knotenanzahl und UnionFind-Variante
# grouped_data = data.groupby(['n', 'union_find']).agg(
#     mean_accesses=('accesses', 'mean'),
#     std_accesses=('accesses', 'std')
# ).reset_index()
x = data["n"]
y = data["accesses"]
print(data.head())

# Erstellen des ersten Plots
plt.figure(figsize=(12, 6))
sns.set(style="whitegrid")

sns.lineplot(data, x='n', y='accesses')


plt.semilogx(base=2)
plt.xlabel("Knotenanzahl n")
plt.ylabel("durchschnittliche Elternarray-Zugriffe pro Kante")
plt.title('Elternarray-Zugriffe pro Kante für verschiedene UnionFind-Varianten')
plt.legend(title='UnionFind Variante')
plt.tight_layout()


plt.savefig("kruskal.pdf")
plt.close()

