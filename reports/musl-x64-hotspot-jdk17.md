---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-24 00:59:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 7 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 9 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (2 unique values: 7-17 cores)</summary>

```
1790225604 7
1790225609 7
1790225614 7
1790225619 7
1790225624 7
1790225629 7
1790225634 7
1790225639 7
1790225644 7
1790225649 7
1790225654 7
1790225659 7
1790225664 7
1790225669 7
1790225674 7
1790225679 7
1790225684 7
1790225689 7
1790225694 7
1790225699 17
```
</details>

---

