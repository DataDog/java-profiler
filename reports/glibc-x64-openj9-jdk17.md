---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-11 17:02:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 11 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (5 unique values: 59-76 cores)</summary>

```
1794434255 61
1794434260 61
1794434265 61
1794434270 61
1794434275 61
1794434280 61
1794434285 61
1794434290 61
1794434295 61
1794434300 61
1794434305 61
1794434310 63
1794434315 63
1794434320 63
1794434325 63
1794434330 63
1794434335 63
1794434340 59
1794434345 59
1794434350 59
```
</details>

---

