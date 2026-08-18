---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-18 08:24:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 10 |
| Allocations | 567 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1787055553 94
1787055558 94
1787055563 96
1787055568 96
1787055573 96
1787055578 96
1787055583 96
1787055588 96
1787055593 96
1787055598 96
1787055603 96
1787055608 96
1787055613 96
1787055618 96
1787055623 96
1787055628 96
1787055633 96
1787055639 96
1787055644 96
1787055649 96
```
</details>

---

