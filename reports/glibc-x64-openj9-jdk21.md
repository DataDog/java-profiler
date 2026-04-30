---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-30 05:30:09 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 10 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (3 unique values: 39-41 cores)</summary>

```
1777541224 39
1777541229 39
1777541234 39
1777541239 39
1777541244 39
1777541249 40
1777541254 40
1777541259 40
1777541264 40
1777541269 40
1777541274 40
1777541279 40
1777541284 41
1777541289 41
1777541294 41
1777541299 41
1777541304 41
1777541309 41
1777541314 41
1777541319 41
```
</details>

---

