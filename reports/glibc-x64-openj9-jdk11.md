---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 07:35:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 750 |
| Sample Rate | 12.50/sec |
| Health Score | 781% |
| Threads | 9 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (4 unique values: 71-94 cores)</summary>

```
1794832258 91
1794832263 91
1794832268 91
1794832273 91
1794832278 91
1794832283 91
1794832288 91
1794832293 91
1794832298 94
1794832303 94
1794832308 94
1794832313 94
1794832318 94
1794832323 94
1794832328 94
1794832333 92
1794832338 92
1794832343 92
1794832348 92
1794832353 92
```
</details>

---

