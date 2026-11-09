---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-09 10:36:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 9 |
| Allocations | 323 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (5 unique values: 76-84 cores)</summary>

```
1794238248 82
1794238253 82
1794238258 82
1794238263 80
1794238268 80
1794238273 78
1794238278 78
1794238283 78
1794238288 78
1794238293 78
1794238298 78
1794238303 78
1794238308 76
1794238313 76
1794238318 76
1794238323 76
1794238328 82
1794238333 82
1794238339 82
1794238344 84
```
</details>

---

