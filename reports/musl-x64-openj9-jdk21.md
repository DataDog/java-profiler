---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 04:59:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 801 |
| Sample Rate | 13.35/sec |
| Health Score | 834% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (4 unique values: 82-91 cores)</summary>

```
1794477185 82
1794477190 84
1794477195 84
1794477200 84
1794477205 86
1794477210 86
1794477215 86
1794477220 86
1794477225 86
1794477230 86
1794477235 86
1794477240 86
1794477245 86
1794477250 86
1794477255 86
1794477260 86
1794477265 86
1794477270 86
1794477275 86
1794477280 91
```
</details>

---

