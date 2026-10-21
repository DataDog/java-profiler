---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-21 05:55:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 281 |
| Sample Rate | 4.68/sec |
| Health Score | 292% |
| Threads | 9 |
| Allocations | 146 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 269 |
| Sample Rate | 4.48/sec |
| Health Score | 280% |
| Threads | 11 |
| Allocations | 145 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1792576265 51
1792576270 51
1792576275 51
1792576280 51
1792576285 51
1792576290 51
1792576295 51
1792576300 51
1792576305 51
1792576310 51
1792576315 51
1792576320 51
1792576325 51
1792576330 51
1792576335 39
1792576340 39
1792576345 39
1792576350 39
1792576355 39
1792576360 39
```
</details>

---

