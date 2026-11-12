---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 07:55:49 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 14 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794487760 46
1794487765 46
1794487770 46
1794487775 46
1794487780 46
1794487785 46
1794487790 46
1794487795 46
1794487800 46
1794487805 46
1794487810 46
1794487815 46
1794487820 46
1794487825 46
1794487830 46
1794487835 46
1794487840 46
1794487845 48
1794487850 48
1794487855 48
```
</details>

---

