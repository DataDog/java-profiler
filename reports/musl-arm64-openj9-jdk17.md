---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 14:31:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 240 |
| Sample Rate | 4.00/sec |
| Health Score | 250% |
| Threads | 11 |
| Allocations | 99 |

<details>
<summary>CPU Timeline (4 unique values: 35-45 cores)</summary>

```
1794511563 45
1794511568 45
1794511573 45
1794511578 40
1794511583 40
1794511588 40
1794511593 40
1794511598 40
1794511603 40
1794511608 40
1794511613 40
1794511618 40
1794511623 40
1794511628 40
1794511633 40
1794511638 35
1794511643 35
1794511648 35
1794511653 40
1794511658 40
```
</details>

---

