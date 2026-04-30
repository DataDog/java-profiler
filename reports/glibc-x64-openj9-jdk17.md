---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-30 10:12:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 314 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 694 |
| Sample Rate | 11.57/sec |
| Health Score | 723% |
| Threads | 11 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (5 unique values: 69-87 cores)</summary>

```
1777558168 87
1777558173 87
1777558178 87
1777558183 87
1777558188 75
1777558193 75
1777558198 75
1777558203 75
1777558208 71
1777558213 71
1777558218 71
1777558223 69
1777558228 69
1777558233 69
1777558238 69
1777558243 69
1777558248 69
1777558253 69
1777558258 69
1777558263 69
```
</details>

---

