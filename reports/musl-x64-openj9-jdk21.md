---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-11 05:27:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 10 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 12 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1773221005 54
1773221010 54
1773221015 54
1773221020 54
1773221025 59
1773221030 59
1773221035 59
1773221040 59
1773221045 64
1773221050 64
1773221055 64
1773221060 64
1773221065 64
1773221070 64
1773221075 64
1773221080 64
1773221085 64
1773221090 64
1773221095 64
1773221100 64
```
</details>

---

