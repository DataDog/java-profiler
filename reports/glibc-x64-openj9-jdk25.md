---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-23 09:28:38 EDT

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
| CPU Cores (start) | 69 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 429 |
| Sample Rate | 7.15/sec |
| Health Score | 447% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (7 unique values: 34-74 cores)</summary>

```
1776950595 69
1776950600 69
1776950605 72
1776950610 72
1776950615 72
1776950620 72
1776950625 74
1776950630 74
1776950635 74
1776950640 74
1776950645 74
1776950650 74
1776950655 74
1776950660 70
1776950665 70
1776950670 70
1776950675 70
1776950680 70
1776950685 61
1776950690 61
```
</details>

---

