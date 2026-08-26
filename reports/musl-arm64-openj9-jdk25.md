---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-26 07:12:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 11 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787742461 43
1787742466 43
1787742471 43
1787742476 43
1787742481 43
1787742486 48
1787742491 48
1787742496 48
1787742501 48
1787742506 48
1787742511 48
1787742516 48
1787742521 48
1787742526 48
1787742531 48
1787742536 48
1787742541 48
1787742546 48
1787742551 48
1787742556 48
```
</details>

---

