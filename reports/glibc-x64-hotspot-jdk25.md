---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-15 15:54:56 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 378 |
| Sample Rate | 6.30/sec |
| Health Score | 394% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 646 |
| Sample Rate | 10.77/sec |
| Health Score | 673% |
| Threads | 10 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (4 unique values: 59-94 cores)</summary>

```
1776282588 59
1776282593 59
1776282598 59
1776282603 59
1776282608 59
1776282613 59
1776282618 59
1776282623 63
1776282628 63
1776282633 63
1776282638 63
1776282643 63
1776282648 63
1776282653 63
1776282658 94
1776282663 94
1776282668 94
1776282673 94
1776282678 94
1776282683 94
```
</details>

---

