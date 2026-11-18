---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 06:36:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 11 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795001518 59
1795001523 59
1795001528 59
1795001533 59
1795001538 59
1795001543 59
1795001548 59
1795001553 59
1795001558 59
1795001563 59
1795001568 59
1795001573 59
1795001578 59
1795001583 59
1795001588 59
1795001593 59
1795001598 59
1795001603 59
1795001608 59
1795001613 59
```
</details>

---

