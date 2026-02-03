---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-03 09:55:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 714 |
| Sample Rate | 11.90/sec |
| Health Score | 744% |
| Threads | 11 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 888 |
| Sample Rate | 14.80/sec |
| Health Score | 925% |
| Threads | 13 |
| Allocations | 470 |

<details>
<summary>CPU Timeline (4 unique values: 63-75 cores)</summary>

```
1770130212 63
1770130218 63
1770130223 63
1770130228 63
1770130233 63
1770130238 63
1770130243 68
1770130248 68
1770130253 68
1770130258 68
1770130263 68
1770130268 68
1770130273 68
1770130278 68
1770130283 68
1770130288 68
1770130293 73
1770130298 73
1770130303 73
1770130308 73
```
</details>

---

