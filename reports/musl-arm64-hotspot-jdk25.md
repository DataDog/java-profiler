---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-27 19:04:07 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 272 |
| Sample Rate | 4.53/sec |
| Health Score | 283% |
| Threads | 11 |
| Allocations | 179 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793141954 51
1793141959 51
1793141964 51
1793141969 51
1793141974 51
1793141979 46
1793141984 46
1793141989 46
1793141994 46
1793141999 46
1793142004 46
1793142009 46
1793142014 46
1793142019 46
1793142024 46
1793142029 46
1793142034 46
1793142039 51
1793142044 51
1793142049 51
```
</details>

---

