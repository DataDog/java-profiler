---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-02 07:22:55 EST

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
| CPU Cores (start) | 67 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (3 unique values: 67-96 cores)</summary>

```
1793621912 67
1793621917 67
1793621922 67
1793621927 67
1793621932 67
1793621937 67
1793621942 67
1793621947 67
1793621952 67
1793621957 67
1793621962 67
1793621967 67
1793621972 67
1793621977 67
1793621982 67
1793621987 75
1793621992 75
1793621997 75
1793622002 75
1793622007 75
```
</details>

---

