---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 10:01:40 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 707 |
| Sample Rate | 11.78/sec |
| Health Score | 736% |
| Threads | 11 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (4 unique values: 48-53 cores)</summary>

```
1795618521 51
1795618526 51
1795618531 51
1795618536 51
1795618541 51
1795618546 53
1795618551 53
1795618556 48
1795618561 48
1795618566 48
1795618571 48
1795618576 48
1795618581 48
1795618586 48
1795618591 48
1795618596 48
1795618601 48
1795618606 48
1795618611 48
1795618616 48
```
</details>

---

