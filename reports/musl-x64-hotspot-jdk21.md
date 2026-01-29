---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-01-29 06:14:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 735 |
| Sample Rate | 24.50/sec |
| Health Score | 1531% |
| Threads | 11 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 817 |
| Sample Rate | 27.23/sec |
| Health Score | 1702% |
| Threads | 13 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (4 unique values: 70-81 cores)</summary>

```
1769684938 70
1769684943 70
1769684948 70
1769684953 70
1769684958 70
1769684963 70
1769684968 70
1769684973 70
1769684978 70
1769684983 70
1769684988 70
1769684993 75
1769684998 75
1769685003 75
1769685008 75
1769685013 75
1769685018 75
1769685023 75
1769685028 75
1769685033 79
```
</details>

---

