---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-18 09:21:53 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 832 |
| Sample Rate | 13.87/sec |
| Health Score | 867% |
| Threads | 9 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (2 unique values: 47-49 cores)</summary>

```
1787059039 49
1787059044 49
1787059049 49
1787059054 49
1787059059 49
1787059064 49
1787059069 49
1787059074 49
1787059079 49
1787059085 49
1787059090 49
1787059095 49
1787059100 49
1787059105 49
1787059110 49
1787059115 47
1787059120 47
1787059125 47
1787059130 47
1787059135 47
```
</details>

---

