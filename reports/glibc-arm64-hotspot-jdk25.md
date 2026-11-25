---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 16:18:46 EST

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 6 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 14-34 cores)</summary>

```
1795641235 14
1795641241 14
1795641246 14
1795641251 14
1795641256 14
1795641261 14
1795641266 14
1795641271 14
1795641276 14
1795641281 14
1795641286 14
1795641291 14
1795641296 14
1795641301 14
1795641306 14
1795641311 14
1795641316 14
1795641321 14
1795641326 14
1795641331 34
```
</details>

---

