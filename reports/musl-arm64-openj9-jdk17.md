---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-24 08:33:45 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 333 |
| Sample Rate | 5.55/sec |
| Health Score | 347% |
| Threads | 13 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (2 unique values: 56-64 cores)</summary>

```
1777033637 64
1777033642 64
1777033647 64
1777033652 64
1777033657 64
1777033662 64
1777033667 64
1777033672 64
1777033677 64
1777033682 64
1777033687 64
1777033692 64
1777033697 64
1777033702 64
1777033707 64
1777033712 64
1777033717 64
1777033722 64
1777033727 64
1777033732 64
```
</details>

---

