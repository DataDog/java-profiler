---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-15 05:47:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 14 |
| Allocations | 155 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1786786990 46
1786786995 46
1786787000 46
1786787005 46
1786787010 46
1786787015 46
1786787020 46
1786787025 46
1786787030 46
1786787035 48
1786787040 48
1786787045 48
1786787050 48
1786787055 48
1786787060 48
1786787066 48
1786787071 48
1786787076 48
1786787081 48
1786787086 48
```
</details>

---

