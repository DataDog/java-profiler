---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 13:06:36 EST

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
| CPU Cores (start) | 78 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 10 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 807 |
| Sample Rate | 13.45/sec |
| Health Score | 841% |
| Threads | 11 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (5 unique values: 77-87 cores)</summary>

```
1794938481 78
1794938486 78
1794938491 78
1794938496 78
1794938501 80
1794938506 80
1794938511 80
1794938516 80
1794938521 80
1794938526 82
1794938531 82
1794938536 77
1794938541 77
1794938546 77
1794938551 87
1794938556 87
1794938561 87
1794938566 87
1794938571 87
1794938576 87
```
</details>

---

