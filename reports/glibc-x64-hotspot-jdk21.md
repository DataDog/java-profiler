---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-09 12:30:01 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 11 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (5 unique values: 57-96 cores)</summary>

```
1794245075 94
1794245080 94
1794245085 94
1794245090 92
1794245095 92
1794245100 94
1794245105 94
1794245110 94
1794245115 94
1794245120 94
1794245125 94
1794245130 94
1794245135 94
1794245140 96
1794245145 96
1794245150 96
1794245155 59
1794245160 59
1794245165 59
1794245170 59
```
</details>

---

