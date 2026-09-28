---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-28 00:58:18 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1052 |
| Sample Rate | 17.53/sec |
| Health Score | 1096% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 46-47 cores)</summary>

```
1790571224 46
1790571229 47
1790571234 47
1790571239 47
1790571244 47
1790571249 47
1790571254 47
1790571259 47
1790571264 47
1790571269 47
1790571274 47
1790571279 47
1790571284 47
1790571289 47
1790571294 47
1790571299 47
1790571304 47
1790571309 47
1790571314 47
1790571319 47
```
</details>

---

