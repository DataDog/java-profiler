---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-27 17:32:21 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 871 |
| Sample Rate | 14.52/sec |
| Health Score | 907% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 44-48 cores)</summary>

```
1777325212 48
1777325217 48
1777325222 48
1777325227 48
1777325232 48
1777325237 48
1777325242 48
1777325247 48
1777325252 48
1777325257 48
1777325262 48
1777325267 48
1777325272 44
1777325277 44
1777325282 44
1777325287 44
1777325292 44
1777325297 44
1777325302 44
1777325307 44
```
</details>

---

