import argparse
import numpy as np
import matplotlib.pyplot as plt

# Provisional bound; at most half of the samples may lack usable load markers.
NA_SHARE_MAX = 0.5
# Provisional; a quiet container reads 0.00 (observed 2026-11-10) and
# sustained values of a few percent mean reclaim is altering the RSS series.
PSI_MEMORY_SOME_AVG10_MAX = 5.0
# psi_cpu_some_avg10 is recorded only, never gating: scheduler contention
# distorts latency verdicts, not RSS trends.

# Provisional bound; a clean non-binding run rose 0->4 throttles, so twice that is allowed.
THROTTLE_EVENTS_MAX = 8
# Provisional bound; the release probe must give back at least half of the growth.
RELEASE_RECOVERY_SHARE = 0.5

# glibc's trim only shrinks the main-arena top, so retained thread-arena RSS can
# still be releasable.
GMALLOC_FAIL_REASON = ("Memory usage is trending up after the malloc_trim release probe"
                       " (thread-arena heap tops are not trimmed, so retained RSS may still"
                       " be releasable)")

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

def parse_key_values(text):
    """Splits whitespace-separated key=value tokens into a dict, skipping other tokens."""
    values = {}
    for token in text.split():
        key, sep, value = token.partition("=")
        if sep:
            values[key] = value
    return values

def numeric_value(value):
    try:
        return float(value)
    except (TypeError, ValueError):
        return None

def marker_value(markers, key):
    """Numeric marker value, or None for a missing record, a missing key or NA."""
    if markers is None:
        return None
    return numeric_value(markers.get(key))

def read_marker_records(file_path, sample_count):
    """One markers dict (or None) per mem sample; a markers record belongs to the
    mem sample that precedes it, and a sample without one counts as NA."""
    markers = [None] * sample_count
    index = -1
    with open(file_path, 'r') as file:
        for line in file:
            if line.startswith("mem:"):
                index += 1
            elif line.startswith("markers:") and 0 <= index < sample_count and markers[index] is None:
                markers[index] = parse_key_values(line[len("markers:"):])
    return markers

def read_probe_records(file_path):
    """Probe bookkeeping; rss is None when the record is absent or its value is not numeric."""
    probe = {"status": None, "before_rss": None, "after_rss": None}
    with open(file_path, 'r') as file:
        for line in file:
            if line.startswith("probe_before:") or line.startswith("probe_after:"):
                values = parse_key_values(line.split(":", 1)[1])
                rss = numeric_value(values.get("rss_kb"))
                key = "before_rss" if line.startswith("probe_before:") else "after_rss"
                probe[key] = int(rss) if rss is not None else None
            elif line.startswith("release_probe=jcmd") and probe["status"] is None:
                probe["status"] = parse_key_values(line[len("release_probe="):]).get("status")
    return probe

def compute_verdict(memory_log, sample_markers, probe, allocator):
    """First-match verdict over the row's own series; returns (verdict, reason)."""
    if len(memory_log) < 5:
        return "inconclusive", f"Only {len(memory_log)} memory samples were recorded, at least 5 are needed"

    na_count = 0
    psi_memory_values = []
    throttle_values = []
    for markers in sample_markers:
        psi_memory = marker_value(markers, "psi_memory_some_avg10")
        throttled = marker_value(markers, "cpu_nr_throttled")
        if psi_memory is None or throttled is None:
            na_count += 1
        else:
            psi_memory_values.append(psi_memory)
            throttle_values.append(throttled)

    if na_count / len(memory_log) > NA_SHARE_MAX:
        return "inconclusive", f"Load markers were missing for {na_count} of {len(memory_log)} memory samples"

    psi_memory_median = float(np.median(psi_memory_values))
    if psi_memory_median > PSI_MEMORY_SOME_AVG10_MAX:
        return "inconclusive", f"Median host memory pressure {psi_memory_median:g} is above the provisional bound"

    throttle_delta = throttle_values[-1] - throttle_values[0]
    if throttle_delta > THROTTLE_EVENTS_MAX:
        return "inconclusive", f"CPU throttling rose by {throttle_delta:g} events over the window, above the provisional bound"

    if allocator == "gmalloc":
        if probe["status"] is None:
            return "inconclusive", "No jcmd release probe record is present"
        if probe["status"] != "ok":
            return "inconclusive", f"The release probe reported status {probe['status']}"
        if probe["before_rss"] is None or probe["after_rss"] is None:
            return "inconclusive", "The release probe did not record a usable RSS value"

    persistent_growth, _ = detect_memory_growth(memory_log, 5, 0.01)
    if not persistent_growth:
        return "pass", "No persistent memory growth was detected"
    if allocator != "gmalloc":
        return "fail", "Memory usage is trending up"

    growth_kb = probe["before_rss"] - memory_log[0]
    released_kb = probe["before_rss"] - probe["after_rss"]
    if growth_kb > 0 and released_kb >= RELEASE_RECOVERY_SHARE * growth_kb:
        return "pass", f"The release probe released {released_kb} kB of the {growth_kb} kB growth"
    return "fail", GMALLOC_FAIL_REASON

def main():
    # Set up the argument parser
    parser = argparse.ArgumentParser(description="Calculate moving average and check if the trend is increasing.")
    parser.add_argument("filename", type=str, help="The path to the data file.")
    parser.add_argument("--plot", action="store_true", help="Plot the memory usage over time.")
    parser.add_argument("--output", type=str, help="Output file for the plot.")
    parser.add_argument("--allocator", type=str, default=None,
                        help="Allocator under test; enables the pass/fail/inconclusive verdict.")

    # Parse the command line arguments
    args = parser.parse_args()
    allocator = args.allocator
    # The printed namespace must stay byte-identical when --allocator is absent.
    del args.allocator
    print("Arguments: ", args)

    memory_log = read_memory_log(args.filename)

    window_size = 5
    threshold = 0.01

    # Without --allocator a short series keeps today's failure; the verdict path
    # reports it as inconclusive instead of crashing.
    if allocator is None or len(memory_log) >= window_size:
        persistent_growth, growth_trend = detect_memory_growth(memory_log, window_size, threshold)
        if persistent_growth:
            print("Persistent and significant memory growth detected.")
            print("TREND:up")
        else:
            print("No persistent and significant memory growth detected.")
    else:
        growth_trend = []

    plot_memory_log(memory_log, growth_trend, window_size, args.output, args.plot)

    if allocator is not None:
        sample_markers = read_marker_records(args.filename, len(memory_log))
        probe = read_probe_records(args.filename)
        verdict, reason = compute_verdict(memory_log, sample_markers, probe, allocator)
        print(f"VERDICT:{verdict}")
        print(f"VERDICT_REASON:{reason}")

if __name__ == "__main__":
    main()
