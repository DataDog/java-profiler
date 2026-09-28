---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-28 08:01:31 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1000 |
| Sample Rate | 16.67/sec |
| Health Score | 1042% |
| Threads | 10 |
| Allocations | 567 |

<details>
<summary>CPU Timeline (2 unique values: 54-65 cores)</summary>

```
1790596538 54
1790596543 54
1790596548 54
1790596553 54
1790596558 54
1790596563 54
1790596568 54
1790596573 54
1790596578 54
1790596583 54
1790596588 54
1790596593 54
1790596598 54
1790596603 65
1790596608 65
1790596613 65
1790596618 65
1790596623 65
1790596628 65
1790596633 65
```
</details>

---

