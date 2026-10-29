---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-29 11:50:43 EDT

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 9 |
| Allocations | 50 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 13 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (4 unique values: 20-24 cores)</summary>

```
1793288573 21
1793288578 21
1793288583 21
1793288588 21
1793288593 21
1793288598 21
1793288603 21
1793288608 21
1793288613 21
1793288618 24
1793288623 24
1793288628 22
1793288633 22
1793288638 22
1793288643 22
1793288648 22
1793288653 22
1793288658 22
1793288663 20
1793288668 20
```
</details>

---

