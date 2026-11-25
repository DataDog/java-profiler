---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-25 10:02:43 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 186 |
| Sample Rate | 3.10/sec |
| Health Score | 194% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 188 |
| Sample Rate | 3.13/sec |
| Health Score | 196% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 72-81 cores)</summary>

```
1795618596 72
1795618601 72
1795618606 72
1795618611 72
1795618616 72
1795618621 72
1795618626 72
1795618631 72
1795618636 72
1795618641 72
1795618646 72
1795618651 72
1795618656 72
1795618661 72
1795618666 72
1795618671 81
1795618676 81
1795618681 81
1795618686 81
1795618691 81
```
</details>

---

