---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-26 01:04:22 EDT

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
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 136 |
| Sample Rate | 2.27/sec |
| Health Score | 142% |
| Threads | 10 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787720253 64
1787720258 64
1787720263 64
1787720268 64
1787720273 64
1787720278 64
1787720283 64
1787720288 64
1787720293 64
1787720298 64
1787720303 64
1787720309 64
1787720314 64
1787720319 64
1787720324 64
1787720329 64
1787720334 64
1787720339 64
1787720344 64
1787720349 64
```
</details>

---

