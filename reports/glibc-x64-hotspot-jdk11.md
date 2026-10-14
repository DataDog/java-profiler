---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-14 11:49:32 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 9 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (2 unique values: 54-56 cores)</summary>

```
1791992508 54
1791992513 54
1791992518 54
1791992523 54
1791992528 54
1791992533 54
1791992538 54
1791992543 56
1791992548 56
1791992553 56
1791992558 56
1791992563 54
1791992568 54
1791992573 54
1791992578 54
1791992583 54
1791992588 54
1791992593 54
1791992598 54
1791992603 56
```
</details>

---

