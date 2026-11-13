---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 00:07:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (2 unique values: 47-49 cores)</summary>

```
1794546163 47
1794546168 47
1794546173 47
1794546178 47
1794546183 47
1794546188 47
1794546193 49
1794546198 49
1794546203 49
1794546208 49
1794546213 49
1794546218 49
1794546223 49
1794546228 49
1794546233 49
1794546238 49
1794546243 49
1794546248 49
1794546253 49
1794546258 49
```
</details>

---

