---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-14 19:51:08 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 29-75 cores)</summary>

```
1794703603 29
1794703608 62
1794703613 62
1794703618 62
1794703623 62
1794703628 62
1794703633 62
1794703638 62
1794703643 62
1794703648 62
1794703653 62
1794703658 62
1794703663 62
1794703668 62
1794703673 62
1794703678 62
1794703683 62
1794703688 75
1794703693 75
1794703698 75
```
</details>

---

