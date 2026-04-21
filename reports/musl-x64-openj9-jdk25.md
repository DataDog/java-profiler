---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-21 10:50:26 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 394 |
| Sample Rate | 6.57/sec |
| Health Score | 411% |
| Threads | 8 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 9 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 31-32 cores)</summary>

```
1776782621 31
1776782626 31
1776782631 31
1776782636 31
1776782641 31
1776782646 31
1776782651 32
1776782656 32
1776782661 32
1776782666 32
1776782671 32
1776782676 32
1776782681 32
1776782686 32
1776782691 32
1776782696 32
1776782701 32
1776782706 32
1776782711 32
1776782716 32
```
</details>

---

