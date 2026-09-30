---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-30 15:17:26 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 8 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 291 |
| Sample Rate | 4.85/sec |
| Health Score | 303% |
| Threads | 15 |
| Allocations | 155 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790795563 48
1790795568 48
1790795573 48
1790795578 48
1790795583 48
1790795588 48
1790795593 48
1790795598 48
1790795603 48
1790795608 48
1790795613 48
1790795618 48
1790795623 43
1790795628 43
1790795633 43
1790795638 43
1790795643 43
1790795648 43
1790795653 43
1790795658 43
```
</details>

---

