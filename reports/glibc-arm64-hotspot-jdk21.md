---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-11 18:22:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 824 |
| Sample Rate | 13.73/sec |
| Health Score | 858% |
| Threads | 11 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1778537947 54
1778537952 59
1778537957 59
1778537962 59
1778537967 59
1778537972 59
1778537977 59
1778537982 59
1778537987 59
1778537992 59
1778537997 59
1778538002 59
1778538007 59
1778538012 59
1778538017 59
1778538022 59
1778538027 59
1778538032 59
1778538037 59
1778538042 64
```
</details>

---

