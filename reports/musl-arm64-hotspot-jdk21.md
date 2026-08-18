---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-18 12:29:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 195 |
| Sample Rate | 3.25/sec |
| Health Score | 203% |
| Threads | 12 |
| Allocations | 162 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1787070267 59
1787070272 59
1787070277 59
1787070282 59
1787070287 59
1787070292 64
1787070297 64
1787070302 64
1787070307 64
1787070312 64
1787070317 64
1787070322 64
1787070327 64
1787070332 64
1787070337 64
1787070342 64
1787070347 64
1787070352 64
1787070357 64
1787070362 64
```
</details>

---

