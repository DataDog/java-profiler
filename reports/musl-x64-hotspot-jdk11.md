---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-24 00:59:18 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 9 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (3 unique values: 28-45 cores)</summary>

```
1790225604 45
1790225609 43
1790225614 43
1790225619 43
1790225624 43
1790225629 43
1790225634 43
1790225639 43
1790225644 43
1790225649 43
1790225654 43
1790225659 43
1790225664 43
1790225669 45
1790225674 45
1790225679 28
1790225684 28
1790225689 28
1790225694 28
1790225699 28
```
</details>

---

