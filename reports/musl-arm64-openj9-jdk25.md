---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 11:07:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 10 |
| Allocations | 38 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 11 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (2 unique values: 15-32 cores)</summary>

```
1789743538 15
1789743543 15
1789743548 15
1789743553 15
1789743558 15
1789743563 15
1789743568 15
1789743573 15
1789743578 15
1789743583 15
1789743588 15
1789743593 15
1789743598 15
1789743603 15
1789743608 15
1789743613 32
1789743618 32
1789743623 32
1789743628 32
1789743633 15
```
</details>

---

