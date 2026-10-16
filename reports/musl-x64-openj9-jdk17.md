---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-16 09:30:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 9 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (4 unique values: 23-65 cores)</summary>

```
1792157149 23
1792157154 23
1792157159 23
1792157164 23
1792157169 23
1792157174 23
1792157179 23
1792157184 31
1792157189 31
1792157194 48
1792157199 48
1792157204 48
1792157209 48
1792157214 48
1792157219 48
1792157224 48
1792157229 48
1792157234 48
1792157239 48
1792157244 48
```
</details>

---

