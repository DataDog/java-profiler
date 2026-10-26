---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-26 08:57:42 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 10 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (3 unique values: 29-32 cores)</summary>

```
1793019080 29
1793019085 29
1793019090 29
1793019095 29
1793019100 29
1793019105 29
1793019110 29
1793019115 29
1793019120 29
1793019125 29
1793019130 32
1793019135 32
1793019140 30
1793019145 30
1793019150 30
1793019155 30
1793019160 30
1793019165 30
1793019170 30
1793019175 30
```
</details>

---

