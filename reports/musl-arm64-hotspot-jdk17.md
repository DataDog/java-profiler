---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-22 20:12:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1787443549 32
1787443554 32
1787443559 32
1787443564 32
1787443569 32
1787443574 32
1787443579 32
1787443584 32
1787443589 32
1787443594 32
1787443599 32
1787443604 32
1787443609 32
1787443614 32
1787443619 32
1787443624 32
1787443629 32
1787443634 32
1787443639 32
1787443644 32
```
</details>

---

