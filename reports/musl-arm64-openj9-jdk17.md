---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 09:50:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 223 |
| Sample Rate | 3.72/sec |
| Health Score | 233% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790084789 48
1790084794 48
1790084799 48
1790084804 48
1790084809 48
1790084814 48
1790084819 48
1790084824 48
1790084829 48
1790084834 48
1790084839 48
1790084844 48
1790084849 48
1790084854 48
1790084859 48
1790084864 43
1790084869 43
1790084874 43
1790084879 43
1790084884 43
```
</details>

---

