---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 13:51:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 9 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (3 unique values: 49-53 cores)</summary>

```
1795632427 49
1795632432 49
1795632437 49
1795632442 49
1795632447 49
1795632452 49
1795632457 51
1795632462 51
1795632467 51
1795632472 51
1795632477 51
1795632482 51
1795632487 53
1795632492 53
1795632497 53
1795632502 53
1795632507 53
1795632512 53
1795632517 53
1795632522 53
```
</details>

---

