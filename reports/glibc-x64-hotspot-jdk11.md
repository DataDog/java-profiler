---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-05 09:56:09 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 90 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 470 |
| Sample Rate | 7.83/sec |
| Health Score | 489% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 9 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (3 unique values: 90-94 cores)</summary>

```
1793890220 94
1793890225 92
1793890230 92
1793890235 92
1793890240 92
1793890245 92
1793890250 92
1793890255 92
1793890260 92
1793890265 92
1793890270 92
1793890275 92
1793890280 94
1793890285 94
1793890290 94
1793890295 94
1793890300 92
1793890305 92
1793890310 92
1793890315 92
```
</details>

---

