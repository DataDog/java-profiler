---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 12:40:41 EDT

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
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 284 |
| Sample Rate | 4.73/sec |
| Health Score | 296% |
| Threads | 12 |
| Allocations | 121 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1793378185 51
1793378190 46
1793378195 46
1793378200 46
1793378205 46
1793378210 46
1793378215 46
1793378220 46
1793378225 46
1793378230 46
1793378235 46
1793378240 46
1793378245 46
1793378250 46
1793378255 46
1793378260 46
1793378265 46
1793378270 46
1793378275 46
1793378280 46
```
</details>

---

