---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 05:22:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 8 |
| Allocations | 314 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 10 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (4 unique values: 52-64 cores)</summary>

```
1795429076 64
1795429081 64
1795429086 56
1795429091 56
1795429096 56
1795429101 56
1795429106 56
1795429111 56
1795429116 56
1795429121 56
1795429126 56
1795429131 56
1795429136 56
1795429141 56
1795429146 56
1795429151 56
1795429156 56
1795429161 56
1795429166 56
1795429171 56
```
</details>

---

