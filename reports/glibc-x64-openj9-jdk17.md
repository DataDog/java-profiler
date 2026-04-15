---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-15 15:54:57 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 10 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (3 unique values: 26-34 cores)</summary>

```
1776282588 26
1776282593 26
1776282598 30
1776282603 30
1776282608 30
1776282613 30
1776282618 30
1776282623 30
1776282628 34
1776282633 34
1776282638 34
1776282643 34
1776282648 34
1776282653 34
1776282658 34
1776282663 34
1776282668 34
1776282673 34
1776282678 34
1776282683 34
```
</details>

---

