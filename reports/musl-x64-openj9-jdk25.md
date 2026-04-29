---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-29 05:44:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 11 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (4 unique values: 81-85 cores)</summary>

```
1777455259 81
1777455264 81
1777455269 81
1777455274 81
1777455279 82
1777455284 82
1777455289 82
1777455294 82
1777455299 83
1777455304 83
1777455309 83
1777455314 85
1777455319 85
1777455324 85
1777455329 85
1777455334 85
1777455339 85
1777455344 85
1777455349 85
1777455354 85
```
</details>

---

