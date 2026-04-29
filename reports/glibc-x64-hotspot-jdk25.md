---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-29 11:49:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 10 |
| Allocations | 549 |

<details>
<summary>CPU Timeline (2 unique values: 70-72 cores)</summary>

```
1777477238 72
1777477243 72
1777477248 72
1777477253 72
1777477258 72
1777477263 72
1777477268 70
1777477273 70
1777477278 70
1777477283 70
1777477288 70
1777477293 70
1777477298 70
1777477303 72
1777477308 72
1777477313 70
1777477318 70
1777477323 70
1777477328 70
1777477333 70
```
</details>

---

