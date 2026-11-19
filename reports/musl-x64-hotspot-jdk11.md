---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 18:13:02 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 8 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 8 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (3 unique values: 59-85 cores)</summary>

```
1795129640 85
1795129645 85
1795129650 59
1795129655 59
1795129660 59
1795129665 59
1795129670 59
1795129675 59
1795129680 61
1795129685 61
1795129690 61
1795129695 61
1795129700 61
1795129705 61
1795129710 61
1795129715 61
1795129720 61
1795129725 61
1795129730 61
1795129735 61
```
</details>

---

