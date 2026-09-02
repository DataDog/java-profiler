---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-02 11:55:34 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1788364298 96
1788364303 96
1788364308 96
1788364313 96
1788364318 96
1788364323 96
1788364328 96
1788364333 96
1788364338 96
1788364343 96
1788364348 88
1788364353 88
1788364358 88
1788364363 88
1788364368 88
1788364373 88
1788364378 88
1788364383 88
1788364388 88
1788364393 88
```
</details>

---

