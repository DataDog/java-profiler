---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-27 17:32:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 999 |
| Sample Rate | 16.65/sec |
| Health Score | 1041% |
| Threads | 11 |
| Allocations | 522 |

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

