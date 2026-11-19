---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 11:31:13 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 258 |
| Sample Rate | 4.30/sec |
| Health Score | 269% |
| Threads | 11 |
| Allocations | 160 |

<details>
<summary>CPU Timeline (2 unique values: 20-34 cores)</summary>

```
1795105565 34
1795105570 20
1795105575 20
1795105580 20
1795105585 20
1795105590 20
1795105595 20
1795105600 20
1795105605 20
1795105610 20
1795105615 20
1795105620 20
1795105625 20
1795105630 20
1795105635 20
1795105640 20
1795105645 20
1795105650 20
1795105655 20
1795105660 20
```
</details>

---

