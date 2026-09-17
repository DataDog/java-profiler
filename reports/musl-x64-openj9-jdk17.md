---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 19:11:36 EDT

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 806 |
| Sample Rate | 13.43/sec |
| Health Score | 839% |
| Threads | 10 |
| Allocations | 427 |

<details>
<summary>CPU Timeline (4 unique values: 82-96 cores)</summary>

```
1789686353 82
1789686358 82
1789686363 82
1789686368 84
1789686373 84
1789686378 82
1789686383 82
1789686388 82
1789686393 82
1789686398 82
1789686403 82
1789686408 84
1789686413 84
1789686418 84
1789686423 96
1789686428 96
1789686433 96
1789686438 96
1789686443 96
1789686448 96
```
</details>

---

