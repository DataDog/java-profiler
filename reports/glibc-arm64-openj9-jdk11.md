---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-17 05:46:52 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 402 |
| Sample Rate | 6.70/sec |
| Health Score | 419% |
| Threads | 10 |
| Allocations | 190 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 15 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (3 unique values: 42-48 cores)</summary>

```
1786959784 48
1786959789 48
1786959794 48
1786959799 48
1786959804 48
1786959809 48
1786959814 48
1786959819 48
1786959824 48
1786959829 48
1786959834 48
1786959839 48
1786959844 48
1786959849 48
1786959854 48
1786959859 48
1786959864 48
1786959869 48
1786959874 48
1786959879 48
```
</details>

---

