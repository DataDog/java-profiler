---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-30 10:12:29 EDT

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
| CPU Cores (start) | 87 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 626 |
| Sample Rate | 10.43/sec |
| Health Score | 652% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 706 |
| Sample Rate | 11.77/sec |
| Health Score | 736% |
| Threads | 11 |
| Allocations | 438 |

<details>
<summary>CPU Timeline (4 unique values: 69-87 cores)</summary>

```
1777558143 87
1777558148 87
1777558153 87
1777558158 87
1777558163 87
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
```
</details>

---

