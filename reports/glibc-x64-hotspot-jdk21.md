---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-03-06 05:53:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 476 |
| Sample Rate | 7.93/sec |
| Health Score | 496% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (4 unique values: 27-38 cores)</summary>

```
1772794081 27
1772794086 27
1772794091 27
1772794096 27
1772794101 36
1772794106 36
1772794111 38
1772794116 38
1772794121 38
1772794126 38
1772794131 38
1772794136 34
1772794141 34
1772794146 34
1772794151 34
1772794156 34
1772794161 34
1772794166 34
1772794171 34
1772794176 34
```
</details>

---

