---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-14 13:34:30 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 346 |
| Sample Rate | 5.77/sec |
| Health Score | 361% |
| Threads | 8 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 465 |
| Sample Rate | 7.75/sec |
| Health Score | 484% |
| Threads | 9 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 14-26 cores)</summary>

```
1776187716 22
1776187721 22
1776187726 22
1776187731 22
1776187736 22
1776187741 22
1776187746 22
1776187751 22
1776187756 22
1776187761 22
1776187766 26
1776187771 26
1776187776 14
1776187781 14
1776187786 14
1776187791 14
1776187796 14
1776187801 14
1776187806 14
1776187811 14
```
</details>

---

