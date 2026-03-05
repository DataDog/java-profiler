---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-03-05 13:29:12 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 600 |
| Sample Rate | 10.00/sec |
| Health Score | 625% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 830 |
| Sample Rate | 13.83/sec |
| Health Score | 864% |
| Threads | 10 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (4 unique values: 49-86 cores)</summary>

```
1772734994 56
1772734999 56
1772735004 56
1772735009 56
1772735014 56
1772735019 49
1772735024 49
1772735029 84
1772735034 84
1772735039 84
1772735044 84
1772735049 84
1772735054 84
1772735059 84
1772735064 86
1772735069 86
1772735074 86
1772735079 86
1772735084 84
1772735089 84
```
</details>

---

