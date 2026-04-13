---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-13 01:30:54 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 8 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 756 |
| Sample Rate | 12.60/sec |
| Health Score | 787% |
| Threads | 9 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1776058066 48
1776058071 48
1776058076 48
1776058081 48
1776058086 48
1776058091 48
1776058096 43
1776058101 43
1776058106 43
1776058111 43
1776058116 43
1776058121 43
1776058126 43
1776058131 43
1776058136 43
1776058142 43
1776058147 43
1776058152 43
1776058157 43
1776058162 43
```
</details>

---

