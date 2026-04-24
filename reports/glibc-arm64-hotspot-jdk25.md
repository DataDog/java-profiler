---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-24 17:03:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 239 |
| Sample Rate | 3.98/sec |
| Health Score | 249% |
| Threads | 9 |
| Allocations | 121 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 54-59 cores)</summary>

```
1777064264 59
1777064269 59
1777064274 59
1777064279 59
1777064284 59
1777064289 59
1777064294 59
1777064299 59
1777064304 59
1777064309 59
1777064314 54
1777064319 54
1777064324 54
1777064329 54
1777064334 54
1777064339 54
1777064344 54
1777064349 54
1777064354 54
1777064359 54
```
</details>

---

