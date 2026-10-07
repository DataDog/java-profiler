---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-07 10:29:46 EDT

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
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 9 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 388 |
| Sample Rate | 6.47/sec |
| Health Score | 404% |
| Threads | 13 |
| Allocations | 118 |

<details>
<summary>CPU Timeline (3 unique values: 39-46 cores)</summary>

```
1791382947 46
1791382952 46
1791382957 41
1791382962 41
1791382967 41
1791382972 41
1791382977 41
1791382982 41
1791382987 41
1791382992 41
1791382997 41
1791383002 41
1791383007 46
1791383012 46
1791383017 46
1791383022 46
1791383027 46
1791383032 46
1791383037 39
1791383042 39
```
</details>

---

