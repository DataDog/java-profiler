---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-26 07:12:53 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 191 |
| Sample Rate | 3.18/sec |
| Health Score | 199% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 27 |
| Sample Rate | 0.45/sec |
| Health Score | 28% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1787742506 48
1787742511 48
1787742516 48
1787742521 48
1787742526 48
1787742531 48
1787742536 48
1787742541 48
1787742546 40
1787742551 40
1787742556 40
1787742561 40
1787742566 40
1787742571 40
1787742576 40
1787742581 40
1787742586 40
1787742591 40
1787742596 40
1787742601 40
```
</details>

---

