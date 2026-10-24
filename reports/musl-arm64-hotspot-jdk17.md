---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-24 05:16:31 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (4 unique values: 38-48 cores)</summary>

```
1792833095 48
1792833100 48
1792833105 48
1792833110 48
1792833115 48
1792833120 48
1792833125 48
1792833130 48
1792833135 48
1792833140 48
1792833145 48
1792833150 43
1792833156 43
1792833161 43
1792833166 43
1792833171 41
1792833176 41
1792833181 41
1792833186 41
1792833191 41
```
</details>

---

