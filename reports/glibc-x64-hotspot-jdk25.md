---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-06 15:13:43 EST

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
| CPU Cores (start) | 10 |
| CPU Cores (end) | 16 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 417 |
| Sample Rate | 6.95/sec |
| Health Score | 434% |
| Threads | 8 |
| Allocations | 415 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 10 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (2 unique values: 10-16 cores)</summary>

```
1793995758 10
1793995763 10
1793995768 10
1793995774 10
1793995779 10
1793995784 10
1793995789 10
1793995794 10
1793995799 10
1793995804 10
1793995809 10
1793995814 10
1793995819 10
1793995824 10
1793995829 10
1793995834 10
1793995839 10
1793995844 10
1793995849 10
1793995854 16
```
</details>

---

