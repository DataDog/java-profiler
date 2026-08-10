---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-10 15:31:41 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 12 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 12 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1786389991 51
1786389996 51
1786390001 51
1786390006 51
1786390011 51
1786390016 51
1786390021 51
1786390026 51
1786390031 51
1786390036 51
1786390041 51
1786390046 51
1786390051 51
1786390056 51
1786390061 51
1786390066 46
1786390071 46
1786390076 46
1786390081 46
1786390086 46
```
</details>

---

