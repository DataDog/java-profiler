---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-15 14:59:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 396 |
| Sample Rate | 6.60/sec |
| Health Score | 412% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (5 unique values: 17-27 cores)</summary>

```
1776279108 25
1776279113 25
1776279118 25
1776279123 25
1776279128 27
1776279133 27
1776279138 23
1776279143 23
1776279148 23
1776279153 23
1776279158 23
1776279163 23
1776279168 23
1776279173 23
1776279178 19
1776279183 19
1776279188 19
1776279193 19
1776279198 19
1776279203 19
```
</details>

---

