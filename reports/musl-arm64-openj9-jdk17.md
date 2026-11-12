---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 07:47:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
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
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 34 |
| Sample Rate | 0.57/sec |
| Health Score | 36% |
| Threads | 2 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1794487383 40
1794487388 40
1794487393 40
1794487398 40
1794487403 40
1794487408 40
1794487413 40
1794487418 40
1794487423 40
1794487428 40
1794487433 40
1794487438 40
1794487443 40
1794487448 40
1794487453 40
1794487459 40
1794487464 40
1794487469 40
1794487474 40
1794487479 40
```
</details>

---

