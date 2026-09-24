---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-24 05:29:00 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 162 |
| Sample Rate | 2.70/sec |
| Health Score | 169% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 184 |
| Sample Rate | 3.07/sec |
| Health Score | 192% |
| Threads | 6 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 54-96 cores)</summary>

```
1790241525 96
1790241530 96
1790241535 63
1790241540 63
1790241545 63
1790241550 63
1790241555 63
1790241560 63
1790241565 63
1790241570 63
1790241575 54
1790241580 54
1790241585 54
1790241590 54
1790241595 54
1790241600 54
1790241605 54
1790241610 54
1790241615 54
1790241620 54
```
</details>

---

