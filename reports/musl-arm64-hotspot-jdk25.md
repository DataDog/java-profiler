---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-26 11:06:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 307 |
| Sample Rate | 5.12/sec |
| Health Score | 320% |
| Threads | 14 |
| Allocations | 147 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793026804 46
1793026809 46
1793026814 46
1793026819 46
1793026824 46
1793026829 46
1793026834 46
1793026839 46
1793026844 51
1793026849 51
1793026854 51
1793026859 51
1793026864 46
1793026869 46
1793026874 46
1793026879 46
1793026884 46
1793026889 46
1793026894 46
1793026899 46
```
</details>

---

