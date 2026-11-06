---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-06 15:13:42 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 287 |
| Sample Rate | 4.78/sec |
| Health Score | 299% |
| Threads | 11 |
| Allocations | 127 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 8 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1793995784 51
1793995789 64
1793995794 64
1793995799 64
1793995804 64
1793995809 64
1793995814 64
1793995819 64
1793995824 64
1793995829 64
1793995834 64
1793995839 64
1793995844 64
1793995849 64
1793995854 64
1793995859 64
1793995864 64
1793995869 64
1793995874 64
1793995879 64
```
</details>

---

