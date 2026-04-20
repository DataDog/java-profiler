---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-20 04:41:21 EDT

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 13 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 8 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 13-17 cores)</summary>

```
1776674135 17
1776674140 17
1776674145 17
1776674150 17
1776674155 17
1776674160 17
1776674165 17
1776674170 17
1776674175 13
1776674180 13
1776674185 13
1776674190 13
1776674195 13
1776674200 13
1776674205 13
1776674210 13
1776674215 13
1776674220 13
1776674225 13
1776674230 13
```
</details>

---

