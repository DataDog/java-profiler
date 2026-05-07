---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-07 11:24:20 EDT

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
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 256 |
| Sample Rate | 4.27/sec |
| Health Score | 267% |
| Threads | 12 |
| Allocations | 153 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778167161 64
1778167166 64
1778167171 64
1778167176 64
1778167181 64
1778167186 64
1778167191 64
1778167196 64
1778167201 64
1778167206 64
1778167211 64
1778167216 64
1778167221 64
1778167226 64
1778167231 64
1778167236 64
1778167241 64
1778167246 64
1778167251 64
1778167256 64
```
</details>

---

