---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 18:13:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 83 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 417 |
| Sample Rate | 6.95/sec |
| Health Score | 434% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 10 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (4 unique values: 69-87 cores)</summary>

```
1795129675 83
1795129680 83
1795129685 83
1795129690 83
1795129695 83
1795129700 83
1795129705 83
1795129710 87
1795129715 87
1795129720 69
1795129725 69
1795129730 69
1795129735 69
1795129740 69
1795129745 69
1795129750 69
1795129755 69
1795129760 69
1795129765 69
1795129770 69
```
</details>

---

