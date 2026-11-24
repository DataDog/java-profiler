---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 09:14:34 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 872 |
| Sample Rate | 14.53/sec |
| Health Score | 908% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (4 unique values: 56-70 cores)</summary>

```
1795529329 56
1795529334 56
1795529339 61
1795529344 61
1795529349 61
1795529354 61
1795529359 61
1795529364 61
1795529369 61
1795529374 61
1795529379 61
1795529384 61
1795529389 61
1795529394 61
1795529399 70
1795529404 70
1795529409 70
1795529414 70
1795529419 70
1795529424 70
```
</details>

---

