---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 17:29:31 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 900 |
| Sample Rate | 15.00/sec |
| Health Score | 938% |
| Threads | 10 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (4 unique values: 53-75 cores)</summary>

```
1789680096 75
1789680101 75
1789680106 75
1789680112 75
1789680117 75
1789680122 75
1789680127 75
1789680132 73
1789680137 73
1789680142 73
1789680147 73
1789680152 73
1789680157 73
1789680162 73
1789680167 73
1789680172 73
1789680177 73
1789680182 75
1789680187 75
1789680192 75
```
</details>

---

