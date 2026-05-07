---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 10:58:42 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 290 |
| Sample Rate | 4.83/sec |
| Health Score | 302% |
| Threads | 11 |
| Allocations | 116 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778165592 64
1778165597 64
1778165602 64
1778165608 64
1778165613 64
1778165618 64
1778165623 64
1778165628 64
1778165633 64
1778165638 64
1778165643 64
1778165648 64
1778165653 64
1778165658 64
1778165663 64
1778165668 64
1778165673 64
1778165678 64
1778165683 64
1778165688 64
```
</details>

---

