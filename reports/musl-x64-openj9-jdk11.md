---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 11:32:49 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 9 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 10 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (2 unique values: 60-62 cores)</summary>

```
1795192066 60
1795192071 60
1795192076 60
1795192081 60
1795192086 62
1795192091 62
1795192096 62
1795192101 62
1795192106 62
1795192111 62
1795192116 62
1795192121 62
1795192126 62
1795192131 62
1795192136 62
1795192141 62
1795192146 62
1795192151 62
1795192156 62
1795192161 62
```
</details>

---

