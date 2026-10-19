---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-19 00:53:03 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 664 |
| Sample Rate | 11.07/sec |
| Health Score | 692% |
| Threads | 11 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (3 unique values: 56-66 cores)</summary>

```
1792385343 66
1792385348 66
1792385353 66
1792385358 66
1792385363 66
1792385368 66
1792385373 66
1792385378 66
1792385383 66
1792385388 66
1792385393 66
1792385398 66
1792385403 66
1792385408 66
1792385413 66
1792385418 58
1792385423 58
1792385428 58
1792385433 58
1792385438 56
```
</details>

---

