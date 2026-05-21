---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-21 08:14:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 262 |
| Sample Rate | 4.37/sec |
| Health Score | 273% |
| Threads | 14 |
| Allocations | 108 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1779365396 64
1779365401 64
1779365406 64
1779365411 64
1779365416 64
1779365421 64
1779365426 64
1779365431 64
1779365436 64
1779365441 64
1779365446 64
1779365451 64
1779365456 64
1779365461 64
1779365466 64
1779365471 64
1779365476 64
1779365481 64
1779365486 64
1779365491 64
```
</details>

---

