---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-02 13:05:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 9 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (2 unique values: 20-32 cores)</summary>

```
1793642460 20
1793642465 20
1793642470 20
1793642475 20
1793642480 20
1793642485 20
1793642490 20
1793642495 20
1793642500 20
1793642505 20
1793642510 20
1793642515 32
1793642520 32
1793642525 32
1793642530 32
1793642535 32
1793642540 32
1793642545 32
1793642550 32
1793642555 32
```
</details>

---

