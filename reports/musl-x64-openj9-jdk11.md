---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-28 08:01:33 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 16 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 814 |
| Sample Rate | 13.57/sec |
| Health Score | 848% |
| Threads | 8 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (1 unique values: 16-16 cores)</summary>

```
1790596523 16
1790596528 16
1790596533 16
1790596538 16
1790596543 16
1790596548 16
1790596553 16
1790596558 16
1790596563 16
1790596568 16
1790596573 16
1790596578 16
1790596583 16
1790596588 16
1790596593 16
1790596598 16
1790596604 16
1790596609 16
1790596614 16
1790596619 16
```
</details>

---

