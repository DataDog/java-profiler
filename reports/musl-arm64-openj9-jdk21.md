---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-15 12:49:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 12 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 9 |
| Allocations | 16 |

<details>
<summary>CPU Timeline (3 unique values: 58-64 cores)</summary>

```
1776271514 58
1776271519 58
1776271524 60
1776271529 60
1776271534 60
1776271539 60
1776271544 60
1776271549 60
1776271554 60
1776271559 60
1776271564 60
1776271569 60
1776271574 64
1776271579 64
1776271584 64
1776271589 64
1776271594 64
1776271599 64
1776271604 64
1776271609 64
```
</details>

---

