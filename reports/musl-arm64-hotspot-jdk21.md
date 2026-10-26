---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-26 10:05:15 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 11 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (4 unique values: 37-42 cores)</summary>

```
1793023173 39
1793023178 39
1793023183 39
1793023188 39
1793023193 39
1793023198 37
1793023203 37
1793023208 40
1793023213 40
1793023218 40
1793023223 40
1793023228 40
1793023233 40
1793023238 40
1793023243 40
1793023248 40
1793023253 40
1793023258 40
1793023263 40
1793023268 40
```
</details>

---

