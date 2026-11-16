---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 08:44:05 EST

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 44 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 187 |
| Sample Rate | 3.12/sec |
| Health Score | 195% |
| Threads | 13 |
| Allocations | 112 |

<details>
<summary>CPU Timeline (4 unique values: 35-43 cores)</summary>

```
1794836397 35
1794836402 35
1794836407 35
1794836412 38
1794836417 38
1794836422 38
1794836427 38
1794836432 38
1794836437 38
1794836442 40
1794836447 40
1794836452 40
1794836457 40
1794836462 40
1794836467 40
1794836472 43
1794836477 43
1794836482 43
1794836487 43
1794836492 40
```
</details>

---

