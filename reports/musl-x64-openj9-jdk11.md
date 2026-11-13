---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 13:50:10 EST

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 547 |
| Sample Rate | 9.12/sec |
| Health Score | 570% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 745 |
| Sample Rate | 12.42/sec |
| Health Score | 776% |
| Threads | 9 |
| Allocations | 572 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1794595523 28
1794595528 28
1794595533 28
1794595538 28
1794595543 28
1794595548 28
1794595553 28
1794595558 28
1794595563 28
1794595568 28
1794595573 28
1794595578 28
1794595583 28
1794595588 28
1794595593 28
1794595598 28
1794595603 28
1794595608 28
1794595613 30
1794595618 30
```
</details>

---

