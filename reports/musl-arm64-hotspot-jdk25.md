---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-20 18:16:58 EDT

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
| CPU Cores (start) | 53 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 284 |
| Sample Rate | 4.73/sec |
| Health Score | 296% |
| Threads | 11 |
| Allocations | 145 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (3 unique values: 52-64 cores)</summary>

```
1792534331 53
1792534336 53
1792534341 53
1792534346 53
1792534351 53
1792534356 53
1792534361 53
1792534366 53
1792534371 53
1792534376 64
1792534381 64
1792534386 64
1792534391 64
1792534396 64
1792534401 64
1792534406 64
1792534411 64
1792534416 64
1792534421 64
1792534426 64
```
</details>

---

