---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-14 13:34:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 824 |
| Sample Rate | 13.73/sec |
| Health Score | 858% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (7 unique values: 60-78 cores)</summary>

```
1776187702 66
1776187707 64
1776187712 64
1776187717 60
1776187722 60
1776187727 60
1776187732 63
1776187737 63
1776187742 63
1776187747 63
1776187752 63
1776187757 70
1776187762 70
1776187767 74
1776187772 74
1776187777 78
1776187782 78
1776187787 78
1776187792 78
1776187797 78
```
</details>

---

