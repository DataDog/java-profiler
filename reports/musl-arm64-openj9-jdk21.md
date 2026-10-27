---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-27 19:04:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 608 |
| Sample Rate | 10.13/sec |
| Health Score | 633% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 11 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (3 unique values: 51-64 cores)</summary>

```
1793141964 51
1793141969 51
1793141974 51
1793141979 51
1793141984 51
1793141989 51
1793141994 51
1793141999 51
1793142004 51
1793142009 51
1793142014 51
1793142019 64
1793142024 64
1793142029 64
1793142034 64
1793142039 64
1793142044 64
1793142049 64
1793142054 64
1793142059 64
```
</details>

---

