---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-18 05:49:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 241 |
| Sample Rate | 4.02/sec |
| Health Score | 251% |
| Threads | 13 |
| Allocations | 132 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1787046221 64
1787046226 64
1787046231 64
1787046236 64
1787046241 64
1787046246 64
1787046251 64
1787046256 64
1787046261 64
1787046266 64
1787046271 64
1787046276 64
1787046281 64
1787046286 64
1787046291 64
1787046296 64
1787046301 64
1787046306 64
1787046311 64
1787046316 64
```
</details>

---

