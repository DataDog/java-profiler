---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-30 08:24:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 952 |
| Sample Rate | 15.87/sec |
| Health Score | 992% |
| Threads | 9 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (3 unique values: 37-39 cores)</summary>

```
1790770739 39
1790770744 39
1790770749 39
1790770754 39
1790770759 37
1790770764 37
1790770769 37
1790770774 37
1790770779 37
1790770784 37
1790770789 37
1790770794 37
1790770799 37
1790770804 37
1790770809 39
1790770814 39
1790770819 39
1790770824 39
1790770829 39
1790770834 39
```
</details>

---

