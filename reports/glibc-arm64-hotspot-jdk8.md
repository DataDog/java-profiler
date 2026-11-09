---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-09 06:39:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 203 |
| Sample Rate | 3.38/sec |
| Health Score | 211% |
| Threads | 12 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 209 |
| Sample Rate | 3.48/sec |
| Health Score | 217% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 40-46 cores)</summary>

```
1794224085 42
1794224090 43
1794224095 43
1794224100 43
1794224105 43
1794224110 43
1794224115 43
1794224120 43
1794224125 46
1794224130 46
1794224135 46
1794224140 46
1794224145 46
1794224150 46
1794224155 41
1794224160 41
1794224165 41
1794224170 41
1794224175 43
1794224180 43
```
</details>

---

