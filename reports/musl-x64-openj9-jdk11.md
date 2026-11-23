---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 05:28:08 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 10 |
| Allocations | 570 |

<details>
<summary>CPU Timeline (2 unique values: 51-72 cores)</summary>

```
1795429412 51
1795429417 51
1795429422 51
1795429427 51
1795429432 51
1795429437 51
1795429442 51
1795429447 51
1795429452 51
1795429457 51
1795429462 51
1795429467 51
1795429472 51
1795429477 51
1795429482 72
1795429487 72
1795429492 72
1795429497 72
1795429502 72
1795429507 72
```
</details>

---

