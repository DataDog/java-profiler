---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-02 10:41:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 13 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793633824 48
1793633829 48
1793633834 43
1793633839 43
1793633844 43
1793633849 43
1793633854 43
1793633859 43
1793633864 43
1793633869 43
1793633874 43
1793633879 43
1793633884 43
1793633889 43
1793633894 43
1793633899 43
1793633904 43
1793633909 43
1793633914 43
1793633919 43
```
</details>

---

