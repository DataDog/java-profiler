---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-03-11 14:07:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 182 |
| Sample Rate | 3.03/sec |
| Health Score | 189% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 219 |
| Sample Rate | 3.65/sec |
| Health Score | 228% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 39-60 cores)</summary>

```
1773252111 56
1773252116 51
1773252121 51
1773252126 51
1773252131 51
1773252136 60
1773252141 60
1773252146 60
1773252152 46
1773252157 46
1773252162 46
1773252167 46
1773252172 46
1773252177 46
1773252182 42
1773252187 42
1773252192 42
1773252197 42
1773252202 42
1773252207 42
```
</details>

---

