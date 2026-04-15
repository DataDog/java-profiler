---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-04-15 14:28:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 152 |
| Sample Rate | 2.53/sec |
| Health Score | 158% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 357 |
| Sample Rate | 5.95/sec |
| Health Score | 372% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 71-83 cores)</summary>

```
1776277349 71
1776277354 73
1776277359 73
1776277364 73
1776277369 73
1776277374 81
1776277379 81
1776277384 81
1776277389 81
1776277394 81
1776277399 83
1776277404 83
1776277409 83
1776277414 83
1776277419 83
1776277424 83
1776277429 83
1776277434 81
1776277439 81
1776277444 81
```
</details>

---

