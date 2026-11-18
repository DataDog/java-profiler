---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 09:52:43 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 9 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 39-52 cores)</summary>

```
1795013135 52
1795013140 52
1795013145 52
1795013150 52
1795013155 39
1795013160 39
1795013165 39
1795013170 39
1795013175 39
1795013180 39
1795013185 39
1795013190 39
1795013195 39
1795013200 39
1795013205 39
1795013210 39
1795013215 39
1795013220 39
1795013225 39
1795013230 39
```
</details>

---

