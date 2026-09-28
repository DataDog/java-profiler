---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-28 08:01:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 11 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (4 unique values: 17-24 cores)</summary>

```
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
1790596618 19
1790596623 19
1790596628 19
1790596633 19
1790596638 19
1790596644 22
1790596649 22
```
</details>

---

