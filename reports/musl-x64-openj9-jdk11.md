---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-15 12:49:15 EDT

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 726 |
| Sample Rate | 12.10/sec |
| Health Score | 756% |
| Threads | 9 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (3 unique values: 63-68 cores)</summary>

```
1776271511 68
1776271516 68
1776271521 68
1776271526 65
1776271531 65
1776271536 65
1776271541 65
1776271546 65
1776271551 65
1776271556 65
1776271561 65
1776271566 65
1776271571 65
1776271576 63
1776271581 63
1776271586 63
1776271591 63
1776271596 63
1776271601 63
1776271606 63
```
</details>

---

