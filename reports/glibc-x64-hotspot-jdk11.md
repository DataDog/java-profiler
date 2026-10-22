---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 08:01:48 EDT

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
| CPU Cores (start) | 88 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 499 |
| Sample Rate | 8.32/sec |
| Health Score | 520% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 9 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1792670188 88
1792670193 88
1792670198 88
1792670203 88
1792670208 88
1792670213 88
1792670218 88
1792670223 88
1792670228 88
1792670233 88
1792670238 96
1792670243 96
1792670248 96
1792670253 96
1792670258 96
1792670263 96
1792670268 96
1792670273 96
1792670278 96
1792670283 96
```
</details>

---

