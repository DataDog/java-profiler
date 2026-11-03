---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 11:00:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 569 |
| Sample Rate | 9.48/sec |
| Health Score | 592% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 782 |
| Sample Rate | 13.03/sec |
| Health Score | 814% |
| Threads | 10 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (3 unique values: 74-78 cores)</summary>

```
1793721199 76
1793721204 76
1793721209 74
1793721214 74
1793721219 74
1793721224 74
1793721229 74
1793721234 74
1793721239 74
1793721244 74
1793721249 74
1793721254 74
1793721259 74
1793721264 74
1793721269 76
1793721274 76
1793721279 76
1793721284 78
1793721289 78
1793721294 78
```
</details>

---

