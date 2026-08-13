---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-13 16:15:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
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
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 12 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 8 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1786651862 64
1786651867 64
1786651872 64
1786651877 64
1786651882 64
1786651887 64
1786651892 64
1786651897 64
1786651902 64
1786651907 64
1786651912 64
1786651917 64
1786651922 64
1786651927 64
1786651932 64
1786651937 64
1786651942 64
1786651947 64
1786651952 64
1786651957 64
```
</details>

---

