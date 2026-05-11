---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-11 11:50:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 775 |
| Sample Rate | 12.92/sec |
| Health Score | 807% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 936 |
| Sample Rate | 15.60/sec |
| Health Score | 975% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (3 unique values: 73-82 cores)</summary>

```
1778514254 73
1778514259 80
1778514264 80
1778514269 80
1778514274 80
1778514279 80
1778514284 80
1778514289 80
1778514294 80
1778514299 80
1778514304 80
1778514309 80
1778514314 80
1778514319 80
1778514324 80
1778514329 80
1778514334 80
1778514339 82
1778514344 82
1778514349 82
```
</details>

---

