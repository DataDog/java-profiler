---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-21 10:50:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 186 |
| Sample Rate | 3.10/sec |
| Health Score | 194% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 229 |
| Sample Rate | 3.82/sec |
| Health Score | 239% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 41-54 cores)</summary>

```
1776782617 41
1776782622 41
1776782627 41
1776782632 54
1776782637 54
1776782642 54
1776782647 54
1776782652 54
1776782657 54
1776782662 54
1776782667 54
1776782672 54
1776782677 54
1776782682 54
1776782687 54
1776782692 54
1776782698 54
1776782703 54
1776782708 54
1776782713 54
```
</details>

---

