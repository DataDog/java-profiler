---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 06:36:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 11 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1795001518 34
1795001523 34
1795001528 34
1795001533 34
1795001538 34
1795001543 34
1795001548 34
1795001553 34
1795001558 34
1795001563 32
1795001568 32
1795001573 32
1795001578 32
1795001583 32
1795001588 32
1795001593 32
1795001598 32
1795001603 32
1795001608 32
1795001613 32
```
</details>

---

