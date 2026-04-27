---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-27 03:38:45 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 670 |
| Sample Rate | 11.17/sec |
| Health Score | 698% |
| Threads | 9 |
| Allocations | 333 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 851 |
| Sample Rate | 14.18/sec |
| Health Score | 886% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (4 unique values: 44-51 cores)</summary>

```
1777275242 49
1777275247 49
1777275252 49
1777275257 49
1777275262 49
1777275267 49
1777275272 49
1777275277 49
1777275282 49
1777275287 49
1777275292 49
1777275297 49
1777275302 49
1777275307 49
1777275312 49
1777275317 49
1777275322 49
1777275327 51
1777275332 51
1777275338 51
```
</details>

---

