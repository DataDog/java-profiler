---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 17:11:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (5 unique values: 36-46 cores)</summary>

```
1793657240 38
1793657245 38
1793657250 38
1793657255 38
1793657260 38
1793657265 36
1793657270 36
1793657275 41
1793657280 41
1793657285 41
1793657290 41
1793657295 43
1793657300 43
1793657305 43
1793657310 43
1793657315 46
1793657320 46
1793657325 46
1793657330 46
1793657335 46
```
</details>

---

