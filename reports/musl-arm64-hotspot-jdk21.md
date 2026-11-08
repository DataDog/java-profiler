---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-08 06:01:08 EST

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
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 22 |
| Sample Rate | 0.37/sec |
| Health Score | 23% |
| Threads | 8 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1794135133 43
1794135138 43
1794135143 43
1794135148 43
1794135153 43
1794135158 43
1794135163 43
1794135168 43
1794135173 43
1794135178 43
1794135183 43
1794135188 43
1794135193 43
1794135198 43
1794135203 38
1794135208 38
1794135213 38
1794135218 38
1794135223 43
1794135228 43
```
</details>

---

