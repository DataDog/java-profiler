---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 06:36:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 12 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (3 unique values: 26-51 cores)</summary>

```
1795001552 26
1795001558 26
1795001563 26
1795001568 26
1795001573 26
1795001578 26
1795001583 26
1795001588 51
1795001593 51
1795001598 51
1795001603 39
1795001608 39
1795001613 39
1795001618 39
1795001623 39
1795001628 39
1795001633 39
1795001638 39
1795001643 39
1795001648 39
```
</details>

---

