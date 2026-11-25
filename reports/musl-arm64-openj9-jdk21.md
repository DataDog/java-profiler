---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ❌ FAIL

**Date:** 2026-11-25 13:51:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 12 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (1 unique values: 33-33 cores)</summary>

```
1795632478 33
1795632483 33
1795632488 33
1795632493 33
1795632498 33
1795632503 33
1795632508 33
1795632513 33
1795632518 33
1795632523 33
1795632528 33
1795632533 33
1795632538 33
1795632543 33
1795632548 33
1795632553 33
1795632558 33
1795632563 33
1795632568 33
1795632573 33
```
</details>

---

