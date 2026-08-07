---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-07 05:50:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 9 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (4 unique values: 86-96 cores)</summary>

```
1786095958 96
1786095963 96
1786095968 96
1786095973 96
1786095978 96
1786095983 96
1786095988 92
1786095993 92
1786095999 92
1786096004 92
1786096009 92
1786096014 92
1786096019 88
1786096024 88
1786096029 88
1786096034 88
1786096039 86
1786096044 86
1786096049 86
1786096054 86
```
</details>

---

