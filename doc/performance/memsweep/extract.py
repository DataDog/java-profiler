import json, sys

path = sys.argv[1]
d = json.load(open(path))
events = d.get("recording", {}).get("events", [])
last = {}
for e in events:
    vals = e.get("values", {})
    name = vals.get("name")
    count = vals.get("count")
    if name and name.startswith("native_mem_"):
        last[name] = count

keys = [
    "native_mem_live_bytes",
    "native_mem_avg_bytes",
    "native_mem_max_bytes",
    "native_mem_max_observed_total_bytes",
    "native_mem_live_bytes.calltrace",
    "native_mem_live_bytes.dictionary",
    "native_mem_live_bytes.thread_filter",
    "native_mem_live_bytes.thread_local",
    "native_mem_live_bytes.native_symbols",
    "native_mem_live_bytes.line_tables",
    "native_mem_live_bytes.jfr_buffers",
    "native_mem_live_bytes.method_map",
    "native_mem_live_bytes.liveness",
    "native_mem_live_bytes.perf",
    "native_mem_live_bytes.misc",
]
print(",".join(str(last.get(k, "")) for k in keys))
