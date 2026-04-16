---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-16 08:50:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 9 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (4 unique values: 42-54 cores)</summary>

```
1776343514 42
1776343519 42
1776343524 42
1776343529 42
1776343534 42
1776343539 42
1776343544 42
1776343549 42
1776343554 42
1776343559 42
1776343564 42
1776343569 42
1776343574 42
1776343579 42
1776343584 42
1776343589 44
1776343594 44
1776343599 54
1776343604 54
1776343609 54
```
</details>

---

