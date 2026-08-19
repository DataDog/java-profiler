---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-19 10:58:57 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 14 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (4 unique values: 34-48 cores)</summary>

```
1787151240 48
1787151245 48
1787151250 48
1787151255 48
1787151260 44
1787151265 44
1787151270 44
1787151275 44
1787151280 44
1787151285 44
1787151290 44
1787151295 44
1787151300 39
1787151305 39
1787151310 34
1787151315 34
1787151320 34
1787151325 34
1787151330 34
1787151335 34
```
</details>

---

