---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 06:23:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 9 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (3 unique values: 78-96 cores)</summary>

```
1795605433 78
1795605438 78
1795605443 78
1795605448 78
1795605453 78
1795605458 78
1795605463 78
1795605468 78
1795605473 78
1795605478 78
1795605483 87
1795605488 87
1795605493 96
1795605498 96
1795605503 96
1795605508 96
1795605513 96
1795605518 96
1795605523 96
1795605528 96
```
</details>

---

