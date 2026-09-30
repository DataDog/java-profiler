---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-30 10:44:06 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 12 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 9 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (3 unique values: 20-22 cores)</summary>

```
1790779140 20
1790779145 20
1790779150 20
1790779155 20
1790779160 20
1790779165 20
1790779170 22
1790779175 22
1790779180 22
1790779185 22
1790779190 22
1790779195 22
1790779201 22
1790779206 22
1790779211 22
1790779216 22
1790779221 21
1790779226 21
1790779231 21
1790779236 21
```
</details>

---

