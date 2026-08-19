---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-19 05:51:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 85 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 37 |
| Sample Rate | 0.62/sec |
| Health Score | 39% |
| Threads | 8 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787132869 64
1787132874 64
1787132879 64
1787132884 64
1787132889 64
1787132894 64
1787132899 64
1787132904 64
1787132909 64
1787132914 64
1787132919 64
1787132924 64
1787132929 64
1787132934 64
1787132939 64
1787132944 64
1787132949 64
1787132954 64
1787132959 64
1787132964 64
```
</details>

---

