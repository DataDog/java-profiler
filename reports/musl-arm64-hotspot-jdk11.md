---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 08:01:49 EDT

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
| CPU Cores (start) | 9 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 9-29 cores)</summary>

```
1792670181 9
1792670186 9
1792670191 9
1792670196 9
1792670201 9
1792670206 9
1792670211 9
1792670216 9
1792670221 9
1792670226 9
1792670231 29
1792670236 29
1792670241 29
1792670246 29
1792670251 29
1792670256 29
1792670261 29
1792670266 29
1792670271 29
1792670276 29
```
</details>

---

