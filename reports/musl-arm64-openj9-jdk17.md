---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-20 09:07:13 EDT

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
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 9 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 10 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (3 unique values: 59-64 cores)</summary>

```
1787230896 64
1787230901 64
1787230906 64
1787230911 64
1787230916 64
1787230921 61
1787230926 61
1787230931 61
1787230936 61
1787230941 61
1787230946 61
1787230951 61
1787230956 61
1787230961 61
1787230966 61
1787230971 61
1787230976 61
1787230981 61
1787230986 61
1787230991 61
```
</details>

---

