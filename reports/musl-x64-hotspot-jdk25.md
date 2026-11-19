---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 12:14:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 10 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (2 unique values: 18-23 cores)</summary>

```
1795108184 18
1795108189 18
1795108194 18
1795108199 18
1795108204 18
1795108209 18
1795108214 18
1795108219 18
1795108224 18
1795108229 18
1795108234 18
1795108239 18
1795108244 18
1795108249 18
1795108254 18
1795108259 18
1795108264 18
1795108269 23
1795108274 23
1795108279 23
```
</details>

---

