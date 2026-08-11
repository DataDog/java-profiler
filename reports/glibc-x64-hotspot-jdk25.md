---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-11 09:27:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 8 |
| Allocations | 430 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 11 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (3 unique values: 60-64 cores)</summary>

```
1786454530 60
1786454535 60
1786454540 60
1786454545 60
1786454550 60
1786454555 60
1786454560 60
1786454565 60
1786454570 64
1786454575 64
1786454580 64
1786454585 64
1786454590 62
1786454595 62
1786454600 62
1786454605 62
1786454610 62
1786454615 62
1786454620 62
1786454626 62
```
</details>

---

