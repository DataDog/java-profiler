---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-11 09:02:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 11 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (4 unique values: 86-91 cores)</summary>

```
1794405523 90
1794405528 90
1794405533 90
1794405538 90
1794405543 90
1794405548 90
1794405553 89
1794405558 89
1794405563 89
1794405568 91
1794405573 91
1794405578 91
1794405583 91
1794405588 91
1794405593 91
1794405598 91
1794405603 91
1794405608 91
1794405613 91
1794405618 91
```
</details>

---

