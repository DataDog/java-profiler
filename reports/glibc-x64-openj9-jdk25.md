---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-26 16:34:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 375 |
| Sample Rate | 6.25/sec |
| Health Score | 391% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 667 |
| Sample Rate | 11.12/sec |
| Health Score | 695% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (4 unique values: 54-62 cores)</summary>

```
1777235412 62
1777235417 60
1777235422 60
1777235427 60
1777235432 60
1777235437 60
1777235442 60
1777235447 62
1777235452 62
1777235457 62
1777235462 62
1777235467 57
1777235472 57
1777235477 54
1777235482 54
1777235487 54
1777235492 54
1777235497 54
1777235502 54
1777235507 54
```
</details>

---

