---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 13:51:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 8 |
| Allocations | 310 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 7 |
| Allocations | 15 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795632479 64
1795632484 64
1795632489 64
1795632494 64
1795632500 64
1795632505 64
1795632510 64
1795632515 64
1795632520 64
1795632525 64
1795632530 64
1795632535 64
1795632540 64
1795632545 64
1795632550 64
1795632555 64
1795632560 64
1795632565 64
1795632570 64
1795632575 64
```
</details>

---

