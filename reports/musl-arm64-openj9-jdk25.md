---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-22 05:47:58 EST

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 17-22 cores)</summary>

```
1795344206 22
1795344211 22
1795344216 22
1795344221 22
1795344226 22
1795344231 22
1795344236 22
1795344241 22
1795344246 22
1795344251 22
1795344256 22
1795344261 17
1795344266 17
1795344271 17
1795344276 17
1795344281 17
1795344286 17
1795344291 17
1795344296 17
1795344301 17
```
</details>

---

