---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-04 16:24:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 12 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (4 unique values: 41-64 cores)</summary>

```
1793827194 46
1793827200 46
1793827205 46
1793827210 46
1793827215 46
1793827220 46
1793827225 46
1793827230 46
1793827235 46
1793827240 46
1793827245 46
1793827250 46
1793827255 41
1793827260 41
1793827265 41
1793827270 41
1793827275 46
1793827280 46
1793827285 46
1793827290 46
```
</details>

---

