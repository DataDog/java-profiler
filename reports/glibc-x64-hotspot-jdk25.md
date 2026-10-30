---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 11:47:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 10 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 10 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (2 unique values: 77-79 cores)</summary>

```
1793374920 79
1793374925 79
1793374930 79
1793374935 79
1793374940 79
1793374945 79
1793374950 79
1793374955 79
1793374960 79
1793374965 79
1793374970 77
1793374975 77
1793374980 77
1793374985 77
1793374990 77
1793374995 77
1793375000 77
1793375005 77
1793375010 77
1793375015 77
```
</details>

---

