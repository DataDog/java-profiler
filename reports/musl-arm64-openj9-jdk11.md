---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-30 21:26:10 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 10 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 9 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1788139176 64
1788139181 64
1788139186 64
1788139191 64
1788139196 64
1788139201 64
1788139206 64
1788139211 64
1788139216 64
1788139221 64
1788139226 64
1788139231 64
1788139236 64
1788139241 64
1788139246 64
1788139251 64
1788139256 64
1788139261 64
1788139266 64
1788139271 64
```
</details>

---

