---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 13:37:07 EST

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 8.97/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 10 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (3 unique values: 58-62 cores)</summary>

```
1794508195 58
1794508200 58
1794508205 58
1794508210 58
1794508215 58
1794508220 58
1794508225 58
1794508230 58
1794508235 62
1794508240 62
1794508245 60
1794508250 60
1794508255 62
1794508260 62
1794508265 62
1794508270 62
1794508275 62
1794508280 62
1794508285 62
1794508290 62
```
</details>

---

