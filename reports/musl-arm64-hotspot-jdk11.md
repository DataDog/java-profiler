---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-12 04:31:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 30 |
| Sample Rate | 0.50/sec |
| Health Score | 31% |
| Threads | 9 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1791793629 48
1791793634 48
1791793639 48
1791793644 48
1791793649 48
1791793654 48
1791793659 48
1791793664 48
1791793669 48
1791793674 48
1791793679 48
1791793684 48
1791793689 48
1791793694 48
1791793699 48
1791793704 48
1791793709 48
1791793714 48
1791793719 48
1791793724 48
```
</details>

---

