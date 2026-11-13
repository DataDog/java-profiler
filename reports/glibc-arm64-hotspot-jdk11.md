---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 13:50:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 7 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 11 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794595528 48
1794595533 48
1794595538 48
1794595543 48
1794595548 48
1794595553 48
1794595558 48
1794595563 48
1794595568 48
1794595573 48
1794595578 48
1794595583 48
1794595588 48
1794595593 48
1794595598 48
1794595603 48
1794595608 48
1794595613 48
1794595618 48
1794595623 48
```
</details>

---

