---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-22 00:56:48 EDT

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 8 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 11-48 cores)</summary>

```
1790052799 11
1790052804 11
1790052809 11
1790052814 11
1790052819 11
1790052824 11
1790052829 11
1790052834 11
1790052839 11
1790052844 11
1790052849 11
1790052854 48
1790052859 48
1790052864 11
1790052869 11
1790052874 11
1790052879 11
1790052884 11
1790052889 11
1790052894 11
```
</details>

---

