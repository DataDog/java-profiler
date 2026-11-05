---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-05 09:56:09 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 534 |
| Sample Rate | 8.90/sec |
| Health Score | 556% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 11 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (2 unique values: 63-64 cores)</summary>

```
1793890221 63
1793890226 63
1793890231 63
1793890236 63
1793890241 63
1793890246 63
1793890251 63
1793890256 64
1793890261 64
1793890266 64
1793890271 64
1793890276 64
1793890281 64
1793890286 64
1793890291 64
1793890296 64
1793890301 64
1793890306 64
1793890311 64
1793890316 64
```
</details>

---

