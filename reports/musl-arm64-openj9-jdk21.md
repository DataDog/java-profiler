---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-22 05:47:58 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 9 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1795344205 24
1795344210 24
1795344215 24
1795344220 24
1795344225 24
1795344230 24
1795344235 24
1795344240 24
1795344245 24
1795344250 24
1795344256 24
1795344261 24
1795344266 24
1795344271 29
1795344276 29
1795344281 29
1795344286 29
1795344291 29
1795344296 29
1795344301 29
```
</details>

---

