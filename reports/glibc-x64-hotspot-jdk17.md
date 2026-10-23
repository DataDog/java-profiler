---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-23 05:58:13 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 431 |
| Sample Rate | 7.18/sec |
| Health Score | 449% |
| Threads | 9 |
| Allocations | 326 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (5 unique values: 28-92 cores)</summary>

```
1792749086 28
1792749091 28
1792749096 28
1792749101 28
1792749106 28
1792749111 61
1792749116 61
1792749121 61
1792749126 61
1792749131 61
1792749136 61
1792749141 61
1792749146 59
1792749151 59
1792749156 59
1792749161 59
1792749166 59
1792749171 59
1792749176 59
1792749181 59
```
</details>

---

