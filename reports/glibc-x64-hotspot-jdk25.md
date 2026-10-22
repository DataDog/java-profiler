---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-22 05:55:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 362 |
| Sample Rate | 6.03/sec |
| Health Score | 377% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 11-32 cores)</summary>

```
1792662627 11
1792662632 11
1792662637 11
1792662642 11
1792662647 11
1792662652 11
1792662657 11
1792662662 11
1792662667 11
1792662672 32
1792662677 32
1792662682 32
1792662687 32
1792662692 32
1792662697 32
1792662702 32
1792662707 32
1792662712 32
1792662717 32
1792662722 32
```
</details>

---

