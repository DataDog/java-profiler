---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-03 11:36:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 996 |
| Sample Rate | 16.60/sec |
| Health Score | 1038% |
| Threads | 12 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (2 unique values: 68-70 cores)</summary>

```
1770136387 70
1770136392 70
1770136397 70
1770136402 70
1770136407 70
1770136412 70
1770136417 70
1770136422 70
1770136427 70
1770136432 70
1770136437 70
1770136442 70
1770136447 70
1770136452 70
1770136457 70
1770136462 70
1770136467 68
1770136472 68
1770136477 68
1770136482 68
```
</details>

---

