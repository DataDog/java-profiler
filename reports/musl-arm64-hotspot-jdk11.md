---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 08:52:15 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 874 |
| Sample Rate | 14.57/sec |
| Health Score | 911% |
| Threads | 9 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794836785 43
1794836790 43
1794836795 43
1794836800 43
1794836805 43
1794836810 43
1794836815 43
1794836820 43
1794836825 48
1794836830 48
1794836835 48
1794836840 48
1794836845 48
1794836850 48
1794836855 48
1794836860 48
1794836865 48
1794836870 48
1794836875 48
1794836880 48
```
</details>

---

