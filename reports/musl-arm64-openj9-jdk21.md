---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-28 09:39:44 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 139 |
| Sample Rate | 2.32/sec |
| Health Score | 145% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 43-44 cores)</summary>

```
1790602523 43
1790602528 43
1790602533 43
1790602538 43
1790602543 43
1790602548 43
1790602553 43
1790602558 43
1790602563 43
1790602568 43
1790602573 44
1790602578 44
1790602583 44
1790602588 44
1790602593 44
1790602598 44
1790602603 44
1790602608 44
1790602613 44
1790602618 44
```
</details>

---

