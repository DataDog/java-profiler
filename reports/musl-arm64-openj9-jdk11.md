---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 10:08:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 39 |
| Sample Rate | 0.65/sec |
| Health Score | 41% |
| Threads | 7 |
| Allocations | 21 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1790172202 48
1790172207 48
1790172212 48
1790172217 48
1790172222 48
1790172227 48
1790172232 48
1790172237 48
1790172242 48
1790172248 48
1790172253 48
1790172258 48
1790172263 48
1790172268 46
1790172273 46
1790172278 46
1790172283 46
1790172288 46
1790172293 46
1790172298 46
```
</details>

---

