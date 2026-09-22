---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-22 12:32:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790093879 50
1790093884 50
1790093889 50
1790093894 50
1790093899 50
1790093904 50
1790093909 50
1790093914 50
1790093919 50
1790093924 50
1790093929 50
1790093934 50
1790093939 50
1790093944 50
1790093949 50
1790093954 50
1790093959 50
1790093964 50
1790093969 50
1790093974 50
```
</details>

---

