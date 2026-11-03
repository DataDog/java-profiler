---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-03 11:00:42 EST

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 8 |
| Allocations | 419 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (3 unique values: 19-27 cores)</summary>

```
1793721227 19
1793721232 19
1793721237 19
1793721242 19
1793721247 19
1793721252 19
1793721257 19
1793721262 19
1793721267 19
1793721272 19
1793721277 19
1793721282 19
1793721287 27
1793721292 27
1793721297 27
1793721302 27
1793721307 25
1793721312 25
1793721317 25
1793721322 25
```
</details>

---

