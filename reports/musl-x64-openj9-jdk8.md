---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-26 10:05:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 341 |
| Sample Rate | 5.68/sec |
| Health Score | 355% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 194 |
| Sample Rate | 3.23/sec |
| Health Score | 202% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 37-41 cores)</summary>

```
1793023153 37
1793023158 37
1793023163 39
1793023168 39
1793023173 39
1793023178 39
1793023183 39
1793023188 39
1793023193 39
1793023198 39
1793023203 39
1793023208 39
1793023213 41
1793023218 41
1793023223 41
1793023228 41
1793023233 41
1793023238 41
1793023243 41
1793023248 41
```
</details>

---

