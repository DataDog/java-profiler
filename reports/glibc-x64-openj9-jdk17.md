---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-30 09:25:03 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 847 |
| Sample Rate | 14.12/sec |
| Health Score | 882% |
| Threads | 10 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (3 unique values: 77-81 cores)</summary>

```
1777555243 81
1777555248 81
1777555253 81
1777555258 77
1777555263 77
1777555268 77
1777555273 77
1777555278 77
1777555283 79
1777555288 79
1777555293 77
1777555298 77
1777555303 79
1777555308 79
1777555313 79
1777555318 79
1777555323 79
1777555328 79
1777555333 79
1777555338 79
```
</details>

---

