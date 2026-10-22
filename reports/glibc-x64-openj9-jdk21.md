---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 05:55:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 595 |
| Sample Rate | 9.92/sec |
| Health Score | 620% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 64-68 cores)</summary>

```
1792662632 64
1792662637 64
1792662642 64
1792662647 64
1792662652 64
1792662657 64
1792662662 64
1792662667 64
1792662672 66
1792662677 66
1792662682 66
1792662687 66
1792662692 66
1792662697 68
1792662702 68
1792662707 68
1792662712 68
1792662717 68
1792662722 68
1792662727 68
```
</details>

---

