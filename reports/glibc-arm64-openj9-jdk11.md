---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-03 11:00:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 13 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793721244 48
1793721249 48
1793721254 48
1793721259 48
1793721264 48
1793721269 48
1793721274 48
1793721279 48
1793721284 48
1793721289 48
1793721294 48
1793721299 48
1793721304 48
1793721309 48
1793721314 48
1793721319 48
1793721324 48
1793721329 48
1793721334 48
1793721339 48
```
</details>

---

