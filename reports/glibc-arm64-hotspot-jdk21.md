---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ❌ FAIL

**Date:** 2026-01-29 06:14:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 2.73/sec |
| Health Score | 171% |
| Threads | 8 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 13 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 6 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769684928 24
1769684933 24
1769684938 24
1769684943 24
1769684948 24
1769684953 24
1769684958 24
1769684963 24
1769684968 24
1769684973 24
1769684978 24
1769684983 24
1769684988 24
1769684993 24
1769684998 24
1769685003 24
1769685008 24
1769685013 24
1769685018 24
1769685023 24
```
</details>

---

