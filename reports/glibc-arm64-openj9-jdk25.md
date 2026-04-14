---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-14 14:58:16 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 248 |
| Sample Rate | 4.13/sec |
| Health Score | 258% |
| Threads | 12 |
| Allocations | 143 |

<details>
<summary>CPU Timeline (2 unique values: 60-64 cores)</summary>

```
1776192784 60
1776192789 60
1776192794 60
1776192799 60
1776192804 60
1776192809 60
1776192814 60
1776192819 60
1776192824 60
1776192829 60
1776192834 60
1776192839 60
1776192844 60
1776192849 60
1776192854 60
1776192859 60
1776192864 60
1776192869 60
1776192874 60
1776192879 60
```
</details>

---

