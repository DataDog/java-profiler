---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-26 14:59:54 EDT

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (3 unique values: 77-83 cores)</summary>

```
1793040917 83
1793040922 83
1793040927 83
1793040932 83
1793040937 83
1793040942 83
1793040947 83
1793040952 77
1793040957 77
1793040962 77
1793040967 77
1793040972 77
1793040977 77
1793040982 77
1793040987 79
1793040992 79
1793040997 79
1793041002 79
1793041007 79
1793041012 79
```
</details>

---

