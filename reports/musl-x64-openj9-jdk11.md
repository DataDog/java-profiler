---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-23 09:28:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 998 |
| Sample Rate | 16.63/sec |
| Health Score | 1039% |
| Threads | 11 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (4 unique values: 80-93 cores)</summary>

```
1776950575 93
1776950580 93
1776950585 93
1776950590 93
1776950595 93
1776950600 93
1776950605 93
1776950610 93
1776950615 93
1776950620 93
1776950625 93
1776950630 93
1776950635 93
1776950640 93
1776950645 93
1776950650 87
1776950655 87
1776950660 89
1776950665 89
1776950670 89
```
</details>

---

