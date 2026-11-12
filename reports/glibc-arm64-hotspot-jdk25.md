---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 13:37:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 8 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1794508232 39
1794508237 39
1794508242 39
1794508247 39
1794508252 39
1794508257 39
1794508262 39
1794508267 39
1794508272 39
1794508277 39
1794508282 39
1794508287 39
1794508292 39
1794508297 39
1794508302 39
1794508307 39
1794508312 39
1794508317 39
1794508322 39
1794508327 51
```
</details>

---

