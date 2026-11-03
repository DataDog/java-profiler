---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-03 11:22:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 12 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 287 |
| Sample Rate | 4.78/sec |
| Health Score | 299% |
| Threads | 14 |
| Allocations | 150 |

<details>
<summary>CPU Timeline (1 unique values: 53-53 cores)</summary>

```
1793722672 53
1793722677 53
1793722682 53
1793722687 53
1793722692 53
1793722697 53
1793722702 53
1793722707 53
1793722712 53
1793722717 53
1793722722 53
1793722727 53
1793722732 53
1793722737 53
1793722742 53
1793722747 53
1793722752 53
1793722757 53
1793722762 53
1793722767 53
```
</details>

---

