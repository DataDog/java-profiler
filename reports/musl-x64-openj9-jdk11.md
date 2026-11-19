---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 13:36:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 586 |
| Sample Rate | 9.77/sec |
| Health Score | 611% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 911 |
| Sample Rate | 15.18/sec |
| Health Score | 949% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 60-81 cores)</summary>

```
1795113178 60
1795113183 60
1795113188 81
1795113193 81
1795113198 81
1795113203 81
1795113208 81
1795113213 81
1795113218 81
1795113223 81
1795113228 81
1795113233 81
1795113238 81
1795113243 81
1795113248 81
1795113253 81
1795113258 81
1795113263 81
1795113268 81
1795113273 81
```
</details>

---

