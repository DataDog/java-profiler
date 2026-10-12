---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-12 05:55:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 174 |
| Sample Rate | 2.90/sec |
| Health Score | 181% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 254 |
| Sample Rate | 4.23/sec |
| Health Score | 264% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 64-96 cores)</summary>

```
1791798659 64
1791798664 64
1791798669 64
1791798674 64
1791798679 72
1791798684 72
1791798689 72
1791798694 72
1791798699 72
1791798704 72
1791798709 72
1791798714 72
1791798719 72
1791798724 72
1791798729 72
1791798734 72
1791798739 72
1791798744 72
1791798749 72
1791798754 72
```
</details>

---

