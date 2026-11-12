---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 04:59:11 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 377 |
| Sample Rate | 6.28/sec |
| Health Score | 392% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 11 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 91-96 cores)</summary>

```
1794477208 91
1794477213 91
1794477218 91
1794477223 91
1794477228 96
1794477233 96
1794477238 96
1794477243 96
1794477248 96
1794477253 96
1794477258 96
1794477263 96
1794477268 96
1794477273 96
1794477278 96
1794477283 96
1794477288 96
1794477293 96
1794477298 96
1794477303 96
```
</details>

---

