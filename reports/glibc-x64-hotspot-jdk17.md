---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-03-13 07:10:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 11 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (4 unique values: 34-41 cores)</summary>

```
1773400036 34
1773400041 34
1773400046 34
1773400051 34
1773400056 34
1773400061 37
1773400066 37
1773400071 39
1773400076 39
1773400081 39
1773400086 39
1773400091 39
1773400096 39
1773400101 39
1773400106 39
1773400111 39
1773400116 39
1773400121 39
1773400126 39
1773400131 39
```
</details>

---

