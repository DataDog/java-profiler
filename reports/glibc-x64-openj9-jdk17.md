---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-05 13:29:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 10 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (2 unique values: 10-12 cores)</summary>

```
1772735124 12
1772735129 12
1772735134 12
1772735139 12
1772735144 12
1772735150 12
1772735155 12
1772735160 12
1772735165 12
1772735170 12
1772735175 12
1772735180 12
1772735185 12
1772735190 12
1772735195 10
1772735200 10
1772735205 10
1772735210 10
1772735215 10
1772735220 10
```
</details>

---

