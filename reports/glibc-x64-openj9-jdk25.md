---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 21:59:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 389 |
| Sample Rate | 6.48/sec |
| Health Score | 405% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 11 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 43-63 cores)</summary>

```
1793674466 63
1793674471 63
1793674476 63
1793674481 63
1793674486 63
1793674491 63
1793674496 63
1793674501 63
1793674506 63
1793674511 63
1793674516 63
1793674521 63
1793674526 63
1793674531 63
1793674536 43
1793674541 43
1793674546 43
1793674551 43
1793674556 43
1793674561 43
```
</details>

---

