---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-04 08:54:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 13 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793800216 48
1793800221 48
1793800226 48
1793800231 48
1793800236 48
1793800241 48
1793800246 48
1793800251 48
1793800256 48
1793800261 48
1793800266 48
1793800271 48
1793800276 48
1793800281 48
1793800286 48
1793800291 48
1793800296 48
1793800301 48
1793800306 48
1793800311 48
```
</details>

---

