---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-10 17:36:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 6 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 305 |
| Sample Rate | 5.08/sec |
| Health Score | 318% |
| Threads | 10 |
| Allocations | 151 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1770762632 24
1770762637 24
1770762642 24
1770762647 24
1770762652 24
1770762657 24
1770762662 24
1770762667 24
1770762672 24
1770762677 24
1770762682 24
1770762687 24
1770762692 24
1770762697 24
1770762702 24
1770762707 24
1770762712 24
1770762717 24
1770762722 24
1770762727 24
```
</details>

---

