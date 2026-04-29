---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-29 11:49:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 11 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1777477268 49
1777477273 49
1777477278 49
1777477283 49
1777477288 49
1777477293 49
1777477298 49
1777477303 49
1777477308 49
1777477314 49
1777477319 49
1777477324 49
1777477329 49
1777477334 49
1777477339 49
1777477344 44
1777477349 44
1777477354 44
1777477359 44
1777477364 44
```
</details>

---

