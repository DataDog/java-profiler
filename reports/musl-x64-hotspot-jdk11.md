---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-21 10:05:25 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 862 |
| Sample Rate | 14.37/sec |
| Health Score | 898% |
| Threads | 10 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 24-25 cores)</summary>

```
1792591189 24
1792591194 24
1792591199 24
1792591204 24
1792591209 24
1792591214 24
1792591219 24
1792591224 24
1792591229 24
1792591234 24
1792591239 24
1792591244 24
1792591249 24
1792591254 24
1792591259 24
1792591264 24
1792591269 25
1792591274 25
1792591279 25
1792591284 25
```
</details>

---

