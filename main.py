import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages


table1 = pd.read_csv("212_AntoshkinAlexeyAlexandrovich_table1.csv", sep=';', index_col='Length')
table2 = pd.read_csv("212_AntoshkinAlexeyAlexandrovich_table2.csv", sep=';', index_col='Length')

name = ['Random 0-5', 'Random Max', 'Almost Sorted', 'Reversed']
type = ['Time (ns.)', 'Operations']

pdf = PdfPages("Figures.pdf")

for j in range(2):
    for i in range(4):
        plt.rcParams["figure.figsize"] = [10, 7]
        plt.rcParams["figure.autolayout"] = True
        table1.iloc[:, i * 2 + j::8].plot()
        plt.title(name[i] + ' (Table 1)')
        plt.ylabel(type[j])
        pdf.savefig()
        plt.close()

        plt.rcParams["figure.figsize"] = [10, 7]
        plt.rcParams["figure.autolayout"] = True
        table2.iloc[:, i * 2 + j::8].plot()
        plt.title(name[i] + ' (Table 2)')
        plt.ylabel(type[j])
        pdf.savefig()
        plt.close()

name = ["SelectionSort",
        "BubbleSort",
        "BubbleSortFirstIverson",
        "BubbleSortSecondIverson",
        "InsertionSort",
        "BinaryInsertionSort",
        "CountingSort",
        "RadixSort",
        "MergeSort",
        "QuickSort",
        "HeapSort",
        "ShellSortCiuraSequence",
        "ShellSortShellSequence"]

for j in range(2):
    for i in range(13):
        plt.rcParams["figure.figsize"] = [10, 7]
        plt.rcParams["figure.autolayout"] = True
        table1.iloc[:, i * 4 * 2 + j : (i + 1) * 4 * 2 : 2].plot()
        plt.title(name[i] + ' (Table 1)')
        plt.ylabel(type[j])
        pdf.savefig()
        plt.close()


        plt.rcParams["figure.figsize"] = [10, 7]
        plt.rcParams["figure.autolayout"] = True
        table2.iloc[:, i * 4 * 2 + j : (i + 1) * 4 * 2 : 2].plot()
        plt.title(name[i] + ' (Table 2)')
        plt.ylabel(type[j])
        pdf.savefig()
        plt.close()

pdf.close()