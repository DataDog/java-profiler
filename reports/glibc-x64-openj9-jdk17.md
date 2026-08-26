---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-26 07:12:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 76-91 cores)</summary>

```
1787742470 91
1787742475 91
1787742480 91
1787742485 91
1787742490 91
1787742495 91
1787742500 91
1787742505 91
1787742510 76
1787742515 76
1787742520 76
1787742525 76
1787742531 76
1787742536 76
1787742541 76
1787742546 76
1787742551 76
1787742556 76
1787742561 76
1787742566 76
```
</details>

---

