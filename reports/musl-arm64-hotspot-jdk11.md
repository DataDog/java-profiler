---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-26 10:30:27 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 9 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 56-64 cores)</summary>

```
1787754297 64
1787754302 64
1787754307 64
1787754312 64
1787754317 64
1787754322 64
1787754327 64
1787754332 64
1787754337 64
1787754342 64
1787754347 64
1787754352 64
1787754357 64
1787754362 64
1787754367 64
1787754372 64
1787754377 64
1787754382 64
1787754387 64
1787754392 64
```
</details>

---

