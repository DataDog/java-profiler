---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-20 11:41:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 7 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1776699115 64
1776699120 64
1776699125 64
1776699130 64
1776699135 64
1776699140 64
1776699145 64
1776699150 64
1776699155 64
1776699160 64
1776699165 64
1776699170 64
1776699175 59
1776699180 59
1776699185 59
1776699190 59
1776699195 59
1776699200 59
1776699205 59
1776699210 59
```
</details>

---

