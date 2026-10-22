---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-22 17:27:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
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
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 13 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792704079 43
1792704084 43
1792704089 43
1792704094 43
1792704099 43
1792704104 43
1792704109 43
1792704114 43
1792704119 43
1792704124 48
1792704129 48
1792704134 48
1792704139 48
1792704144 48
1792704149 48
1792704154 48
1792704159 48
1792704164 48
1792704169 48
1792704174 48
```
</details>

---

