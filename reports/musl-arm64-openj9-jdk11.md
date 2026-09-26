---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-26 05:48:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 9 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 8 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (4 unique values: 14-29 cores)</summary>

```
1790415829 14
1790415834 14
1790415839 14
1790415844 14
1790415849 19
1790415854 19
1790415859 19
1790415864 19
1790415869 24
1790415874 24
1790415879 29
1790415884 29
1790415889 29
1790415894 29
1790415899 29
1790415904 29
1790415909 29
1790415914 29
1790415919 29
1790415924 29
```
</details>

---

