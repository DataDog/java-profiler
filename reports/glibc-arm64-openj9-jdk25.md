---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-30 17:09:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 29 |

<details>
<summary>CPU Timeline (3 unique values: 44-48 cores)</summary>

```
1793394293 44
1793394298 44
1793394303 46
1793394308 46
1793394313 46
1793394318 46
1793394323 46
1793394328 46
1793394333 48
1793394338 48
1793394343 48
1793394348 48
1793394353 48
1793394358 46
1793394363 46
1793394368 46
1793394373 46
1793394378 46
1793394383 46
1793394388 46
```
</details>

---

