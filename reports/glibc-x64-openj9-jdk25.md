---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-01 01:04:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 368 |
| Sample Rate | 6.13/sec |
| Health Score | 383% |
| Threads | 9 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 11 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (3 unique values: 62-66 cores)</summary>

```
1793509233 66
1793509238 66
1793509243 66
1793509248 66
1793509253 66
1793509258 64
1793509263 64
1793509268 64
1793509273 64
1793509278 64
1793509283 64
1793509288 62
1793509293 62
1793509298 62
1793509303 62
1793509308 62
1793509313 62
1793509318 62
1793509323 62
1793509328 62
```
</details>

---

