---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 00:07:35 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 8 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 6 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1794546188 24
1794546193 24
1794546198 24
1794546203 24
1794546208 24
1794546213 24
1794546218 24
1794546223 24
1794546228 24
1794546233 24
1794546238 24
1794546243 24
1794546248 29
1794546253 29
1794546258 29
1794546263 34
1794546268 34
1794546273 34
1794546278 34
1794546283 34
```
</details>

---

