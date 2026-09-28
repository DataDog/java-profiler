---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-28 09:39:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 6 |
| CPU Cores (end) | 11 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 9 |
| Allocations | 417 |

<details>
<summary>CPU Timeline (2 unique values: 6-11 cores)</summary>

```
1790602560 6
1790602565 6
1790602570 6
1790602575 6
1790602580 6
1790602585 6
1790602590 6
1790602595 6
1790602600 6
1790602605 6
1790602610 6
1790602615 11
1790602620 11
1790602625 11
1790602630 11
1790602635 11
1790602640 11
1790602645 11
1790602650 11
1790602655 11
```
</details>

---

