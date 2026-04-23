---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-23 10:22:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 10 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 14 |
| Allocations | 109 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776953779 64
1776953784 64
1776953789 64
1776953794 64
1776953799 64
1776953804 64
1776953809 64
1776953814 64
1776953819 64
1776953824 64
1776953829 64
1776953834 64
1776953839 64
1776953844 64
1776953849 64
1776953854 64
1776953859 64
1776953864 64
1776953869 64
1776953874 64
```
</details>

---

