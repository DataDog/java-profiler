---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 14:31:00 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 828 |
| Sample Rate | 13.80/sec |
| Health Score | 862% |
| Threads | 9 |
| Allocations | 551 |

<details>
<summary>CPU Timeline (3 unique values: 72-91 cores)</summary>

```
1794511568 91
1794511573 91
1794511578 91
1794511583 91
1794511588 72
1794511593 72
1794511598 72
1794511603 72
1794511608 72
1794511613 72
1794511618 72
1794511623 72
1794511628 72
1794511633 72
1794511638 72
1794511643 74
1794511648 74
1794511653 74
1794511658 74
1794511663 74
```
</details>

---

