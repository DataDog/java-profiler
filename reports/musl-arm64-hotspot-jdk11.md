---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 09:14:33 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 133 |
| Sample Rate | 2.22/sec |
| Health Score | 139% |
| Threads | 10 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 43-64 cores)</summary>

```
1795529309 43
1795529314 43
1795529319 43
1795529324 43
1795529329 43
1795529334 43
1795529339 43
1795529344 43
1795529349 43
1795529354 43
1795529359 43
1795529364 43
1795529369 43
1795529374 43
1795529379 43
1795529384 43
1795529389 43
1795529394 43
1795529399 59
1795529404 59
```
</details>

---

