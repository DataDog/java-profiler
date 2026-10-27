---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-27 07:00:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 8 |
| Allocations | 436 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 9 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (5 unique values: 10-31 cores)</summary>

```
1793098450 26
1793098455 26
1793098460 26
1793098465 26
1793098470 26
1793098475 26
1793098480 26
1793098485 28
1793098490 28
1793098495 28
1793098500 28
1793098505 11
1793098510 11
1793098515 11
1793098520 11
1793098525 11
1793098530 11
1793098535 31
1793098540 31
1793098545 31
```
</details>

---

