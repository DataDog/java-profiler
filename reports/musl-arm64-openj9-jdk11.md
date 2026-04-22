---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-22 12:39:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 879 |
| Sample Rate | 14.65/sec |
| Health Score | 916% |
| Threads | 9 |
| Allocations | 441 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1776875631 64
1776875636 64
1776875641 64
1776875646 64
1776875651 64
1776875656 64
1776875661 64
1776875666 64
1776875671 64
1776875676 64
1776875681 64
1776875686 64
1776875691 64
1776875696 64
1776875701 64
1776875706 64
1776875711 64
1776875716 64
1776875721 64
1776875726 64
```
</details>

---

