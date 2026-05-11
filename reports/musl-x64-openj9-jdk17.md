---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-11 10:31:06 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 972 |
| Sample Rate | 16.20/sec |
| Health Score | 1012% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 82-84 cores)</summary>

```
1778509476 84
1778509481 84
1778509486 84
1778509491 84
1778509496 84
1778509501 84
1778509506 84
1778509511 84
1778509516 84
1778509521 84
1778509526 84
1778509531 84
1778509536 84
1778509541 84
1778509546 84
1778509551 82
1778509556 82
1778509561 82
1778509566 82
1778509571 82
```
</details>

---

