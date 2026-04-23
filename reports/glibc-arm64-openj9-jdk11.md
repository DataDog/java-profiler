---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-23 15:03:16 EDT

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
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 8 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776970773 64
1776970778 64
1776970783 64
1776970788 64
1776970793 64
1776970798 64
1776970803 64
1776970808 64
1776970813 64
1776970818 64
1776970823 64
1776970828 64
1776970833 64
1776970838 64
1776970843 64
1776970848 64
1776970853 64
1776970858 64
1776970863 64
1776970868 64
```
</details>

---

