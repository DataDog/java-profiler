---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-15 08:57:52 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 11 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (4 unique values: 31-43 cores)</summary>

```
1776257521 43
1776257526 43
1776257531 43
1776257536 43
1776257541 43
1776257546 43
1776257551 43
1776257556 43
1776257561 43
1776257566 43
1776257571 43
1776257576 43
1776257581 42
1776257586 42
1776257591 42
1776257596 42
1776257601 35
1776257606 35
1776257611 31
1776257616 31
```
</details>

---

