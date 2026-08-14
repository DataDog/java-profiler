---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-14 08:29:03 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 137 |
| Sample Rate | 2.28/sec |
| Health Score | 142% |
| Threads | 14 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 52-64 cores)</summary>

```
1786710273 52
1786710278 52
1786710283 52
1786710288 52
1786710293 52
1786710298 52
1786710303 52
1786710308 52
1786710313 52
1786710318 52
1786710323 52
1786710328 52
1786710333 52
1786710338 52
1786710343 52
1786710348 52
1786710353 52
1786710358 52
1786710363 52
1786710368 64
```
</details>

---

