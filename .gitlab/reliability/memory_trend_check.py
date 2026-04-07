import argparse
import numpy as np
import matplotlib.pyplot as plt

def detect_memory_growth(memory_log, window_size=5, threshold=0.01):
    growth_trend = []
    for i in range(len(memory_log) - window_size + 1):
        window = memory_log[i:i + window_size]
        growth = np.diff(window)
        avg_growth = np.mean(growth)
        growth_trend.append(avg_growth > threshold * window[0])

    persistent_growth = sum(growth_trend) / len(growth_trend) > 0.5  # More than 50% of the windows show growth
    return persistent_growth, growth_trend

def read_memory_log(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()
    memory_log = [int(line.split(":")[1].strip()) for line in lines if line.startswith("mem:")]
    return memory_log

def plot_memory_log(memory_log, growth_trend, window_size, output=None, show=False):
    print("Plotting memory log to " + output)

    plt.figure(figsize=(10, 5))
    plt.plot(range(0, len(memory_log)), memory_log, label='Memory Usage')
    plt.title('Memory Usage Over Time')
    plt.xlabel('Sample')
    plt.ylabel('Memory (units)')

    # Highlight the windows where growth is detected
    for i in range(len(growth_trend)):
        if growth_trend[i]:
            plt.axvspan(i, i + window_size, color='red', alpha=0.3)

    plt.legend()
    if (output):
        plt.savefig(output)
        plt.close()
    if (show):
        plt.show()

def main():
    # Set up the argument parser
    parser = argparse.ArgumentParser(description="Calculate moving average and check if the trend is increasing.")
    parser.add_argument("filename", type=str, help="The path to the data file.")
    parser.add_argument("--plot", action="store_true", help="Plot the memory usage over time.")
    parser.add_argument("--output", type=str, help="Output file for the plot.")

    print("Arguments: ", parser.parse_args())

    # Parse the command line arguments
    args = parser.parse_args()

    memory_log = read_memory_log(args.filename  )

    window_size = 5
    threshold = 0.01
    persistent_growth, growth_trend = detect_memory_growth(memory_log, window_size, threshold)

    if persistent_growth:
        print("Persistent and significant memory growth detected.")
        print("TREND:up")
    else:
        print("No persistent and significant memory growth detected.")

    plot_memory_log(memory_log, growth_trend, window_size, args.output, args.plot)

if __name__ == "__main__":
    main()