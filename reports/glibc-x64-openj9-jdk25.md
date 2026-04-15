---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-15 11:14:27 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 10 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (3 unique values: 87-93 cores)</summary>

```
1776265702 89
1776265707 87
1776265712 87
1776265717 87
1776265722 87
1776265727 87
1776265732 87
1776265737 87
1776265742 89
1776265747 89
1776265752 89
1776265757 89
1776265762 89
1776265767 89
1776265772 89
1776265777 89
1776265782 87
1776265787 87
1776265792 87
1776265797 93
```
</details>

---

