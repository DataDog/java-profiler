---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-19 09:18:49 EDT

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 9 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (4 unique values: 24-29 cores)</summary>

```
1792415672 26
1792415677 24
1792415682 24
1792415687 24
1792415692 24
1792415697 24
1792415702 24
1792415707 26
1792415712 26
1792415717 29
1792415722 29
1792415727 29
1792415732 29
1792415737 29
1792415742 29
1792415747 29
1792415752 29
1792415757 26
1792415762 26
1792415767 27
```
</details>

---

