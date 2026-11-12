---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-12 06:55:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 326 |
| Sample Rate | 5.43/sec |
| Health Score | 339% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 26-30 cores)</summary>

```
1794484096 28
1794484101 26
1794484106 26
1794484111 26
1794484116 26
1794484121 26
1794484126 26
1794484131 30
1794484136 30
1794484142 30
1794484147 30
1794484152 30
1794484157 30
1794484162 30
1794484167 30
1794484172 30
1794484177 30
1794484182 30
1794484187 30
1794484192 30
```
</details>

---

