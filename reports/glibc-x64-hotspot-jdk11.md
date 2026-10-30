---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-30 13:48:57 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 761 |
| Sample Rate | 12.68/sec |
| Health Score | 792% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (3 unique values: 59-63 cores)</summary>

```
1793382235 63
1793382240 63
1793382245 61
1793382250 61
1793382255 59
1793382260 59
1793382265 59
1793382270 59
1793382275 59
1793382280 59
1793382285 59
1793382290 59
1793382295 59
1793382300 59
1793382305 59
1793382310 59
1793382315 59
1793382320 59
1793382325 59
1793382330 59
```
</details>

---

