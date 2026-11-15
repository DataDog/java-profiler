---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-14 19:51:06 EST

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 183 |
| Sample Rate | 3.05/sec |
| Health Score | 191% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 354 |
| Sample Rate | 5.90/sec |
| Health Score | 369% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 92-96 cores)</summary>

```
1794703621 92
1794703626 92
1794703631 92
1794703636 92
1794703641 92
1794703646 92
1794703651 92
1794703656 92
1794703661 92
1794703666 92
1794703671 92
1794703676 92
1794703681 92
1794703686 92
1794703691 96
1794703697 96
1794703702 96
1794703707 96
1794703712 96
1794703717 96
```
</details>

---

