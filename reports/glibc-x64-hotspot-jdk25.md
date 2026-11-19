---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 13:36:48 EST

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 515 |
| Sample Rate | 8.58/sec |
| Health Score | 536% |
| Threads | 11 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 61-62 cores)</summary>

```
1795113174 61
1795113179 61
1795113184 61
1795113189 61
1795113194 61
1795113199 61
1795113204 62
1795113209 62
1795113214 62
1795113219 62
1795113224 62
1795113229 62
1795113234 62
1795113239 62
1795113244 62
1795113249 62
1795113254 62
1795113259 62
1795113264 62
1795113269 62
```
</details>

---

