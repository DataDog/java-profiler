---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-14 19:51:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 148 |
| Sample Rate | 2.47/sec |
| Health Score | 154% |
| Threads | 10 |
| Allocations | 91 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 12.25/sec |
| Health Score | 766% |
| Threads | 10 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794703601 48
1794703606 48
1794703611 46
1794703616 46
1794703621 46
1794703626 46
1794703631 46
1794703636 46
1794703641 46
1794703646 46
1794703651 48
1794703656 48
1794703661 48
1794703666 48
1794703671 48
1794703676 48
1794703681 48
1794703686 48
1794703691 48
1794703696 48
```
</details>

---

