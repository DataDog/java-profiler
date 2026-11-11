---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 09:47:15 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 9 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1794408142 48
1794408147 48
1794408152 48
1794408157 48
1794408162 48
1794408167 48
1794408172 46
1794408177 46
1794408182 46
1794408187 46
1794408192 46
1794408197 46
1794408202 46
1794408207 46
1794408212 46
1794408217 46
1794408222 46
1794408227 46
1794408232 48
1794408237 48
```
</details>

---

