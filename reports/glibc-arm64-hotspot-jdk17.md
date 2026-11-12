---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 13:37:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 290 |
| Sample Rate | 4.83/sec |
| Health Score | 302% |
| Threads | 8 |
| Allocations | 164 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 10 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (2 unique values: 47-51 cores)</summary>

```
1794508186 47
1794508191 47
1794508196 47
1794508201 47
1794508206 47
1794508211 47
1794508216 47
1794508221 47
1794508226 47
1794508231 47
1794508236 47
1794508241 51
1794508246 51
1794508251 51
1794508256 51
1794508261 51
1794508266 51
1794508271 51
1794508276 51
1794508281 51
```
</details>

---

