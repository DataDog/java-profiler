---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 06:18:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 389 |
| Sample Rate | 6.48/sec |
| Health Score | 405% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 197 |
| Sample Rate | 3.28/sec |
| Health Score | 205% |
| Threads | 14 |
| Allocations | 118 |

<details>
<summary>CPU Timeline (3 unique values: 26-31 cores)</summary>

```
1795605065 31
1795605070 31
1795605075 31
1795605080 31
1795605085 31
1795605090 31
1795605095 31
1795605100 31
1795605105 31
1795605110 31
1795605115 31
1795605120 31
1795605125 31
1795605130 31
1795605135 31
1795605140 31
1795605145 31
1795605150 31
1795605155 26
1795605160 26
```
</details>

---

