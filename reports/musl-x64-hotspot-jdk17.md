---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-21 10:48:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (3 unique values: 80-96 cores)</summary>

```
1792593781 94
1792593786 94
1792593792 96
1792593797 96
1792593802 96
1792593807 96
1792593812 96
1792593817 96
1792593822 96
1792593827 96
1792593832 96
1792593837 96
1792593842 96
1792593847 96
1792593852 96
1792593857 96
1792593862 80
1792593867 80
1792593872 80
1792593877 80
```
</details>

---

