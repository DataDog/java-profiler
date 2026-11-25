---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 10:02:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 784 |
| Sample Rate | 13.07/sec |
| Health Score | 817% |
| Threads | 8 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (2 unique values: 50-51 cores)</summary>

```
1795618626 50
1795618631 50
1795618636 50
1795618641 50
1795618646 50
1795618651 50
1795618656 50
1795618661 50
1795618666 50
1795618671 50
1795618676 50
1795618681 50
1795618686 50
1795618691 50
1795618696 50
1795618701 50
1795618706 51
1795618711 51
1795618716 51
1795618721 51
```
</details>

---

