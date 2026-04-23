---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-23 10:04:16 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 604 |
| Sample Rate | 10.07/sec |
| Health Score | 629% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 884 |
| Sample Rate | 14.73/sec |
| Health Score | 921% |
| Threads | 9 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (6 unique values: 77-84 cores)</summary>

```
1776952760 79
1776952765 80
1776952770 80
1776952775 80
1776952780 80
1776952785 80
1776952790 80
1776952795 84
1776952800 84
1776952805 84
1776952810 84
1776952815 82
1776952820 82
1776952825 82
1776952830 82
1776952835 82
1776952840 81
1776952845 81
1776952851 81
1776952856 81
```
</details>

---

