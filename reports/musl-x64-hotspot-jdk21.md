---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 13:08:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 11 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 9 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (5 unique values: 86-93 cores)</summary>

```
1794506548 87
1794506554 87
1794506559 87
1794506564 87
1794506569 87
1794506574 87
1794506579 87
1794506584 87
1794506589 87
1794506594 87
1794506599 87
1794506604 89
1794506609 89
1794506614 89
1794506619 89
1794506624 89
1794506629 86
1794506634 86
1794506639 86
1794506644 91
```
</details>

---

