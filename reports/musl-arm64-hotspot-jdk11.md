---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-12 09:25:55 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 12 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (5 unique values: 38-48 cores)</summary>

```
1791811229 38
1791811234 38
1791811239 38
1791811244 38
1791811249 43
1791811254 43
1791811259 43
1791811264 43
1791811269 48
1791811274 48
1791811279 48
1791811285 48
1791811290 48
1791811295 48
1791811300 48
1791811305 48
1791811310 46
1791811315 46
1791811320 46
1791811325 46
```
</details>

---

