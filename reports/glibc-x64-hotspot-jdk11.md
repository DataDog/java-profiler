---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 07:51:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 8 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794401179 32
1794401184 32
1794401189 32
1794401194 32
1794401199 32
1794401204 32
1794401209 32
1794401214 32
1794401219 32
1794401224 32
1794401229 32
1794401234 32
1794401239 32
1794401244 30
1794401249 30
1794401254 30
1794401259 30
1794401264 30
1794401269 30
1794401274 32
```
</details>

---

