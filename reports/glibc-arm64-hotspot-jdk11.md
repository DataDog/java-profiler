---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-01 15:37:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 13 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 45-48 cores)</summary>

```
1788291209 48
1788291214 48
1788291219 48
1788291224 48
1788291229 48
1788291234 48
1788291239 48
1788291244 48
1788291249 48
1788291254 48
1788291259 48
1788291264 48
1788291269 45
1788291274 45
1788291279 45
1788291284 45
1788291289 45
1788291294 45
1788291299 45
1788291304 45
```
</details>

---

