---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-27 03:38:44 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 320 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 147 |
| Sample Rate | 2.45/sec |
| Health Score | 153% |
| Threads | 10 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (3 unique values: 49-59 cores)</summary>

```
1777275247 49
1777275252 54
1777275257 54
1777275262 54
1777275267 59
1777275272 59
1777275277 59
1777275282 59
1777275287 59
1777275292 59
1777275297 59
1777275302 59
1777275307 59
1777275312 59
1777275317 59
1777275322 59
1777275327 59
1777275332 59
1777275337 59
1777275342 59
```
</details>

---

