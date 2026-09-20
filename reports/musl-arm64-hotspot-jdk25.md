---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-20 05:46:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (4 unique values: 11-18 cores)</summary>

```
1789897322 13
1789897327 13
1789897332 13
1789897337 13
1789897342 13
1789897347 13
1789897352 11
1789897357 11
1789897362 11
1789897367 11
1789897372 16
1789897377 16
1789897382 16
1789897387 16
1789897392 18
1789897397 18
1789897402 18
1789897407 18
1789897412 18
1789897417 18
```
</details>

---

