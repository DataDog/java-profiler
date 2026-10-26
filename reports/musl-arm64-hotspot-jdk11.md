---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-26 06:57:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 7 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 291 |
| Sample Rate | 4.85/sec |
| Health Score | 303% |
| Threads | 11 |
| Allocations | 162 |

<details>
<summary>CPU Timeline (4 unique values: 37-40 cores)</summary>

```
1793011963 37
1793011968 38
1793011973 38
1793011978 40
1793011983 40
1793011988 40
1793011993 40
1793011998 40
1793012003 40
1793012008 40
1793012013 40
1793012018 40
1793012023 40
1793012028 40
1793012033 40
1793012038 40
1793012043 40
1793012048 40
1793012053 40
1793012058 40
```
</details>

---

