---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-07 12:48:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 871 |
| Sample Rate | 14.52/sec |
| Health Score | 907% |
| Threads | 11 |
| Allocations | 417 |

<details>
<summary>CPU Timeline (3 unique values: 66-71 cores)</summary>

```
1791391390 69
1791391395 69
1791391400 69
1791391405 71
1791391410 71
1791391415 71
1791391420 71
1791391425 71
1791391430 71
1791391435 71
1791391440 71
1791391445 71
1791391450 71
1791391455 66
1791391460 66
1791391465 66
1791391470 66
1791391475 66
1791391480 66
1791391485 66
```
</details>

---

