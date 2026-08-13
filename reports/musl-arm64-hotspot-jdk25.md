---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-13 16:15:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1786651867 32
1786651872 32
1786651877 32
1786651882 32
1786651887 32
1786651892 32
1786651897 32
1786651902 32
1786651907 32
1786651912 32
1786651917 32
1786651922 32
1786651927 32
1786651932 32
1786651937 32
1786651942 32
1786651947 32
1786651952 32
1786651957 32
1786651962 32
```
</details>

---

