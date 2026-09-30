---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-30 11:36:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 513 |
| Sample Rate | 8.55/sec |
| Health Score | 534% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (4 unique values: 46-74 cores)</summary>

```
1790782297 74
1790782302 74
1790782307 74
1790782312 74
1790782317 74
1790782322 74
1790782327 74
1790782332 74
1790782337 74
1790782342 74
1790782347 74
1790782352 70
1790782357 70
1790782362 70
1790782367 70
1790782372 70
1790782377 70
1790782382 70
1790782387 70
1790782392 70
```
</details>

---

