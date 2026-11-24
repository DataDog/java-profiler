---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 13:05:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 967 |
| Sample Rate | 16.12/sec |
| Health Score | 1007% |
| Threads | 11 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (4 unique values: 46-51 cores)</summary>

```
1795543230 49
1795543235 49
1795543240 49
1795543245 46
1795543250 46
1795543255 46
1795543260 46
1795543265 46
1795543270 46
1795543275 46
1795543280 46
1795543285 51
1795543290 51
1795543295 49
1795543300 49
1795543305 49
1795543310 49
1795543315 49
1795543320 49
1795543325 49
```
</details>

---

