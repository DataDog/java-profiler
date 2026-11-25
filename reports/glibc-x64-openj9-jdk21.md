---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 13:33:28 EST

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (5 unique values: 49-80 cores)</summary>

```
1795631269 80
1795631274 71
1795631279 71
1795631284 53
1795631289 53
1795631294 53
1795631299 53
1795631304 53
1795631309 53
1795631314 53
1795631319 51
1795631324 51
1795631329 51
1795631334 51
1795631339 51
1795631344 51
1795631349 51
1795631354 51
1795631359 51
1795631364 51
```
</details>

---

