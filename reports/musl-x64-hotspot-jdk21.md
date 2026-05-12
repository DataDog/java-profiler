---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-12 05:49:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 9 |
| Allocations | 412 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 719 |
| Sample Rate | 11.98/sec |
| Health Score | 749% |
| Threads | 10 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (2 unique values: 18-20 cores)</summary>

```
1778579054 18
1778579059 18
1778579064 18
1778579069 18
1778579074 18
1778579079 18
1778579084 18
1778579089 20
1778579094 20
1778579099 20
1778579104 20
1778579109 20
1778579114 20
1778579119 20
1778579124 20
1778579129 20
1778579134 20
1778579139 20
1778579144 20
1778579149 18
```
</details>

---

