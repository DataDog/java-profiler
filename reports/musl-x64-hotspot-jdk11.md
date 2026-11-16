---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 07:25:16 EST

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
| CPU Cores (start) | 74 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 745 |
| Sample Rate | 12.42/sec |
| Health Score | 776% |
| Threads | 9 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (3 unique values: 72-94 cores)</summary>

```
1794831573 74
1794831578 74
1794831583 72
1794831588 72
1794831593 72
1794831598 72
1794831603 72
1794831608 72
1794831613 72
1794831618 72
1794831623 72
1794831628 72
1794831633 72
1794831638 72
1794831643 94
1794831648 94
1794831653 94
1794831658 94
1794831663 94
1794831668 94
```
</details>

---

