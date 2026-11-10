---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-10 14:54:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 369 |
| Sample Rate | 6.15/sec |
| Health Score | 384% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 250 |
| Sample Rate | 4.17/sec |
| Health Score | 261% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 85-92 cores)</summary>

```
1794340100 87
1794340105 85
1794340110 85
1794340115 85
1794340120 85
1794340125 85
1794340130 85
1794340135 90
1794340140 90
1794340145 90
1794340150 90
1794340155 90
1794340160 90
1794340165 90
1794340170 92
1794340175 92
1794340180 92
1794340185 90
1794340191 90
1794340196 90
```
</details>

---

