---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-03 11:25:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 31-48 cores)</summary>

```
1793722818 48
1793722823 48
1793722828 48
1793722834 48
1793722839 48
1793722844 48
1793722849 48
1793722854 48
1793722859 48
1793722864 48
1793722869 48
1793722874 31
1793722879 31
1793722884 31
1793722889 31
1793722894 31
1793722899 31
1793722904 31
1793722909 31
1793722914 31
```
</details>

---

