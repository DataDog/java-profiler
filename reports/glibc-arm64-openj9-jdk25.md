---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-06 14:19:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 749 |
| Sample Rate | 12.48/sec |
| Health Score | 780% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (1 unique values: 28-28 cores)</summary>

```
1793992553 28
1793992558 28
1793992563 28
1793992568 28
1793992573 28
1793992578 28
1793992583 28
1793992588 28
1793992593 28
1793992598 28
1793992603 28
1793992608 28
1793992613 28
1793992618 28
1793992623 28
1793992628 28
1793992633 28
1793992638 28
1793992643 28
1793992648 28
```
</details>

---

