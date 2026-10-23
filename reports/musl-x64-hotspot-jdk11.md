---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-23 05:58:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 682 |
| Sample Rate | 11.37/sec |
| Health Score | 711% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 883 |
| Sample Rate | 14.72/sec |
| Health Score | 920% |
| Threads | 10 |
| Allocations | 546 |

<details>
<summary>CPU Timeline (3 unique values: 73-94 cores)</summary>

```
1792749121 92
1792749126 92
1792749131 92
1792749136 92
1792749141 92
1792749146 92
1792749151 92
1792749156 92
1792749161 92
1792749166 92
1792749171 92
1792749176 92
1792749181 92
1792749186 92
1792749191 92
1792749196 94
1792749201 94
1792749206 94
1792749211 73
1792749216 73
```
</details>

---

