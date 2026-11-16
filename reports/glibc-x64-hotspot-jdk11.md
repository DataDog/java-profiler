---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 09:37:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 809 |
| Sample Rate | 13.48/sec |
| Health Score | 842% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (3 unique values: 64-68 cores)</summary>

```
1794839611 64
1794839616 64
1794839621 64
1794839626 66
1794839631 66
1794839636 66
1794839641 66
1794839646 66
1794839651 66
1794839656 64
1794839661 64
1794839666 64
1794839671 64
1794839676 64
1794839681 64
1794839686 64
1794839691 64
1794839696 66
1794839701 66
1794839706 66
```
</details>

---

