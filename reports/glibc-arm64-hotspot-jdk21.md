---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 15:37:56 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 397 |
| Sample Rate | 6.62/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 12 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (2 unique values: 18-49 cores)</summary>

```
1795465987 49
1795465992 49
1795465997 49
1795466002 49
1795466007 49
1795466012 49
1795466017 49
1795466022 18
1795466027 18
1795466032 18
1795466037 18
1795466042 18
1795466047 18
1795466052 18
1795466057 18
1795466062 18
1795466067 18
1795466072 18
1795466077 18
1795466082 18
```
</details>

---

