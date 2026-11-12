---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 13:35:18 EST

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
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 8 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (4 unique values: 39-52 cores)</summary>

```
1794508187 39
1794508192 52
1794508197 52
1794508202 52
1794508207 52
1794508212 39
1794508217 39
1794508222 39
1794508227 39
1794508232 39
1794508237 39
1794508242 39
1794508247 39
1794508252 51
1794508257 51
1794508262 51
1794508267 51
1794508272 46
1794508277 46
1794508282 46
```
</details>

---

