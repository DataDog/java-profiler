---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-11 20:52:51 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 273 |
| Sample Rate | 4.55/sec |
| Health Score | 284% |
| Threads | 11 |
| Allocations | 105 |

<details>
<summary>CPU Timeline (2 unique values: 51-56 cores)</summary>

```
1778546969 51
1778546974 51
1778546979 56
1778546984 56
1778546989 56
1778546994 56
1778546999 56
1778547004 56
1778547009 56
1778547014 56
1778547019 56
1778547024 56
1778547029 56
1778547034 56
1778547039 56
1778547044 56
1778547049 56
1778547054 56
1778547059 56
1778547064 56
```
</details>

---

