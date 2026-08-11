---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-10 20:49:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 339 |
| Sample Rate | 5.65/sec |
| Health Score | 353% |
| Threads | 11 |
| Allocations | 143 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (4 unique values: 30-51 cores)</summary>

```
1786409154 30
1786409159 30
1786409164 30
1786409169 30
1786409174 30
1786409179 41
1786409184 41
1786409189 41
1786409194 41
1786409199 41
1786409204 41
1786409209 41
1786409214 41
1786409219 41
1786409224 41
1786409229 46
1786409234 46
1786409239 51
1786409244 51
1786409249 51
```
</details>

---

