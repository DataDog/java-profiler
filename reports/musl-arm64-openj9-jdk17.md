---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-18 08:24:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 7 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 7 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1787055553 48
1787055558 48
1787055563 48
1787055568 48
1787055573 48
1787055578 48
1787055583 48
1787055588 43
1787055593 43
1787055598 43
1787055603 43
1787055608 43
1787055613 43
1787055618 43
1787055623 43
1787055628 43
1787055633 43
1787055638 43
1787055644 43
1787055649 43
```
</details>

---

