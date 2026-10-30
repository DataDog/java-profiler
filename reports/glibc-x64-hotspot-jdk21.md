---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-30 06:28:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 10 |
| Allocations | 435 |

<details>
<summary>CPU Timeline (3 unique values: 73-96 cores)</summary>

```
1793355867 77
1793355872 77
1793355877 77
1793355882 77
1793355887 77
1793355892 77
1793355897 77
1793355902 77
1793355907 77
1793355912 77
1793355917 77
1793355922 77
1793355927 77
1793355932 77
1793355937 77
1793355942 77
1793355947 96
1793355952 96
1793355957 96
1793355962 96
```
</details>

---

