---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 05:28:05 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 13 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (3 unique values: 29-34 cores)</summary>

```
1795429485 29
1795429490 29
1795429495 29
1795429500 29
1795429505 29
1795429510 29
1795429515 29
1795429520 29
1795429525 29
1795429530 34
1795429535 34
1795429540 30
1795429545 30
1795429550 30
1795429555 30
1795429561 30
1795429566 30
1795429571 30
1795429576 30
1795429581 30
```
</details>

---

