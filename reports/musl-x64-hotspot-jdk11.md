---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 12:32:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 765 |
| Sample Rate | 12.75/sec |
| Health Score | 797% |
| Threads | 10 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794850019 32
1794850024 32
1794850029 32
1794850034 32
1794850039 32
1794850044 32
1794850049 32
1794850054 32
1794850059 32
1794850064 32
1794850069 32
1794850074 32
1794850079 32
1794850084 32
1794850089 32
1794850094 32
1794850099 32
1794850104 32
1794850109 32
1794850114 32
```
</details>

---

