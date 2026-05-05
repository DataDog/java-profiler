---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-05 08:22:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 708 |
| Sample Rate | 11.80/sec |
| Health Score | 738% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1013 |
| Sample Rate | 16.88/sec |
| Health Score | 1055% |
| Threads | 11 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1777983470 32
1777983475 32
1777983480 32
1777983485 32
1777983491 32
1777983496 32
1777983501 32
1777983506 32
1777983511 32
1777983516 32
1777983521 32
1777983526 32
1777983531 32
1777983536 32
1777983541 32
1777983546 32
1777983551 32
1777983556 32
1777983561 32
1777983566 32
```
</details>

---

