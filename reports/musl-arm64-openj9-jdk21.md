---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-05 21:05:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 251 |
| Sample Rate | 4.18/sec |
| Health Score | 261% |
| Threads | 12 |
| Allocations | 117 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793930480 43
1793930485 43
1793930490 43
1793930495 43
1793930500 43
1793930505 43
1793930510 43
1793930515 48
1793930520 48
1793930525 48
1793930530 48
1793930535 48
1793930540 48
1793930545 48
1793930550 48
1793930555 48
1793930560 48
1793930565 48
1793930570 48
1793930575 48
```
</details>

---

