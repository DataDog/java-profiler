---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-14 13:34:30 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 772 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 11 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (5 unique values: 60-78 cores)</summary>

```
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
1776187802 78
1776187807 78
1776187812 78
```
</details>

---

