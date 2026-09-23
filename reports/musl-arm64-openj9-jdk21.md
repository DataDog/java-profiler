---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-23 10:25:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 147 |
| Sample Rate | 2.45/sec |
| Health Score | 153% |
| Threads | 8 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 286 |
| Sample Rate | 4.77/sec |
| Health Score | 298% |
| Threads | 14 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790173214 43
1790173219 43
1790173224 43
1790173229 43
1790173234 48
1790173239 48
1790173244 48
1790173249 48
1790173254 48
1790173259 48
1790173264 48
1790173269 48
1790173274 48
1790173279 48
1790173284 48
1790173289 48
1790173294 48
1790173299 48
1790173304 48
1790173309 48
```
</details>

---

