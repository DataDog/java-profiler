---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-22 03:53:36 EDT

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
| CPU Cores (start) | 90 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 973 |
| Sample Rate | 16.22/sec |
| Health Score | 1014% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (3 unique values: 90-96 cores)</summary>

```
1776844227 90
1776844232 90
1776844237 94
1776844242 94
1776844247 94
1776844252 94
1776844257 94
1776844262 94
1776844267 94
1776844272 94
1776844277 94
1776844282 94
1776844287 94
1776844292 94
1776844297 94
1776844302 96
1776844307 96
1776844312 96
1776844317 96
1776844322 96
```
</details>

---

