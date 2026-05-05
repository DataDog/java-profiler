---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-05 08:22:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 9 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 10 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (3 unique values: 52-62 cores)</summary>

```
1777983471 52
1777983476 52
1777983481 52
1777983486 52
1777983491 57
1777983496 57
1777983501 57
1777983506 57
1777983511 57
1777983516 57
1777983521 62
1777983526 62
1777983531 62
1777983536 62
1777983542 62
1777983547 62
1777983552 62
1777983557 62
1777983562 62
1777983567 62
```
</details>

---

