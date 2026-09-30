---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-30 07:31:56 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 759 |
| Sample Rate | 12.65/sec |
| Health Score | 791% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (3 unique values: 47-66 cores)</summary>

```
1790767598 47
1790767603 47
1790767608 47
1790767613 47
1790767618 64
1790767623 64
1790767628 64
1790767633 64
1790767638 64
1790767643 64
1790767648 64
1790767653 64
1790767658 64
1790767663 64
1790767668 66
1790767673 66
1790767678 66
1790767683 66
1790767688 66
1790767693 66
```
</details>

---

