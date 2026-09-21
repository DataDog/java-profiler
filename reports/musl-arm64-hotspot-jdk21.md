---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-21 09:02:25 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 49-64 cores)</summary>

```
1789995353 64
1789995358 64
1789995363 64
1789995368 49
1789995373 49
1789995378 49
1789995383 49
1789995388 49
1789995393 49
1789995398 49
1789995403 49
1789995408 49
1789995413 49
1789995418 49
1789995423 49
1789995428 49
1789995433 49
1789995438 49
1789995443 49
1789995448 49
```
</details>

---

