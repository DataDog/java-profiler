---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 05:00:22 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 196 |
| Sample Rate | 3.27/sec |
| Health Score | 204% |
| Threads | 13 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (2 unique values: 25-26 cores)</summary>

```
1794477233 26
1794477238 26
1794477243 26
1794477248 26
1794477253 25
1794477258 25
1794477263 25
1794477268 25
1794477273 26
1794477278 26
1794477283 26
1794477288 26
1794477293 25
1794477298 25
1794477303 25
1794477308 25
1794477313 25
1794477318 25
1794477323 25
1794477328 25
```
</details>

---

