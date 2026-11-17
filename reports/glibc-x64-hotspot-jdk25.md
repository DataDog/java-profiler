---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 05:59:00 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 387 |
| Sample Rate | 6.45/sec |
| Health Score | 403% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 10 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (3 unique values: 42-79 cores)</summary>

```
1794912872 42
1794912877 42
1794912882 42
1794912887 42
1794912892 42
1794912897 42
1794912902 42
1794912907 42
1794912912 42
1794912917 42
1794912922 42
1794912927 42
1794912932 42
1794912937 42
1794912942 71
1794912947 71
1794912952 71
1794912957 71
1794912962 71
1794912967 71
```
</details>

---

