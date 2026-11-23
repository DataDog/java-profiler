---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 15:37:56 EST

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 10 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (4 unique values: 37-58 cores)</summary>

```
1795465961 55
1795465966 55
1795465971 55
1795465976 55
1795465982 55
1795465987 55
1795465992 55
1795465997 55
1795466002 57
1795466007 57
1795466012 57
1795466017 57
1795466022 57
1795466027 57
1795466032 57
1795466037 57
1795466042 57
1795466047 37
1795466052 37
1795466057 37
```
</details>

---

