---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-05 09:56:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 11 |
| Allocations | 110 |

<details>
<summary>CPU Timeline (2 unique values: 37-40 cores)</summary>

```
1793890220 37
1793890225 37
1793890230 37
1793890235 37
1793890240 37
1793890246 37
1793890251 37
1793890256 37
1793890261 37
1793890266 37
1793890271 40
1793890276 40
1793890281 40
1793890286 40
1793890291 40
1793890296 40
1793890301 40
1793890306 40
1793890311 40
1793890316 40
```
</details>

---

