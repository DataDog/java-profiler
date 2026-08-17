---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-17 10:37:17 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 12 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 11 |
| Allocations | 189 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1786977207 38
1786977212 38
1786977217 38
1786977222 38
1786977227 38
1786977233 43
1786977238 43
1786977243 43
1786977248 43
1786977253 43
1786977258 43
1786977263 43
1786977268 43
1786977273 43
1786977278 43
1786977283 43
1786977288 43
1786977293 43
1786977298 43
1786977303 43
```
</details>

---

