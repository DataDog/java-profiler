---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-24 05:55:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 9 |
| Allocations | 414 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 938 |
| Sample Rate | 15.63/sec |
| Health Score | 977% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (5 unique values: 33-72 cores)</summary>

```
1792835473 72
1792835478 72
1792835483 72
1792835488 72
1792835493 72
1792835498 72
1792835503 72
1792835508 72
1792835514 37
1792835519 37
1792835524 37
1792835529 37
1792835534 37
1792835539 37
1792835544 39
1792835549 39
1792835554 39
1792835559 39
1792835564 33
1792835569 33
```
</details>

---

