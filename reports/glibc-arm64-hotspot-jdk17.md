---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-07 19:05:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
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
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 8 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 192 |
| Sample Rate | 3.20/sec |
| Health Score | 200% |
| Threads | 12 |
| Allocations | 148 |

<details>
<summary>CPU Timeline (3 unique values: 57-64 cores)</summary>

```
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
1778194939 64
1778194944 64
1778194949 57
```
</details>

---

