---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-18 08:24:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 10 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1787055553 94
1787055558 94
1787055563 94
1787055568 96
1787055573 96
1787055578 94
1787055583 94
1787055588 94
1787055593 94
1787055598 94
1787055603 94
1787055608 94
1787055613 94
1787055618 94
1787055623 94
1787055628 94
1787055633 94
1787055638 92
1787055643 92
1787055648 92
```
</details>

---

