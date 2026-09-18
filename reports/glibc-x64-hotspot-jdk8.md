---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-18 03:37:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 321 |
| Sample Rate | 5.35/sec |
| Health Score | 334% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 75-81 cores)</summary>

```
1789716673 79
1789716678 81
1789716683 81
1789716688 81
1789716693 81
1789716698 81
1789716703 81
1789716708 81
1789716713 81
1789716718 81
1789716723 81
1789716728 79
1789716733 79
1789716738 79
1789716743 79
1789716748 79
1789716753 75
1789716758 75
1789716763 75
1789716768 75
```
</details>

---

