---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-23 10:08:38 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 153 |
| Sample Rate | 2.55/sec |
| Health Score | 159% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 207 |
| Sample Rate | 3.45/sec |
| Health Score | 216% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 35-43 cores)</summary>

```
1790172196 41
1790172201 41
1790172206 41
1790172211 41
1790172216 43
1790172221 43
1790172226 41
1790172231 41
1790172236 41
1790172241 41
1790172246 41
1790172251 41
1790172256 38
1790172261 38
1790172266 38
1790172271 38
1790172276 38
1790172281 38
1790172286 35
1790172291 35
```
</details>

---

