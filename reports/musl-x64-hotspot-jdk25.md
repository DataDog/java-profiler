---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-24 00:59:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 437 |
| Sample Rate | 7.28/sec |
| Health Score | 455% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 20-63 cores)</summary>

```
1790225607 20
1790225612 20
1790225617 20
1790225622 20
1790225627 20
1790225632 20
1790225637 20
1790225642 57
1790225647 57
1790225652 57
1790225657 57
1790225662 57
1790225667 57
1790225672 57
1790225677 57
1790225682 57
1790225687 57
1790225692 57
1790225697 57
1790225702 57
```
</details>

---

