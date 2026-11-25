---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 10:01:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 434 |
| Sample Rate | 7.23/sec |
| Health Score | 452% |
| Threads | 9 |
| Allocations | 421 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 10 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (4 unique values: 69-87 cores)</summary>

```
1795618521 72
1795618526 72
1795618531 72
1795618536 72
1795618541 72
1795618546 72
1795618551 72
1795618556 69
1795618561 69
1795618566 69
1795618571 69
1795618576 69
1795618581 69
1795618586 69
1795618591 69
1795618596 69
1795618601 78
1795618606 78
1795618611 78
1795618616 78
```
</details>

---

