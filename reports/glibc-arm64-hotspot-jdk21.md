---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 18:01:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 12 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1789682185 43
1789682190 43
1789682195 46
1789682200 46
1789682205 46
1789682210 46
1789682215 46
1789682220 46
1789682225 46
1789682230 48
1789682235 48
1789682240 48
1789682245 48
1789682250 48
1789682255 48
1789682260 48
1789682265 48
1789682270 48
1789682275 48
1789682280 48
```
</details>

---

