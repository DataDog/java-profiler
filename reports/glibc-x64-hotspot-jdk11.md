---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-20 09:41:43 EDT

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
| CPU Cores (start) | 77 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 9 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (3 unique values: 77-81 cores)</summary>

```
1787233014 77
1787233019 79
1787233024 79
1787233029 79
1787233034 79
1787233039 79
1787233044 79
1787233049 79
1787233054 79
1787233059 81
1787233064 81
1787233069 81
1787233074 81
1787233079 81
1787233084 81
1787233089 81
1787233094 81
1787233099 81
1787233104 81
1787233109 81
```
</details>

---

