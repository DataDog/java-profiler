---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-06 05:37:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 8 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 11 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (4 unique values: 34-40 cores)</summary>

```
1791279049 40
1791279054 40
1791279059 40
1791279064 40
1791279069 39
1791279074 39
1791279079 39
1791279084 34
1791279089 34
1791279094 34
1791279099 34
1791279104 34
1791279109 34
1791279114 34
1791279119 34
1791279124 35
1791279129 35
1791279134 35
1791279139 35
1791279144 35
```
</details>

---

