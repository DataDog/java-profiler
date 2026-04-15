---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-15 11:14:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 10 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776265578 64
1776265583 64
1776265588 64
1776265593 64
1776265599 64
1776265604 64
1776265609 64
1776265614 64
1776265619 64
1776265624 64
1776265629 64
1776265634 64
1776265639 59
1776265644 59
1776265649 59
1776265654 59
1776265659 59
1776265664 59
1776265669 59
1776265674 59
```
</details>

---

