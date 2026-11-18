---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 13:43:03 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 8 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 14 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (2 unique values: 32-64 cores)</summary>

```
1795027177 64
1795027182 64
1795027187 64
1795027192 64
1795027197 64
1795027202 64
1795027207 64
1795027212 64
1795027217 64
1795027222 64
1795027227 64
1795027232 64
1795027237 64
1795027242 64
1795027247 64
1795027252 64
1795027257 64
1795027262 64
1795027267 64
1795027272 64
```
</details>

---

