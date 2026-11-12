---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 14:31:01 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 427 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 10 |
| Allocations | 563 |

<details>
<summary>CPU Timeline (3 unique values: 26-30 cores)</summary>

```
1794511593 30
1794511598 30
1794511603 30
1794511608 30
1794511613 30
1794511618 30
1794511623 30
1794511628 30
1794511633 30
1794511638 30
1794511643 28
1794511648 28
1794511653 28
1794511658 28
1794511663 28
1794511668 28
1794511673 28
1794511678 28
1794511683 28
1794511688 28
```
</details>

---

