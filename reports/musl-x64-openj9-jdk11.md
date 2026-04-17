---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-17 10:21:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 546 |
| Sample Rate | 9.10/sec |
| Health Score | 569% |
| Threads | 8 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 867 |
| Sample Rate | 14.45/sec |
| Health Score | 903% |
| Threads | 10 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (5 unique values: 81-88 cores)</summary>

```
1776435278 84
1776435283 84
1776435288 84
1776435293 84
1776435298 84
1776435303 81
1776435308 81
1776435313 81
1776435318 81
1776435323 81
1776435328 81
1776435333 83
1776435338 83
1776435343 83
1776435348 88
1776435353 88
1776435358 88
1776435363 84
1776435368 84
1776435373 86
```
</details>

---

