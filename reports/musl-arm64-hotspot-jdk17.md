---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-06 05:52:39 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 295 |
| Sample Rate | 4.92/sec |
| Health Score | 308% |
| Threads | 9 |
| Allocations | 153 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 390 |
| Sample Rate | 6.50/sec |
| Health Score | 406% |
| Threads | 11 |
| Allocations | 122 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1791279945 48
1791279950 48
1791279955 48
1791279960 48
1791279965 48
1791279970 48
1791279975 48
1791279980 48
1791279985 48
1791279990 48
1791279995 48
1791280000 48
1791280005 48
1791280010 48
1791280015 43
1791280020 43
1791280025 43
1791280030 43
1791280035 43
1791280040 43
```
</details>

---

