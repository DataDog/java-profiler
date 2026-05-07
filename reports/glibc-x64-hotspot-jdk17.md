---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-07 07:09:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 765 |
| Sample Rate | 12.75/sec |
| Health Score | 797% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (5 unique values: 74-82 cores)</summary>

```
1778151772 80
1778151777 74
1778151782 74
1778151787 74
1778151792 74
1778151797 74
1778151802 75
1778151807 75
1778151812 75
1778151817 75
1778151822 75
1778151827 75
1778151832 75
1778151837 75
1778151842 75
1778151847 75
1778151852 77
1778151857 77
1778151862 77
1778151867 77
```
</details>

---

