---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-25 06:23:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 166 |
| Sample Rate | 2.77/sec |
| Health Score | 173% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 7.00/sec |
| Health Score | 438% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 70-91 cores)</summary>

```
1795605433 91
1795605438 91
1795605443 70
1795605448 70
1795605453 70
1795605458 70
1795605463 70
1795605468 70
1795605473 70
1795605478 70
1795605483 70
1795605488 70
1795605493 70
1795605498 70
1795605503 70
1795605509 70
1795605514 70
1795605519 70
1795605524 70
1795605529 70
```
</details>

---

