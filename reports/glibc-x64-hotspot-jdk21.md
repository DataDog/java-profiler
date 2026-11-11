---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 09:26:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 12 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 50-52 cores)</summary>

```
1794406986 52
1794406991 52
1794406996 52
1794407001 52
1794407006 52
1794407011 52
1794407016 52
1794407021 52
1794407026 52
1794407031 52
1794407036 52
1794407041 52
1794407046 52
1794407051 52
1794407056 52
1794407061 50
1794407066 50
1794407071 50
1794407076 50
1794407081 50
```
</details>

---

