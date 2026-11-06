---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-05 21:05:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 46 |
| Sample Rate | 0.77/sec |
| Health Score | 48% |
| Threads | 9 |
| Allocations | 43 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 176 |
| Sample Rate | 2.93/sec |
| Health Score | 183% |
| Threads | 11 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1793930470 40
1793930475 40
1793930480 40
1793930485 40
1793930490 40
1793930495 40
1793930500 40
1793930505 40
1793930510 40
1793930515 40
1793930520 40
1793930525 40
1793930530 40
1793930535 40
1793930540 40
1793930545 40
1793930550 40
1793930555 40
1793930560 40
1793930565 40
```
</details>

---

