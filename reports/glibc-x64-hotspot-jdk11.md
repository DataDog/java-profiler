---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-13 11:08:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 8 |
| Allocations | 341 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 814 |
| Sample Rate | 13.57/sec |
| Health Score | 848% |
| Threads | 11 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (3 unique values: 68-75 cores)</summary>

```
1778684536 68
1778684541 68
1778684546 68
1778684551 68
1778684556 68
1778684561 68
1778684566 70
1778684571 70
1778684576 70
1778684581 70
1778684586 70
1778684591 70
1778684596 70
1778684601 70
1778684606 75
1778684611 75
1778684616 75
1778684621 75
1778684626 75
1778684631 75
```
</details>

---

