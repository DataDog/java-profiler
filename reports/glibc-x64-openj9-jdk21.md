---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-23 14:32:12 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 625 |
| Sample Rate | 10.42/sec |
| Health Score | 651% |
| Threads | 10 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (3 unique values: 88-93 cores)</summary>

```
1776968724 88
1776968729 88
1776968734 88
1776968739 88
1776968744 88
1776968749 88
1776968754 88
1776968759 88
1776968764 88
1776968769 88
1776968774 88
1776968779 93
1776968784 93
1776968789 91
1776968794 91
1776968799 91
1776968804 93
1776968809 93
1776968814 93
1776968819 93
```
</details>

---

