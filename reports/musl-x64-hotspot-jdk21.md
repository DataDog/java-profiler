---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-08 12:33:21 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 8 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 797 |
| Sample Rate | 13.28/sec |
| Health Score | 830% |
| Threads | 10 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (3 unique values: 25-29 cores)</summary>

```
1791476919 29
1791476924 29
1791476929 29
1791476934 27
1791476939 27
1791476944 27
1791476949 25
1791476954 25
1791476959 25
1791476964 25
1791476969 25
1791476974 25
1791476979 25
1791476984 25
1791476989 27
1791476995 27
1791477000 27
1791477005 27
1791477010 27
1791477015 27
```
</details>

---

