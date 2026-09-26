---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-26 05:48:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (4 unique values: 14-29 cores)</summary>

```
1790415814 14
1790415819 14
1790415824 14
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
```
</details>

---

