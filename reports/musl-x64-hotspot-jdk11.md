---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 13:07:04 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 8 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (3 unique values: 48-52 cores)</summary>

```
1795111302 52
1795111307 52
1795111312 52
1795111317 52
1795111322 52
1795111327 52
1795111332 52
1795111337 52
1795111342 52
1795111347 52
1795111352 52
1795111357 52
1795111362 52
1795111367 52
1795111372 48
1795111377 48
1795111382 48
1795111387 48
1795111392 48
1795111397 48
```
</details>

---

