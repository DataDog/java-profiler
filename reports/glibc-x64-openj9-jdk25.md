---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-20 01:00:54 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 443 |
| Sample Rate | 7.38/sec |
| Health Score | 461% |
| Threads | 10 |
| Allocations | 388 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 11 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (2 unique values: 42-44 cores)</summary>

```
1787201710 44
1787201715 44
1787201720 44
1787201725 44
1787201730 44
1787201735 44
1787201740 44
1787201745 44
1787201750 44
1787201755 44
1787201760 44
1787201765 44
1787201770 44
1787201775 44
1787201780 42
1787201785 42
1787201790 42
1787201795 42
1787201800 42
1787201805 42
```
</details>

---

