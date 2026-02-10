---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-02-10 16:50:45 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 879 |
| Sample Rate | 14.65/sec |
| Health Score | 916% |
| Threads | 11 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (3 unique values: 32-64 cores)</summary>

```
1770760060 32
1770760065 32
1770760070 32
1770760075 32
1770760080 32
1770760085 32
1770760090 46
1770760095 46
1770760100 46
1770760105 46
1770760110 46
1770760115 46
1770760120 46
1770760125 46
1770760130 46
1770760135 46
1770760140 46
1770760145 46
1770760150 46
1770760155 46
```
</details>

---

