---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-18 08:22:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 8 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 273 |
| Sample Rate | 4.55/sec |
| Health Score | 284% |
| Threads | 14 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (1 unique values: 36-36 cores)</summary>

```
1795007924 36
1795007929 36
1795007934 36
1795007939 36
1795007944 36
1795007949 36
1795007954 36
1795007959 36
1795007964 36
1795007969 36
1795007974 36
1795007979 36
1795007984 36
1795007989 36
1795007994 36
1795007999 36
1795008004 36
1795008009 36
1795008014 36
1795008019 36
```
</details>

---

