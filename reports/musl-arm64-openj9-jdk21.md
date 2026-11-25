---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 06:39:36 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 43 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795606486 33
1795606491 33
1795606496 33
1795606501 33
1795606506 33
1795606511 33
1795606516 33
1795606521 33
1795606526 33
1795606531 33
1795606536 33
1795606541 33
1795606546 33
1795606551 33
1795606556 33
1795606561 33
1795606566 64
1795606571 64
1795606576 64
1795606581 64
```
</details>

---

