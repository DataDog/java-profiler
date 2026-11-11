---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-10 19:36:45 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 25 |
| Sample Rate | 0.42/sec |
| Health Score | 26% |
| Threads | 8 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 33-43 cores)</summary>

```
1794357123 43
1794357128 43
1794357133 43
1794357138 43
1794357143 43
1794357148 38
1794357153 38
1794357158 38
1794357163 38
1794357168 38
1794357173 38
1794357178 33
1794357184 33
1794357189 33
1794357194 33
1794357199 33
1794357204 33
1794357209 38
1794357214 38
1794357219 38
```
</details>

---

