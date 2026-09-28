---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-28 08:01:30 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 9 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (3 unique values: 19-24 cores)</summary>

```
1790596528 22
1790596533 22
1790596538 22
1790596543 22
1790596548 22
1790596553 22
1790596558 22
1790596563 22
1790596568 22
1790596573 22
1790596578 24
1790596583 24
1790596588 24
1790596593 24
1790596598 24
1790596603 24
1790596608 24
1790596613 24
1790596618 24
1790596623 19
```
</details>

---

