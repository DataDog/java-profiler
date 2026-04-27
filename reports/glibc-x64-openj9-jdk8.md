---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-04-27 17:32:19 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 66 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 176 |
| Sample Rate | 2.93/sec |
| Health Score | 183% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 220 |
| Sample Rate | 3.67/sec |
| Health Score | 229% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 58-66 cores)</summary>

```
1777325186 66
1777325191 62
1777325196 62
1777325201 58
1777325206 58
1777325211 58
1777325216 58
1777325221 58
1777325226 58
1777325231 58
1777325236 58
1777325241 58
1777325246 58
1777325251 58
1777325256 58
1777325261 58
1777325267 58
1777325272 58
1777325277 58
1777325282 58
```
</details>

---

