---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-25 13:33:27 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 20 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 389 |
| Sample Rate | 6.48/sec |
| Health Score | 405% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 16 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 20-24 cores)</summary>

```
1795631284 24
1795631289 24
1795631294 24
1795631299 24
1795631304 24
1795631309 24
1795631314 24
1795631319 24
1795631324 24
1795631329 24
1795631334 24
1795631339 24
1795631344 24
1795631349 24
1795631354 24
1795631359 24
1795631364 24
1795631369 20
1795631374 20
1795631379 20
```
</details>

---

