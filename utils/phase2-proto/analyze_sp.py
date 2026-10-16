# Usage: python3 analyze_sp.py <dir> <mode>...
# Summarizes -Xlog:safepoint logs named <mode>-<run>-sp.log: GC safepoints (G1 operations), their
# count, mean / p50 / p99 / max of "At safepoint" time (the pause itself, where the GC-start hook
# runs) and total stopped time per run.
import glob, re, statistics, sys
d, modes = sys.argv[1], sys.argv[2:]
pat = re.compile(r'Safepoint "([^"]+)".*?At safepoint: (\d+) ns.*?Total: (\d+) ns')
print(f"{'mode':10} {'runs':>4} {'GC sp/run':>9} {'mean ms':>8} {'p50':>7} {'p99':>7} {'max':>7} {'stopped s/run':>13}")
for m in modes:
    at, runs, stopped = [], 0, []
    for f in sorted(glob.glob(f"{d}/{m}-*-sp.log")):
        runs += 1
        rows = pat.findall(open(f).read())
        gc = [int(a) / 1e6 for op, a, t in rows if op.startswith('G1') or 'Collect' in op]
        at += gc
        stopped.append(sum(int(t) for op, a, t in rows) / 1e9)
    if not at:
        print(m, "no data"); continue
    at.sort()
    q = lambda p: at[min(len(at) - 1, int(p * len(at)))]
    print(f"{m:10} {runs:>4} {len(at)//runs:>9} {statistics.mean(at):>8.3f} {q(.5):>7.3f} {q(.99):>7.3f} {at[-1]:>7.3f} {statistics.mean(stopped):>13.3f}")
