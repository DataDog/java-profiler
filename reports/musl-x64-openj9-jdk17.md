---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 10:09:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 10 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 677 |
| Sample Rate | 11.28/sec |
| Health Score | 705% |
| Threads | 9 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (3 unique values: 38-42 cores)</summary>

```
1794495876 38
1794495881 38
1794495886 38
1794495891 38
1794495896 38
1794495901 38
1794495906 38
1794495911 38
1794495916 40
1794495921 40
1794495926 40
1794495931 40
1794495936 42
1794495941 42
1794495946 42
1794495951 42
1794495956 42
1794495961 42
1794495966 42
1794495971 42
```
</details>

---

