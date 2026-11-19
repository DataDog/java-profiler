---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-19 13:36:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 170 |
| Sample Rate | 2.83/sec |
| Health Score | 177% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 239 |
| Sample Rate | 3.98/sec |
| Health Score | 249% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 61-70 cores)</summary>

```
1795113159 61
1795113164 61
1795113169 61
1795113174 61
1795113179 61
1795113184 61
1795113189 61
1795113194 61
1795113199 61
1795113204 70
1795113209 70
1795113214 62
1795113219 62
1795113224 62
1795113229 62
1795113234 62
1795113239 62
1795113244 62
1795113249 62
1795113254 62
```
</details>

---

