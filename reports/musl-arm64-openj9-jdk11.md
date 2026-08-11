---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-11 09:44:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 14 |
| Allocations | 148 |

<details>
<summary>CPU Timeline (2 unique values: 56-64 cores)</summary>

```
1786455578 56
1786455583 56
1786455588 56
1786455593 56
1786455598 56
1786455603 56
1786455608 56
1786455613 64
1786455618 64
1786455623 64
1786455628 64
1786455633 64
1786455638 64
1786455643 64
1786455648 64
1786455653 64
1786455658 64
1786455663 64
1786455668 64
1786455673 64
```
</details>

---

