---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-03-13 12:15:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 11 |
| Allocations | 329 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 13 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 55-94 cores)</summary>

```
1773418132 94
1773418137 94
1773418142 58
1773418147 58
1773418152 58
1773418157 58
1773418162 58
1773418167 58
1773418172 58
1773418177 58
1773418182 58
1773418187 58
1773418192 58
1773418197 58
1773418202 58
1773418208 58
1773418213 58
1773418218 58
1773418223 58
1773418228 58
```
</details>

---

