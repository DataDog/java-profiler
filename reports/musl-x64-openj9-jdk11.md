---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-15 15:54:58 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 723 |
| Sample Rate | 12.05/sec |
| Health Score | 753% |
| Threads | 9 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (3 unique values: 42-47 cores)</summary>

```
1776282569 43
1776282574 43
1776282579 43
1776282584 43
1776282589 43
1776282594 43
1776282599 43
1776282604 43
1776282609 43
1776282614 43
1776282619 43
1776282624 42
1776282629 42
1776282634 42
1776282639 42
1776282644 42
1776282649 43
1776282654 43
1776282659 47
1776282664 47
```
</details>

---

