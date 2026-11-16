---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-15 20:28:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 340 |
| Sample Rate | 5.67/sec |
| Health Score | 354% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 462 |
| Sample Rate | 7.70/sec |
| Health Score | 481% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 75-96 cores)</summary>

```
1794792272 75
1794792277 96
1794792282 96
1794792287 96
1794792292 94
1794792297 94
1794792302 94
1794792307 94
1794792312 94
1794792317 94
1794792322 94
1794792327 94
1794792332 96
1794792337 96
1794792342 96
1794792347 96
1794792352 96
1794792357 96
1794792362 96
1794792367 96
```
</details>

---

