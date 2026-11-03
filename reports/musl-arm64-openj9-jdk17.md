---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-03 16:51:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 8 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 39-40 cores)</summary>

```
1793742145 40
1793742150 40
1793742155 40
1793742160 40
1793742165 40
1793742170 40
1793742175 40
1793742180 39
1793742185 39
1793742190 39
1793742195 39
1793742200 39
1793742205 39
1793742210 39
1793742215 39
1793742220 39
1793742225 39
1793742230 40
1793742235 40
1793742240 40
```
</details>

---

