---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-26 09:38:31 EDT

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 129 |
| Sample Rate | 2.15/sec |
| Health Score | 134% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 15 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 37-48 cores)</summary>

```
1793021638 37
1793021643 48
1793021648 48
1793021653 48
1793021658 48
1793021663 48
1793021668 48
1793021673 48
1793021678 48
1793021683 48
1793021688 48
1793021693 48
1793021698 48
1793021703 48
1793021708 48
1793021713 48
1793021718 48
1793021723 48
1793021728 48
1793021733 48
```
</details>

---

