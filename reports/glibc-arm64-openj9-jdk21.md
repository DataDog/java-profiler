---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-07 19:05:09 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 42 |
| Sample Rate | 0.70/sec |
| Health Score | 44% |
| Threads | 7 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 10 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (2 unique values: 57-64 cores)</summary>

```
1778194839 64
1778194844 64
1778194849 64
1778194854 64
1778194859 64
1778194864 64
1778194869 64
1778194874 64
1778194879 64
1778194884 64
1778194889 64
1778194894 64
1778194899 64
1778194904 64
1778194909 64
1778194914 64
1778194919 64
1778194924 64
1778194929 64
1778194934 64
```
</details>

---

