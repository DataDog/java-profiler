---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 11:47:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 782 |
| Sample Rate | 13.03/sec |
| Health Score | 814% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 7 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1793374914 64
1793374920 64
1793374925 64
1793374930 64
1793374935 64
1793374940 64
1793374945 64
1793374950 64
1793374955 64
1793374960 64
1793374965 64
1793374970 64
1793374975 64
1793374980 64
1793374985 64
1793374990 64
1793374995 64
1793375000 64
1793375005 64
1793375010 64
```
</details>

---

