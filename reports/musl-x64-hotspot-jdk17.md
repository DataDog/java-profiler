---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-06 14:10:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 719 |
| Sample Rate | 11.98/sec |
| Health Score | 749% |
| Threads | 10 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (2 unique values: 11-23 cores)</summary>

```
1778090728 11
1778090733 11
1778090738 11
1778090743 11
1778090748 11
1778090753 11
1778090758 11
1778090763 11
1778090768 11
1778090773 11
1778090778 11
1778090783 11
1778090788 11
1778090793 23
1778090798 23
1778090803 23
1778090808 23
1778090813 23
1778090818 23
1778090823 23
```
</details>

---

