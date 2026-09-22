---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-22 15:04:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 10 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (4 unique values: 50-96 cores)</summary>

```
1790103667 50
1790103672 50
1790103677 50
1790103682 50
1790103687 50
1790103692 50
1790103697 72
1790103702 72
1790103707 72
1790103712 72
1790103717 72
1790103722 72
1790103727 72
1790103732 72
1790103737 72
1790103742 72
1790103747 72
1790103752 72
1790103757 96
1790103762 96
```
</details>

---

