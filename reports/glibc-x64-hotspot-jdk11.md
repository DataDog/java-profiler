---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-27 17:32:18 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 9 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (3 unique values: 16-50 cores)</summary>

```
1777325198 47
1777325203 47
1777325208 47
1777325213 47
1777325218 47
1777325223 47
1777325228 16
1777325233 16
1777325238 16
1777325243 16
1777325248 16
1777325253 16
1777325258 16
1777325263 16
1777325268 16
1777325273 16
1777325278 16
1777325283 16
1777325288 16
1777325293 16
```
</details>

---

