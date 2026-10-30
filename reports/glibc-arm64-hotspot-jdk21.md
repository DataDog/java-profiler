---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-30 06:16:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 238 |
| Sample Rate | 3.97/sec |
| Health Score | 248% |
| Threads | 14 |
| Allocations | 135 |

<details>
<summary>CPU Timeline (3 unique values: 41-51 cores)</summary>

```
1793355171 41
1793355176 41
1793355181 41
1793355186 41
1793355191 41
1793355196 41
1793355201 41
1793355206 41
1793355211 41
1793355216 41
1793355221 41
1793355226 41
1793355231 46
1793355236 46
1793355241 46
1793355246 46
1793355251 46
1793355256 46
1793355261 46
1793355266 46
```
</details>

---

