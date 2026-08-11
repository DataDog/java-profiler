---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-11 02:24:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 458 |
| Sample Rate | 7.63/sec |
| Health Score | 477% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 9 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (5 unique values: 19-31 cores)</summary>

```
1786429198 21
1786429203 21
1786429208 21
1786429213 21
1786429218 19
1786429223 19
1786429228 19
1786429233 19
1786429238 19
1786429243 19
1786429248 19
1786429253 19
1786429258 27
1786429263 27
1786429268 29
1786429273 29
1786429278 29
1786429283 31
1786429288 31
1786429293 31
```
</details>

---

