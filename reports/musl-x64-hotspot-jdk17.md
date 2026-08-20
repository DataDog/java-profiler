---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-20 12:17:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 9 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 855 |
| Sample Rate | 14.25/sec |
| Health Score | 891% |
| Threads | 11 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (4 unique values: 82-88 cores)</summary>

```
1787242355 88
1787242360 88
1787242365 88
1787242370 88
1787242375 88
1787242380 86
1787242385 86
1787242390 86
1787242395 86
1787242400 86
1787242405 86
1787242410 84
1787242415 84
1787242420 84
1787242425 84
1787242430 84
1787242435 82
1787242440 82
1787242445 84
1787242450 84
```
</details>

---

