---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-14 01:04:02 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 245 |
| Sample Rate | 4.08/sec |
| Health Score | 255% |
| Threads | 10 |
| Allocations | 169 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (3 unique values: 46-51 cores)</summary>

```
1791953958 48
1791953963 48
1791953968 48
1791953973 48
1791953978 48
1791953983 48
1791953988 48
1791953993 48
1791953998 48
1791954003 48
1791954008 48
1791954013 48
1791954018 48
1791954023 48
1791954028 46
1791954033 46
1791954038 51
1791954043 51
1791954048 51
1791954053 51
```
</details>

---

