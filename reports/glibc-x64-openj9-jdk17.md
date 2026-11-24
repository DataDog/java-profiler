---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-24 09:14:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 593 |
| Sample Rate | 9.88/sec |
| Health Score | 618% |
| Threads | 10 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 64-70 cores)</summary>

```
1795529324 64
1795529329 64
1795529334 64
1795529339 64
1795529344 64
1795529349 64
1795529354 64
1795529359 64
1795529364 64
1795529369 64
1795529374 64
1795529379 64
1795529384 70
1795529389 70
1795529394 70
1795529399 70
1795529404 70
1795529409 70
1795529414 70
1795529419 70
```
</details>

---

