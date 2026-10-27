---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-27 19:15:09 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (3 unique values: 91-96 cores)</summary>

```
1793142574 91
1793142579 91
1793142584 91
1793142589 91
1793142594 91
1793142599 91
1793142604 91
1793142609 96
1793142614 96
1793142619 96
1793142624 96
1793142629 96
1793142634 96
1793142639 96
1793142644 96
1793142650 96
1793142655 96
1793142660 94
1793142665 94
1793142670 94
```
</details>

---

