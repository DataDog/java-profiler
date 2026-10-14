---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-14 08:33:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 11 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1791980920 48
1791980925 48
1791980930 46
1791980935 46
1791980940 46
1791980945 46
1791980950 46
1791980955 46
1791980960 46
1791980965 46
1791980970 46
1791980975 46
1791980980 46
1791980985 48
1791980990 48
1791980995 48
1791981000 48
1791981005 48
1791981010 48
1791981015 48
```
</details>

---

