---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-12 04:42:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 925 |
| Sample Rate | 15.42/sec |
| Health Score | 964% |
| Threads | 8 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (3 unique values: 36-48 cores)</summary>

```
1791794205 36
1791794210 36
1791794215 36
1791794220 48
1791794225 48
1791794230 48
1791794235 48
1791794240 48
1791794245 48
1791794250 48
1791794255 48
1791794260 48
1791794265 43
1791794270 43
1791794275 43
1791794280 43
1791794285 43
1791794290 43
1791794295 43
1791794300 43
```
</details>

---

