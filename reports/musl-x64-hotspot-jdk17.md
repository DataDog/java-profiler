---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 10:08:11 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1034 |
| Sample Rate | 17.23/sec |
| Health Score | 1077% |
| Threads | 11 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 45-54 cores)</summary>

```
1795618875 54
1795618880 54
1795618885 54
1795618890 54
1795618895 54
1795618900 54
1795618905 54
1795618911 54
1795618916 54
1795618921 54
1795618926 46
1795618931 46
1795618936 46
1795618941 46
1795618946 45
1795618951 45
1795618956 45
1795618961 45
1795618966 45
1795618971 45
```
</details>

---

