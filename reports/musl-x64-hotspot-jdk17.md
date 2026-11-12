---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-12 08:35:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 346 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 799 |
| Sample Rate | 13.32/sec |
| Health Score | 832% |
| Threads | 11 |
| Allocations | 513 |

<details>
<summary>CPU Timeline (3 unique values: 70-90 cores)</summary>

```
1794490171 73
1794490176 73
1794490181 73
1794490186 73
1794490191 73
1794490196 73
1794490201 73
1794490206 73
1794490211 73
1794490216 73
1794490221 73
1794490226 70
1794490231 70
1794490236 70
1794490241 70
1794490246 70
1794490251 70
1794490256 70
1794490261 70
1794490266 90
```
</details>

---

