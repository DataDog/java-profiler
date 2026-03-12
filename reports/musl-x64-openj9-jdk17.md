---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-12 10:27:02 EDT

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 651 |
| Sample Rate | 10.85/sec |
| Health Score | 678% |
| Threads | 11 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (4 unique values: 49-52 cores)</summary>

```
1773325257 50
1773325262 50
1773325267 50
1773325272 50
1773325277 50
1773325282 50
1773325287 50
1773325292 50
1773325297 49
1773325302 49
1773325307 49
1773325312 49
1773325317 49
1773325322 51
1773325327 51
1773325332 51
1773325337 51
1773325342 52
1773325347 52
1773325352 52
```
</details>

---

