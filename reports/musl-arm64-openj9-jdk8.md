---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-24 05:28:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 238 |
| Sample Rate | 3.97/sec |
| Health Score | 248% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1790241530 46
1790241535 46
1790241540 46
1790241545 46
1790241550 46
1790241555 46
1790241560 46
1790241565 46
1790241570 48
1790241575 48
1790241580 48
1790241585 48
1790241590 48
1790241595 48
1790241600 48
1790241605 43
1790241610 43
1790241615 43
1790241620 43
1790241625 43
```
</details>

---

