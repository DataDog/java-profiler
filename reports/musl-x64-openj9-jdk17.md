---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-05 05:23:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 12 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (3 unique values: 79-96 cores)</summary>

```
1770286763 96
1770286768 96
1770286773 96
1770286778 96
1770286783 96
1770286788 96
1770286793 96
1770286798 96
1770286803 96
1770286808 93
1770286813 93
1770286818 93
1770286823 93
1770286828 93
1770286833 93
1770286838 93
1770286843 93
1770286848 93
1770286853 93
1770286858 93
```
</details>

---

