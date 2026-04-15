---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-15 13:31:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 13 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776274061 64
1776274066 64
1776274071 64
1776274076 64
1776274081 64
1776274086 64
1776274091 64
1776274096 64
1776274101 64
1776274106 64
1776274111 64
1776274116 64
1776274121 64
1776274126 64
1776274131 64
1776274136 64
1776274141 64
1776274146 64
1776274151 64
1776274156 64
```
</details>

---

