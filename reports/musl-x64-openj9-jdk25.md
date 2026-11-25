---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 10:02:43 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 395 |
| Sample Rate | 6.58/sec |
| Health Score | 411% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 606 |
| Sample Rate | 10.10/sec |
| Health Score | 631% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (2 unique values: 78-80 cores)</summary>

```
1795618616 78
1795618621 78
1795618626 78
1795618631 78
1795618636 78
1795618641 78
1795618646 78
1795618651 78
1795618656 78
1795618661 78
1795618666 78
1795618671 78
1795618676 78
1795618681 78
1795618686 78
1795618691 80
1795618696 80
1795618701 80
1795618706 80
1795618711 80
```
</details>

---

