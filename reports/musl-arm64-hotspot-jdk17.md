---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-24 00:59:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (3 unique values: 9-14 cores)</summary>

```
1790225613 9
1790225618 9
1790225623 9
1790225628 9
1790225633 9
1790225638 9
1790225643 9
1790225648 9
1790225653 14
1790225658 14
1790225663 12
1790225668 12
1790225673 12
1790225678 12
1790225683 12
1790225688 12
1790225694 12
1790225699 12
1790225704 12
1790225709 12
```
</details>

---

