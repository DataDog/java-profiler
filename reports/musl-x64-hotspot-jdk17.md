---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 09:53:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 686 |
| Sample Rate | 11.43/sec |
| Health Score | 714% |
| Threads | 11 |
| Allocations | 520 |

<details>
<summary>CPU Timeline (3 unique values: 55-64 cores)</summary>

```
1795618208 61
1795618213 61
1795618218 61
1795618223 61
1795618228 64
1795618233 64
1795618238 64
1795618243 64
1795618248 64
1795618253 64
1795618258 64
1795618263 64
1795618268 64
1795618273 64
1795618278 64
1795618283 64
1795618288 64
1795618293 64
1795618298 64
1795618303 64
```
</details>

---

