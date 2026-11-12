---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 13:37:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 9 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 11 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (4 unique values: 79-85 cores)</summary>

```
1794508173 85
1794508178 85
1794508183 85
1794508188 85
1794508193 83
1794508198 83
1794508203 83
1794508208 81
1794508213 81
1794508218 81
1794508223 81
1794508228 79
1794508233 79
1794508238 79
1794508243 79
1794508248 79
1794508253 81
1794508258 81
1794508263 81
1794508268 81
```
</details>

---

