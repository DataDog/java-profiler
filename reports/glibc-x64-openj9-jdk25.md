---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-11 05:49:17 EDT

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 12 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (6 unique values: 70-84 cores)</summary>

```
1786441483 70
1786441488 70
1786441493 70
1786441498 70
1786441503 70
1786441508 70
1786441513 78
1786441518 78
1786441523 76
1786441528 76
1786441533 76
1786441538 76
1786441544 76
1786441549 76
1786441554 76
1786441559 76
1786441564 82
1786441569 82
1786441574 80
1786441579 80
```
</details>

---

