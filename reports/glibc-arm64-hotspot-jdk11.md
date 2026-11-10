---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 13:30:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 13 |
| Allocations | 189 |

<details>
<summary>CPU Timeline (3 unique values: 34-52 cores)</summary>

```
1794334838 52
1794334843 52
1794334848 52
1794334853 52
1794334859 52
1794334864 52
1794334869 39
1794334874 39
1794334879 39
1794334884 39
1794334889 34
1794334894 34
1794334899 34
1794334904 34
1794334909 34
1794334914 34
1794334919 34
1794334924 34
1794334929 34
1794334934 34
```
</details>

---

