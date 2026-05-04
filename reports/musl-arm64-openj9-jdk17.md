---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-03 21:22:14 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 45 |
| Sample Rate | 0.75/sec |
| Health Score | 47% |
| Threads | 8 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 193 |
| Sample Rate | 3.22/sec |
| Health Score | 201% |
| Threads | 12 |
| Allocations | 147 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777857397 64
1777857402 64
1777857407 64
1777857412 64
1777857417 64
1777857422 64
1777857427 64
1777857432 64
1777857437 64
1777857442 64
1777857447 64
1777857452 64
1777857457 64
1777857462 64
1777857467 64
1777857472 64
1777857477 64
1777857482 64
1777857487 64
1777857492 64
```
</details>

---

