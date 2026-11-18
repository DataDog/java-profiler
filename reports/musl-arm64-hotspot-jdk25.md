---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 06:29:51 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 308 |
| Sample Rate | 5.13/sec |
| Health Score | 321% |
| Threads | 10 |
| Allocations | 120 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 15 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1795001015 51
1795001020 51
1795001025 51
1795001030 51
1795001035 51
1795001040 46
1795001045 46
1795001050 46
1795001055 46
1795001060 46
1795001065 46
1795001070 46
1795001075 46
1795001080 46
1795001085 46
1795001090 46
1795001096 46
1795001101 51
1795001106 51
1795001111 51
```
</details>

---

