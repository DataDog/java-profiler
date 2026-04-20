---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-20 09:29:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 236 |
| Sample Rate | 3.93/sec |
| Health Score | 246% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 19-32 cores)</summary>

```
1776691509 19
1776691514 19
1776691519 19
1776691524 19
1776691529 19
1776691534 19
1776691539 19
1776691544 19
1776691549 19
1776691554 19
1776691559 19
1776691564 19
1776691569 19
1776691574 19
1776691579 19
1776691584 19
1776691589 19
1776691594 19
1776691599 32
1776691604 32
```
</details>

---

