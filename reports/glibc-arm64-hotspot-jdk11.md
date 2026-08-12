---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-12 05:47:58 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 14 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1786527827 43
1786527832 43
1786527837 43
1786527842 43
1786527847 43
1786527852 43
1786527857 43
1786527862 43
1786527867 43
1786527872 43
1786527877 43
1786527882 38
1786527887 38
1786527892 38
1786527897 38
1786527902 38
1786527907 38
1786527912 38
1786527917 38
1786527922 43
```
</details>

---

