---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-23 05:53:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 9 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 829 |
| Sample Rate | 13.82/sec |
| Health Score | 864% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (4 unique values: 69-76 cores)</summary>

```
1776937734 71
1776937739 71
1776937744 71
1776937749 71
1776937754 71
1776937759 71
1776937764 71
1776937769 76
1776937774 76
1776937779 76
1776937784 76
1776937789 73
1776937794 73
1776937799 73
1776937804 73
1776937809 73
1776937815 73
1776937820 73
1776937825 73
1776937830 69
```
</details>

---

