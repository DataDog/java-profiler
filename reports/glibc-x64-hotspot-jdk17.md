---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-06 14:10:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 419 |
| Sample Rate | 6.98/sec |
| Health Score | 436% |
| Threads | 8 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 10 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 37-42 cores)</summary>

```
1778090753 42
1778090758 42
1778090763 37
1778090768 37
1778090773 37
1778090778 37
1778090783 37
1778090788 37
1778090793 42
1778090798 42
1778090803 42
1778090808 42
1778090813 42
1778090818 42
1778090823 42
1778090828 42
1778090833 42
1778090838 42
1778090843 42
1778090848 42
```
</details>

---

