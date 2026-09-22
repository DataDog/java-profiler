---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-22 12:32:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
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
| CPU Samples | 233 |
| Sample Rate | 3.88/sec |
| Health Score | 242% |
| Threads | 10 |
| Allocations | 145 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 13 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790093854 50
1790093859 50
1790093864 50
1790093869 50
1790093874 50
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
```
</details>

---

