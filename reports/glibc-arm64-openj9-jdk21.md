---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-17 21:38:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 223 |
| Sample Rate | 3.72/sec |
| Health Score | 233% |
| Threads | 11 |
| Allocations | 165 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 15 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787016840 48
1787016845 48
1787016850 48
1787016855 43
1787016860 43
1787016865 43
1787016870 43
1787016875 43
1787016880 43
1787016885 43
1787016890 43
1787016895 43
1787016900 43
1787016905 48
1787016910 48
1787016915 48
1787016920 48
1787016925 48
1787016930 48
1787016935 48
```
</details>

---

