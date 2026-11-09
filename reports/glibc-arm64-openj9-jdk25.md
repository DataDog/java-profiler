---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-09 09:27:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 15 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794234222 51
1794234227 51
1794234232 51
1794234237 51
1794234242 51
1794234247 51
1794234252 51
1794234257 51
1794234262 51
1794234267 51
1794234272 51
1794234277 51
1794234282 51
1794234287 51
1794234292 51
1794234297 51
1794234302 51
1794234307 51
1794234312 51
1794234317 51
```
</details>

---

