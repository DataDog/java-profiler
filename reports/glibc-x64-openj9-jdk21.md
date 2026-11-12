---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 13:37:07 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 8 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 549 |
| Sample Rate | 9.15/sec |
| Health Score | 572% |
| Threads | 9 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (2 unique values: 28-30 cores)</summary>

```
1794508169 28
1794508174 28
1794508179 28
1794508184 28
1794508189 28
1794508194 30
1794508199 30
1794508204 30
1794508209 30
1794508214 30
1794508219 30
1794508224 30
1794508229 30
1794508234 30
1794508239 30
1794508244 30
1794508249 30
1794508254 30
1794508259 30
1794508264 30
```
</details>

---

