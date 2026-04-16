---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-16 08:50:24 EDT

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
| CPU Cores (start) | 73 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 825 |
| Sample Rate | 13.75/sec |
| Health Score | 859% |
| Threads | 9 |
| Allocations | 547 |

<details>
<summary>CPU Timeline (6 unique values: 64-88 cores)</summary>

```
1776343514 73
1776343519 73
1776343524 73
1776343529 73
1776343534 73
1776343539 73
1776343544 73
1776343549 73
1776343554 75
1776343559 75
1776343564 79
1776343569 79
1776343574 79
1776343579 79
1776343584 79
1776343589 79
1776343594 79
1776343599 79
1776343604 79
1776343609 79
```
</details>

---

