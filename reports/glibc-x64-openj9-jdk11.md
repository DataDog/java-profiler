---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-22 20:29:49 EST

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
| CPU Cores (start) | 10 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 751 |
| Sample Rate | 12.52/sec |
| Health Score | 782% |
| Threads | 10 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (2 unique values: 10-12 cores)</summary>

```
1795397134 10
1795397139 10
1795397144 10
1795397149 10
1795397154 10
1795397159 10
1795397164 10
1795397169 10
1795397174 10
1795397179 10
1795397184 10
1795397189 10
1795397194 12
1795397199 12
1795397204 10
1795397209 10
1795397214 10
1795397219 10
1795397224 10
1795397230 10
```
</details>

---

