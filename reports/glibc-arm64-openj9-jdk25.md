---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-15 20:26:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 11 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794792227 48
1794792232 48
1794792237 48
1794792242 48
1794792247 48
1794792252 48
1794792257 48
1794792262 48
1794792267 48
1794792272 48
1794792277 48
1794792282 48
1794792287 48
1794792292 48
1794792297 48
1794792302 48
1794792307 48
1794792312 48
1794792317 48
1794792322 48
```
</details>

---

