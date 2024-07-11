import numpy as np
from numpy import std, median

pc = [85519840, 85359474, 85430228, 85495475, 85400741]
rank = [29694604, 29762331, 29827548, 29673240, 29786212]
pc_rank = [31533582, 31488842, 31516358, 31499785, 31510371]

print(f"Path Compression:\n-\tmedian: {median(pc)}\n-\tstd: {std(pc)}")
print(f"Union by Rank:\n-\tmedian: {median(rank)}\n-\tstd: {std(rank)}")
print(f"Both:\n-\tmedian: {median(pc_rank)}\n-\tstd: {std(pc_rank)}")
