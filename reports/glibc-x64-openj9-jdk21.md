---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-19 18:19:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 10 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (2 unique values: 75-81 cores)</summary>

```
1792448118 75
1792448123 75
1792448128 75
1792448133 75
1792448138 75
1792448143 75
1792448148 75
1792448153 75
1792448158 75
1792448163 75
1792448168 75
1792448173 75
1792448178 81
1792448183 81
1792448188 81
1792448193 81
1792448198 81
1792448203 81
1792448208 81
1792448213 81
```
</details>

---

